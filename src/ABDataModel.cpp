/*
 * ABDataModel.cpp
 *
 *  Created on: 2017年2月6日
 *      Author: Joe
 */

#include "ABDataModel.hpp"
using namespace bb::cascades;
using namespace bb::data;

#include <ctime>
#include <cfloat>
using namespace std;

#include <QDir>

ABDataModel::ABDataModel(QObject *parent)
    :DataModel(parent), sqlda(NULL), m_data(),
     expense(0), max(DBL_MIN), mean(0), min(DBL_MAX)
{

}

ABDataModel::~ABDataModel()
{
    // sqlda is a QObject with a proper parent set, so no release is needed.
    // take care of our own data.
    for(int i = 0; i < m_data.size(); i++) {
        for (int j = 0; j < 12; j++) {
            if(m_data[i].month[j] != NULL) {
                delete m_data[i].month[j];
            }
        }
    }
}

/**
 * execution flow:
 * 1) query all data from SQLDataAccess. if success, reset all data members.
 * 2) group all data in a hierarchy: universal > year > month > item
 *  2.1) first adds all items to related month, and maintains month's total expense
 *  2.2) then, calculate max/mean/min expense of month and total expense for every year
 *  2.3) then those statistics for universal.
 */
void ABDataModel::load() {
    if (sqlda == NULL) {
        return;
    }

    const QString query = "SELECT date, expense, detail, comment from Account "
                          "ORDER BY date DESC";
    const QVariant res = sqlda->execute(query);
    if (sqlda->hasError()) {
        qDebug() << "ABDataModel::load: " << sqlda->error().errorMessage() << endl;
        return;
    }

    m_data.clear();
    expense = 0;
    max = DBL_MIN;
    mean = 0;
    min = DBL_MAX;

    const QVariantList result = res.toList();
    // add items to itemList, maintain 'expense' for every MonthNode.
    // maintain `monthCount' for every YearNode. but not `expense', `max/mean/min'
    for (int idx = -1, i = 0; i < result.size(); i++) {
        const QVariantMap map = result[i].toMap();
        const time_t timer = map["date"].toLongLong() / 1000UL;
        const struct tm *time = localtime(&timer);
        const int year = 1900 + time->tm_year;  // year since 1900, see c reference.
        const int mon = 11 - time->tm_mon;  // cause data are descended.

        if (idx == -1 || year != m_data[idx].year) {
            // another year should be added to our data
            m_data.push_back(YearNode());
            ++idx;
            m_data[idx].year = year;
            m_data[idx].monthCount = 0;
        }
        if (m_data[idx].month[mon] == NULL) {
            // another month should be added to this year
            ++m_data[idx].monthCount;
            m_data[idx].month[mon] = new MonthNode();
            m_data[idx].month[mon]->parent = &m_data[idx];
            m_data[idx].month[mon]->month = 11 - mon;
            m_data[idx].month[mon]->expense = 0;
        }
        // don't use adjust_mexpense() here, since the expense may change again very soon.
        m_data[idx].month[mon]->expense += map["expense"].toDouble();
        m_data[idx].month[mon]->itemList.push_back(map);
    }

    // set `expense', `max/mean/min' for every `YearNode's and `Universal'.
    for (int i = 0; i < m_data.size(); i++) {
        m_data[i].expense = 0;
        m_data[i].max = DBL_MIN;
        m_data[i].min = DBL_MAX;
        for (int j = 0; j < 12; j++) {
            if (m_data[i].month[j] == NULL) {
                continue;
            }

            m_data[i].expense += m_data[i].month[j]->expense;
            // maintain year's statistics
            if (m_data[i].month[j]->expense > m_data[i].max) {
            	m_data[i].max = m_data[i].month[j]->expense;
            }
            if (m_data[i].month[j]->expense < m_data[i].min) {
            	m_data[i].min = m_data[i].month[j]->expense;
            }
        }
        set_ymean(i);

        expense += m_data[i].expense;
        // maintain universal's statistics
        if (m_data[i].expense > max) {
        	max = m_data[i].expense;
        }
        if (m_data[i].expense < min) {
        	min = m_data[i].expense;
        }
    }
    set_mean();

    emit itemsChanged(DataModelChangeType::Init, QSharedPointer<DataModel::IndexMapper>(0));
}

/**
 * return a pointer of MonthNode indexed by @indexPath
 * NULL is returned, if @indexPath is shorter than 3 or out of range.
 */
