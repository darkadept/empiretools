#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "database/repository.h"

class CharacterModel : public Repository
{
    Q_OBJECT
public:
    static CharacterModel* instance() {
        static CharacterModel instance;
        return &instance;
    }
    ~CharacterModel();

    //QAbstractTableModel
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

protected:
    virtual DataObject *objectFactory(const QUuid &id = QUuid());
    virtual void dbInsert(DataObject* obj, QSqlQuery *query);
    virtual void dbUpdate(DataObject* obj, QSqlQuery *query);
    virtual void dbDelete(const QUuid &id, QSqlQuery *query);
    virtual void dbLoad(DataObject* object, QSqlQuery *query);

private:
    CharacterModel();
    CharacterModel(CharacterModel const &);
    void operator=(CharacterModel const&);
};



#endif // PLAYERMODEL_H
