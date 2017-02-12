/****************************************************************************
** Meta object code from reading C++ file 'ABDataModel.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ABDataModel.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ABDataModel.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ABDataModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       1,   89, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   13,   12,   12, 0x05,
      47,   13,   12,   12, 0x05,
      73,   13,   12,   12, 0x05,
     123,   99,   12,   12, 0x05,
     242,  230,   12,   12, 0x25,
     296,   12,   12,   12, 0x25,
     318,  311,   12,   12, 0x05,

 // methods: signature, parameters, type, tag, flags
     345,   13,  341,   12, 0x02,
     375,   13,  370,   12, 0x02,
     409,   13,  401,   12, 0x02,
     441,   13,  432,   12, 0x02,
     460,   12,  401,   12, 0x02,
     469,  311,   12,   12, 0x02,
     493,  488,  370,   12, 0x02,
     518,   13,  370,   12, 0x02,

 // properties: name, type, flags
     311,  401, 0x0a495103,

 // properties: notify_signal_id
       6,

       0        // eod
};

static const char qt_meta_stringdata_ABDataModel[] = {
    "ABDataModel\0\0indexPath\0itemAdded(QVariantList)\0"
    "itemRemoved(QVariantList)\0"
    "itemUpdated(QVariantList)\0"
    "eChangeType,indexMapper\0"
    "itemsChanged(bb::cascades::DataModelChangeType::Type,QSharedPointer<bb"
    "::cascades::DataModel::IndexMapper>)\0"
    "eChangeType\0"
    "itemsChanged(bb::cascades::DataModelChangeType::Type)\0"
    "itemsChanged()\0source\0sourceChanged(QString)\0"
    "int\0childCount(QVariantList)\0bool\0"
    "hasChildren(QVariantList)\0QString\0"
    "itemType(QVariantList)\0QVariant\0"
    "data(QVariantList)\0source()\0"
    "setSource(QString)\0item\0"
    "insert_item(QVariantMap)\0"
    "delete_item(QVariantList)\0"
};

void ABDataModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ABDataModel *_t = static_cast<ABDataModel *>(_o);
        switch (_id) {
        case 0: _t->itemAdded((*reinterpret_cast< QVariantList(*)>(_a[1]))); break;
        case 1: _t->itemRemoved((*reinterpret_cast< QVariantList(*)>(_a[1]))); break;
        case 2: _t->itemUpdated((*reinterpret_cast< QVariantList(*)>(_a[1]))); break;
        case 3: _t->itemsChanged((*reinterpret_cast< bb::cascades::DataModelChangeType::Type(*)>(_a[1])),(*reinterpret_cast< QSharedPointer<bb::cascades::DataModel::IndexMapper>(*)>(_a[2]))); break;
        case 4: _t->itemsChanged((*reinterpret_cast< bb::cascades::DataModelChangeType::Type(*)>(_a[1]))); break;
        case 5: _t->itemsChanged(); break;
        case 6: _t->sourceChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: { int _r = _t->childCount((*reinterpret_cast< const QVariantList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->hasChildren((*reinterpret_cast< const QVariantList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { QString _r = _t->itemType((*reinterpret_cast< const QVariantList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: { QVariant _r = _t->data((*reinterpret_cast< const QVariantList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->source();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: _t->setSource((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: { bool _r = _t->insert_item((*reinterpret_cast< const QVariantMap(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { bool _r = _t->delete_item((*reinterpret_cast< QVariantList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ABDataModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ABDataModel::staticMetaObject = {
    { &bb::cascades::DataModel::staticMetaObject, qt_meta_stringdata_ABDataModel,
      qt_meta_data_ABDataModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ABDataModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ABDataModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ABDataModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ABDataModel))
        return static_cast<void*>(const_cast< ABDataModel*>(this));
    typedef bb::cascades::DataModel QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int ABDataModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef bb::cascades::DataModel QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = source(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setSource(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ABDataModel::itemAdded(QVariantList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ABDataModel::itemRemoved(QVariantList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ABDataModel::itemUpdated(QVariantList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ABDataModel::itemsChanged(bb::cascades::DataModelChangeType::Type _t1, QSharedPointer<bb::cascades::DataModel::IndexMapper> _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 6
void ABDataModel::sourceChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