MonthNode *ABDataModel::get_month(const QVariantList &indexPath) const {
    if (indexPath.size() < 3) {
        return NULL;
    }

    const int idx[2] = {indexPath[1].toInt(), indexPath[2].toInt()};
    const YearNode &year = m_data[idx[0]];
    for (int nth = 0, i = 0; i < 12; i++) {
        if (year.month[i] != NULL) {
            if (++nth > idx[1]) {
                return year.month[i];
            }
        }
    }
    return NULL;
}

int ABDataModel::childCount (const QVariantList &indexPath) {
    // declare on the top to eliminate crosses initializations
    int idx;
    switch (indexPath.size()) {
        case 0: // only one universal
            return 1;
        case 1:
            return m_data.size();
        case 2:
            idx = indexPath[1].toInt();
            return m_data[idx].monthCount;
        case 3:
            return get_month(indexPath)->itemList.size();
        case 4: // item has no child
            return 0;
        default:
            return 0;
    }
}

bool ABDataModel::hasChildren (const QVariantList &indexPath) {
    // every valid year and month has their children, but item doesn't
    switch (indexPath.size()) {
        case 0:
            return true;
        case 1:
            return !m_data.empty();
        case 2: // if year exists, there must be a item therefore a month.
            return true;
        case 3:
            return true;
        case 4:
            return false;
        default:
            return false;
    }
}

QString ABDataModel::itemType (const QVariantList &indexPath) {
    switch (indexPath.size()) {
        case 0:
            return "";
        case 1:
            return "root";
        case 2:
            return "year";
        case 3:
            return "month";
        case 4:
            return "item";
        default:
            return "";
    }
}

QVariant ABDataModel::data (const QVariantList &indexPath) {
    QVariantMap map;

    // declare on the top to eliminate crosses initializations.
    int idx;
    const MonthNode *month;
    switch (indexPath.size()) {
        case 0:
            break;
        case 1: // root
            map["expense"] = expense;
            map["max"] = max;
            map["min"] = min;
            map["mean"] = mean;
            break;
        case 2: // year
            idx = indexPath[1].toInt();
            map["year"] = m_data[idx].year;
            map["expense"] = m_data[idx].expense;
            map["max"] = m_data[idx].max;
            map["min"] = m_data[idx].min;
            map["mean"] = m_data[idx].mean;
            map["y_mean"] = mean;
            break;
        case 3: // month
            month = get_month(indexPath);
            map["year"] = month->parent->year;
            map["month"] = month->month;
            map["expense"] = month->expense;
            map["m_mean"] = month->parent->mean;
            break;
        case 4: // item
            idx = indexPath[3].toInt();
            map = get_month(indexPath)->itemList[idx];
    }
    return map;
}

QString ABDataModel::source() const {
    return m_source;
}

void ABDataModel::setSource(QString source) {
	if (m_source == source) {
		return;
	}

    m_source = source;
    emit sourceChanged(source);

    if (sqlda) {
        delete sqlda;
    }

    source = QDir::currentPath() + "/app/native/assets/" + source;
    sqlda = new SqlDataAccess(source, this);
    load();
}

/**
 * Increase @year's expense by @expense (or decrease if @expense < 0)
 * and check if that change makes sense to universal's statistics.
 *
 * there is no need to call this function manually, use adjust_mexpense() instead.
 */
void ABDataModel::adjust_yexpense(double expense, int year) {
	m_data[year].expense += expense;
	if (m_data[year].expense > max) {
		max = m_data[year].expense;
	}
	if (m_data[year].expense < min) {
		min = m_data[year].expense;
	}
	set_ymean(year);

	this->expense += expense;
	set_mean();
}

/**
 * Increase @year->@mon's expense by @expense (or decrease if @expense < 0)
 * and check if that change makes sense to @year's statistics.
 */
void ABDataModel::adjust_mexpense(double expense, int year, int mon) {
	m_data[year].month[mon]->expense += expense;
	if (m_data[year].month[mon]->expense > m_data[year].max) {
		m_data[year].max = m_data[year].month[mon]->expense;
	}
	if (m_data[year].month[mon]->expense < m_data[year].min) {
		m_data[year].min = m_data[year].month[mon]->expense;
	}

	adjust_yexpense(expense, year);
}

/**
 * to adjust universal's mean.
 * this will be automatically called by adjust_yexpense(), therefore adjust_mexpense()
 *
 * you should call this manually, if you want to remove some `YearNode's in m_data.
 * in that condition, you need to:
 * 	1) call adjust_yexpense first to maintain other statistics.
 * 	2) remove that year node
 * 	3) call this function to overwrite the mean's value
 * example:
 * 	adjust_yexpense(-m_data[year].expense, year);
 * 	m_data.erase(year);
 * 	set_mean();
 */
