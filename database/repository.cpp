#include "repository.h"

#include <QList>
#include <QHash>
#include <QSet>
#include <QUuid>
#include <QMetaProperty>
#include <QCryptographicHash>
#include <QDataStream>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "databridge.h"
#include "orm.h"

class RepositoryPrivate {
public:
    QMetaObject meta;
    DataBridge *dataBridge;

    QList<DataObject*> objects;         // List of active DataObjects (in row order)
    QHash<QUuid, DataObject*> idIndex;  // Hash of DataObjects by ID
    QSet<QUuid> idsToRemove;            // Set of ID's to remove from the repository/database
    QSet<QUuid> idsToAdd;               // Set of ID's to add to the database
    QHash<DataObject*, QByteArray> md5; // Hash of MD5's by DataObject

    //Static variables
    int columnCount;
    QHash<QString, int> columnsHash;
};

Repository::Repository(const QMetaObject &meta, QObject *parent) :
    QAbstractTableModel(parent),
    d(*new RepositoryPrivate)
{
    d.meta = meta; //store metaojbect information

    // Calculate static variables
    d.columnCount = d.meta.propertyCount() - d.meta.propertyOffset() + 1; //+1 for ID field
    d.columnsHash.insert("id", 0);
    int n=1;
    for (int i=d.meta.propertyOffset(); i<d.meta.propertyCount(); ++i) {
        QString propName(d.meta.property(i).name());
        d.columnsHash.insert(propName.toLower(), n);
        ++n;
    }

    d.dataBridge = new DataBridge(d.meta, this);
}

Repository::~Repository() {
    delete &d;
}

/**
 * @brief Repository::createObject
 * @return
 * Creates an object of this Repository's type.
 */
DataObject* Repository::createObject() {
    beginInsertRows(QModelIndex(), d.objects.count(), d.objects.count());

    //Attempt to create the object
    DataObject *object = qobject_cast<DataObject*>(d.meta.newInstance());
    if (!object) return 0;

    qDebug() << "Created object" << object->objectName() << "[" << d.meta.className() << "]" << object->id();

    //Add the object to the store
    d.objects.append(object);
    d.idIndex.insert(object->id(), object);
    d.idsToAdd << object->id();
    updateMd5(object);

    endInsertRows();
    return object;
}

/**
 * @brief Repository::allObjects
 * @return A list of all of the DataObject's.
 */
QList<DataObject *> Repository::allObjects() const {
    return d.objects;
}

/**
 * @brief Repository::fetchObject
 * @param id
 * @return The object with the specific id or null if not found.
 */
DataObject *Repository::fetchObject(const QUuid &id) const {
    if (d.idIndex.contains(id)) return d.idIndex.value(id);
    return 0;
}

/**
 * @brief Repository::fetchObject
 * @param row
 * @return The object by row index.
 */
DataObject* Repository::fetchObject(int row) const {
    if (row<d.objects.count()) return d.objects.at((row));
    return 0;
}

/**
 * @brief Repository::fetchObject
 * @param index
 * @return The object located at the specific index or null if not valid.
 */
DataObject *Repository::fetchObject(const QModelIndex &index) const {
    if (index.isValid())
        return fetchObject(index.row());
    return 0;
}

/**
 * @brief Repository::remove
 * @param obj
 * Removes an object from the Repository.
 */
void Repository::remove(DataObject *obj) {
    if (d.objects.contains(obj)) {
        int row = d.objects.indexOf(obj);
        beginRemoveRows(QModelIndex(), row, row);
        if (d.idsToAdd.contains(obj->id())) {
            d.idsToAdd.remove(obj->id());
        } else {
            d.idsToRemove.insert(obj->id());
        }
        d.objects.removeAt(row);
        d.idIndex.remove(obj->id());
        delete obj;
        endRemoveRows();
    }
}

/**
 * @brief Repository::remove
 * @param index
 * Removes an object at the specified index.
 */
void Repository::remove(const QModelIndex &index) {
    if (!index.isValid()) return;
    remove(d.objects.at(index.row()));
}

/**
 * @brief Repository::load
 * Loads all data into the Repository from the database.
 */
void Repository::load() {
    beginResetModel();
    QSqlQuery q(d.dataBridge->sqlSelect());
    while (q.next()) {
        QUuid id(q.value(0).toString());
        DataObject *obj = qobject_cast<DataObject*>(d.meta.newInstance(Q_ARG(QUuid, id)));
        d.dataBridge->dbLoad(obj, &q);
        updateMd5(obj);
        d.objects.append(obj);
        d.idIndex.insert(obj->id(), obj);
        qDebug() << "Loaded:" << obj->objectName() << "[" << d.meta.className() << "]" << obj->id();
    }
    endResetModel();
}

/**
 * @brief Repository::submit
 * @return
 * Submits changes objects to the database.
 */
