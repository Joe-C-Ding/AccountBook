/*
 * ABDataModel.h
 *
 *  Created on: 2017年2月6日
 *      Author: Joe
 */

#ifndef ABDATAMODEL_H_
#define ABDATAMODEL_H_

#include <bb/data/SqlDataAccess>
#include <bb/cascades/DataModel>

#include <deque>

#include <QObject>
#include <QtCore/QVariant>

struct _MonthNode;
struct _YearNode {
    int year;
    double expense;
    double max, mean, min;

    _MonthNode *month[12];
    int monthCount;
};
typedef struct _YearNode YearNode;
typedef std::deque<YearNode> YearList;


struct _MonthNode {
    int month;
    double expense;
    _YearNode *parent;

    std::deque<QVariantMap> itemList;
};
typedef struct _MonthNode MonthNode;
typedef std::deque<QVariantMap> ItemList;


class ABDataModel: public bb::cascades::DataModel {
    Q_OBJECT

    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)

public:
    ABDataModel(QObject *parent = 0);
    ~ABDataModel();

public:
    Q_INVOKABLE int childCount (const QVariantList &indexPath);
    Q_INVOKABLE bool hasChildren (const QVariantList &indexPath);
    Q_INVOKABLE QString itemType (const QVariantList &indexPath);
    Q_INVOKABLE QVariant data (const QVariantList &indexPath);

    Q_INVOKABLE QString source() const;
    Q_INVOKABLE void setSource(QString source);

    Q_INVOKABLE bool insert_item (const QVariantMap &item);
    Q_INVOKABLE bool delete_item (QVariantList indexPath);

Q_SIGNALS:
    void itemAdded (QVariantList indexPath);
    void itemRemoved (QVariantList indexPath);
    void itemUpdated (QVariantList indexPath);
    void itemsChanged (bb::cascades::DataModelChangeType::Type eChangeType=bb::cascades::DataModelChangeType::Init,
            QSharedPointer< bb::cascades::DataModel::IndexMapper > indexMapper=QSharedPointer< bb::cascades::DataModel::IndexMapper >(0));

    void sourceChanged(QString source);

private:
    void load();
    MonthNode *get_month(const QVariantList &indexPath) const;

    void adjust_mexpense(double expense, int year, int mon);
    void adjust_yexpense(double expense, int year);
    void set_mean();
    void set_ymean(int year);

private:
    QString m_source;
    bb::data::SqlDataAccess *sqlda;

    YearList m_data;
    double expense;
    double max, mean, min;
};

#endif /* ABDATAMODEL_H_ */