void ABDataModel::set_mean() {
	if (m_data.empty()) {
		mean = 0;
	} else {
		mean = expense / m_data.size();
	}
}

/**
 * to adjust @year's mean.
 * this will be automatically called by adjust_yexpense(), therefore adjust_mexpense()
 *
 * you should call this manually, if you want to remove some `MonthNode in this @year.
 * in that condition, you need to:
 * 	1) call adjust_mexpense first to maintain other statistics.
 * 	2) release that month node
 * 	3) call this function to overwrite the mean's value
 * 	4) if that makes the year a empty list, then remove that year from m_data.
 * example:
 * 	adjust_mexpense(-expense_of_that_month, year, mon);
 * 	delete m_data.[year].month[mon];
 * 	m_data.[year].month[mon] = NULL;
 * 	--m_data.[year].monthCount;
 * 	set_ymean(year);
 */
void ABDataModel::set_ymean(int year) {
	if (m_data[year].monthCount == 0) {
		m_data[year].mean = 0;
	} else {
		m_data[year].mean = m_data[year].expense / m_data[year].monthCount;
	}
}

bool ABDataModel::insert_item (const QVariantMap &item) {
	if (sqlda == NULL) {
		return false;
	}

	const QString insert = "INSERT INTO Account (date, expense, detail, comment)"
						   "VALUES (:date, :expense, :detail, :comment)";
	sqlda->execute(insert, item);
	if (sqlda->hasError()) {
		qDebug() << "ABDataModel::insert_item: " << sqlda->error().errorMessage() << endl;
		return false;
	}

	QVariantList indexPath;

    const time_t timer = item["date"].toLongLong() / 1000L;
    const struct tm *time = localtime(&timer);
    const int year = 1900 + time->tm_year;  // year since 1900, see c reference.
    const int mon = 11 - time->tm_mon;  // cause data are descended.

    int idxy = 0;
    for (; idxy < m_data.size(); idxy++) {
    	if (m_data[idxy].year <= year) {
    		break;
    	}
    }
    indexPath << idxy;
    if (idxy == m_data.size() || m_data[idxy].year != year) {
    	YearNode this_yaer;
    	this_yaer.year = year;
    	this_yaer.expense = 0;
    	this_yaer.max = DBL_MIN;
    	this_yaer.min = DBL_MAX;

    	m_data.insert(m_data.begin() + idxy, this_yaer);
    	emit itemAdded(indexPath);
    }
    indexPath << mon;
    if (m_data[idxy].month[mon] == NULL) {
    	m_data[idxy].month[mon] = new MonthNode();
    	m_data[idxy].month[mon]->parent = &m_data[idxy];
    	m_data[idxy].month[mon]->month = 11 - mon;
    	m_data[idxy].month[mon]->expense = 0;

    	emit itemAdded(indexPath);
    }

    ItemList &list = m_data[idxy].month[mon]->itemList;
    int idx = 0;
    for(; idx < list.size(); idx++) {
    	if (list[idx]["date"].toLongLong() / 1000L <= timer) {
    		break;
    	}
    }
    indexPath << idx;
    list.insert(list.begin() + idx, item);
    adjust_mexpense(item["expense"].toDouble(), idxy, mon);

    emit itemAdded(indexPath);
    return true;
}

bool ABDataModel::delete_item (QVariantList indexPath) {
	if (sqlda == NULL) {
		return false;
	}

	// only item can be deleted now.
	if (indexPath.size() < 4) {
		return false;
	}
	const int year = indexPath[1].toInt();
	const int mon = indexPath[2].toInt();
	const int idx = indexPath[3].toInt();

	MonthNode *month = get_month(indexPath);
	const double expense = month->itemList[idx]["expense"].toDouble();
	const long long date = month->itemList[idx]["date"].toLongLong();
	adjust_mexpense(-expense, year, mon);

	month->itemList.erase(month->itemList.begin() + idx);
	emit itemRemoved(indexPath);
	if (month->itemList.empty()) {
		delete m_data[year].month[mon];
		m_data[year].month[mon] = NULL;
		--m_data[year].monthCount;
		set_ymean(year);

		indexPath.removeLast();
		emit itemRemoved(indexPath);

		if (m_data[year].monthCount == 0) {
			 m_data.erase(m_data.begin() + year);
			 set_mean();

			 indexPath.removeLast();
			 emit itemRemoved(indexPath);
		}
	}

	const QString exec = "DELETE FROM Account WHERE date = ?";
	sqlda->execute(exec, QVariantList() << date);
	if (sqlda->hasError()) {
		qDebug() << "ABDataModel::delete_item: " << sqlda->error().errorMessage() << endl;
		return false;
	}

	return true;
}