bool Repository::submit() {
    // Adds new objects to the database.
    foreach (const QUuid &id, d.idsToAdd) {
        DataObject *obj = d.idIndex.value(id);
        QSqlQuery q;
        d.dataBridge->dbInsert(obj, &q);
        qDebug() << "Adding to DB:" << obj->objectName() << "[" << d.meta.className() << "]" << id.toString();
        if (!q.exec()) {
            qDebug() << q.lastError().text();
        }
        d.idsToAdd.remove(id);
        if (objectIsChanged(obj)) {
            updateMd5(obj);
            int row = d.objects.indexOf(obj);
            emit dataChanged(index(row,0), index(row,columnCount()-1));
        }
    }

    // Updates changed objects.
    foreach (DataObject* obj, d.objects) {
        if (objectIsChanged(obj)) {
            updateMd5(obj);
            QSqlQuery q;
            d.dataBridge->dbUpdate(obj, &q);
            qDebug() << "Updating DB:" << obj->objectName() << "[" << d.meta.className() << "]" << obj->id().toString();
            if (!q.exec()) {
                qDebug() << q.lastError().text();
            }
            int row = d.objects.indexOf(obj);
            emit dataChanged(index(row,0), index(row,columnCount()-1));
        }
    }

    // Removes deleted objects.
    foreach (const QUuid &id, d.idsToRemove) {
        QSqlQuery q;
        d.dataBridge->dbDelete(id, &q);
        qDebug() << "Removing from DB:" << "[" << d.meta.className() << "]" << id.toString();
        if (!q.exec()) {
            qDebug() << q.lastError().text();
        }
    }
    d.idsToRemove.clear();

    return true;
}

/**
 * @brief Repository::indexOf
 * @param obj
 * @return The index of the object.
 */
QModelIndex Repository::indexOf(DataObject *obj) const {
    if (!d.objects.contains(obj)) return QModelIndex();
    return index(d.objects.indexOf(obj), 0);
}

int Repository::column(const QString &name) const {
    if (d.columnsHash.contains(name.toLower()))
        return d.columnsHash.value(name.toLower());
    return -1;
}

/**
 * @brief Repository::rowCount
 * @return The number of objects loaded in the repository
 */
int Repository::rowCount(const QModelIndex &/*parent*/) const {
    return d.objects.count();
}

/**
 * @brief Repository::columnCount
 * @return The number of columns in this table (including ID)
 */
int Repository::columnCount(const QModelIndex &/*parent*/) const {
    return d.columnCount;
}

/**
 * @brief Repository::data
 * @param index
 * @param role
 * @return The data value at the specified index.
 */
QVariant Repository::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    DataObject *obj = fetchObject(index);
    QMetaProperty property = d.meta.property(d.meta.propertyOffset() - 1 + index.column());
    QVariant value = property.read(obj);

    if (role == Qt::DisplayRole) {
        if (property.isEnumType()) {
            value = Orm::instance()->metaEnum(property.typeName()).valueToKey(value.toInt());
        }
    } else if (role == Qt::EditRole) {

    } else {
        value = QVariant();
    }

    return value;
}

QVariant Repository::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return QVariant();
    if (section < 0 && section >= columnCount()) return QVariant();

    QMetaProperty property = d.meta.property(d.meta.propertyOffset() - 1 + section);
    QString name(property.name());
    name = name.left(1).toUpper() + name.mid(1).toLower();
    return QVariant(name);
}

Qt::ItemFlags Repository::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::NoItemFlags;

    if (index.column() == 0) return QAbstractTableModel::flags(index);
    return (QAbstractTableModel::flags(index) | Qt::ItemIsEditable);
}

bool Repository::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid()) return false;
    if (role != Qt::EditRole) return false;

    DataObject *obj = fetchObject(index);
    QMetaProperty property = d.meta.property(d.meta.propertyOffset() - 1 + index.column());
    bool worked = property.write(obj, value);
    Q_ASSERT(worked);

    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

/**
 * @brief Repository::md5
 * @param object
 * @return
 * Generate the MD5 of the object
 */
QByteArray Repository::md5(DataObject *object) const {
    QByteArray byteArray;
    QDataStream dataStream(&byteArray, QIODevice::WriteOnly);

    //Iterate over properties
    for (int i=d.meta.propertyOffset(); i<d.meta.propertyCount(); ++i) {
        QMetaProperty property = d.meta.property(i);
        QVariant value = property.read(object);
        dataStream << value;
    }

    //Generate md5
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(byteArray);
    return hash.result();
}

/**
 * @brief Repository::updateMd5
 * @param object
 * Update the stored value of the MD5
 */
void Repository::updateMd5(DataObject *object) const {
    d.md5.insert(object, md5(object));
}

/**
 * @brief Repository::objectIsChanged
 * @param object
 * @return True if the object has changed, otherwise false.
 */
bool Repository::objectIsChanged(DataObject *object) const {
    return (d.md5.value(object) != md5(object));
}
