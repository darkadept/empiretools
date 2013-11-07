#include "repository.h"

#include <QSet>
#include <QHash>
#include <QSqlError>
#include <QDebug>

class RepositoryPrivate {
public:
    QList<DataObject*> objects;
    QHash<QUuid, DataObject*> idIndex;
    QSet<QUuid> idsToRemove;
    QSet<QUuid> idsToAdd;

    QString sqlSelect;
};

Repository::Repository(const QString &sqlSelect, QObject *parent) :
    QAbstractTableModel(parent),
    d(*new RepositoryPrivate)
{
    d.sqlSelect = sqlSelect;
}

Repository::~Repository() {
    delete &d;
}

/**
 * @brief Repository::createObject
 * @return The new DataObject.
 * Creates a DataObject of this Repository's type.
 */
DataObject *Repository::createObject() {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    DataObject *object = objectFactory();
    d.objects.append(object);
    d.idIndex.insert(object->id(), object);
    d.idsToAdd << object->id();
    object->updateMd5();
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
 * @return The object located at the specific row or null if row not valid.
 */
DataObject *Repository::fetchObject(int row) const {
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
 * @brief Repository::indexOf
 * @param obj
 * @return The index of the object.
 */
QModelIndex Repository::indexOf(DataObject *obj) const {
    if (!d.objects.contains(obj)) return QModelIndex();
    return index(d.objects.indexOf(obj), 0);
}

/**
 * @brief Repository::count
 * @return
 * Alias for rowCount().
 */
int Repository::count() const {
    return rowCount();
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
 * @brief Repository::submit
 * @return
 * Submits changed, new and deleted objects to the database.
 */
bool Repository::submit() {
    // Adds new objects to the database.
    foreach (const QUuid &id, d.idsToAdd) {
        DataObject *obj = d.idIndex.value(id);
        QSqlQuery q;
        dbInsert(obj, &q);
        qDebug() << "Adding to DB:" << obj->objectName() << id.toString();
        if (!q.exec()) {
            qDebug() << q.lastError().text();
        }
        d.idsToAdd.remove(id);
        if (obj->isChanged()) {
            obj->updateMd5();
            int row = d.objects.indexOf(obj);
            emit dataChanged(index(row,0), index(row,columnCount()-1));
        }
    }

    // Updates changed objects.
    foreach (DataObject* obj, d.objects) {
        if (obj->isChanged()) {            
            obj->updateMd5();
            QSqlQuery q;
            dbUpdate(obj, &q);
            qDebug() << "Updating DB:" << obj->objectName() << obj->id().toString();
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
        dbDelete(id, &q);
        qDebug() << "Removing from DB:" << id.toString();
        if (!q.exec()) {
            qDebug() << q.lastError().text();
        }
    }
    d.idsToRemove.clear();

    return true;
}

/**
 * @brief Repository::load
 * Loads the data from the database into the Repository.
 */
void Repository::load() {
    beginResetModel();
    QSqlQuery q(d.sqlSelect);
    while (q.next()) {
        DataObject *obj = objectFactory(QUuid(q.value(0).toString())); //TODO: this isn't great. we assume the first is id
        dbLoad(obj, &q);
        obj->updateMd5();
        d.objects.append(obj);
        d.idIndex.insert(obj->id(), obj);
        qDebug() << "Loaded:" << obj->objectName() << obj->id();
    }
    endResetModel();
}

/**
 * @brief Repository::rowCount
 * @param parent
 * @return The number of rows in the Repository.
 */
int Repository::rowCount(const QModelIndex &parent) const {
    return d.objects.count();
}
