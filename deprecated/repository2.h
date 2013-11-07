#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QAbstractTableModel>
#include <QList>
#include <QUuid>
#include <QSqlQuery>
#include "dataobject.h"

class Repository : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit Repository(const QString &sqlSelect, QObject *parent = 0);
    virtual ~Repository();

    // DataObject methods
    QList<DataObject*> allObjects() const;
    DataObject *fetchObject(const QUuid &id) const;
    DataObject *fetchObject(int row) const;
    DataObject *fetchObject(const QModelIndex &index) const;

    // Type methods
    template<class T> T* create();
    template<class T> QList<T*> fetchAll() const;
    template<class T> T* fetchById(const QUuid &id) const;
    template<class T> T* fetchByRow(int row) const;

    QModelIndex indexOf(DataObject *obj) const;
    int count() const;

    // QAbstractTableModel methods
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

public slots:
    DataObject *createObject();
    void remove(DataObject *obj);
    void remove(const QModelIndex &index);
    virtual bool submit();
    void load();

protected:
    // Virtual methods
    virtual DataObject* objectFactory(const QUuid &id = QUuid()) = 0;
    virtual void dbInsert(DataObject* object, QSqlQuery *query) = 0;
    virtual void dbUpdate(DataObject* object, QSqlQuery *query) = 0;
    virtual void dbDelete(const QUuid &id, QSqlQuery *query) = 0;
    virtual void dbLoad(DataObject* object, QSqlQuery *query) = 0;

private:
    class RepositoryPrivate &d;
};

template<class T>
T* Repository::create() {
    return qobject_cast<T*>(createObject());
}

template<class T>
QList<T*> Repository::fetchAll() const {
    QList<DataObject*> srcList = allObjects();
    QList<T*> retList;
    for (int i=0; i<srcList.count(); ++i) {
        retList.append(qobject_cast<T*>(srcList.at(i)));
    }
    return retList;
}

template<class T>
T* Repository::fetchById(const QUuid &id) const {
    return qobject_cast<T*>(fetchObject(id));
}

template<class T>
T* Repository::fetchByRow(int row) const {
    return qobject_cast<T*>(fetchObject(row));
}

#endif // REPOSITORY_H
