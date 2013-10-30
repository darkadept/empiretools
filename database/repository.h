#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QAbstractTableModel>
#include <QByteArray>
#include "dataobject.h"

class Repository : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit Repository(const QMetaObject &meta, QObject *parent = 0);
    ~Repository();

    // Create methods
    template<class T> T* create();
    DataObject *createObject();

    // Select methods
    template<class T> QList<T*> fetchAll() const;
    template<class T> T* fetchById(const QUuid &id) const;
    template<class T> T* fetchByRow(int row) const;
    QList<DataObject*> allObjects() const;
    DataObject *fetchObject(const QUuid &id) const;
    DataObject *fetchObject(int row) const;
    DataObject *fetchObject(const QModelIndex &index) const;

    // Deletion methods
    void remove(const QModelIndex &index);
    void remove(DataObject *obj);

    // Other
    void load();
    virtual bool submit();
    QModelIndex indexOf(DataObject *obj) const;    
    int column(const QString &name) const;

    //QAbstractTableModel methods
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    QByteArray md5(DataObject *object) const;
    void updateMd5(DataObject *object) const;
    bool objectIsChanged(DataObject *object) const;

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
