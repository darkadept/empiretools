#ifndef SKILLMODEL_H
#define SKILLMODEL_H

#include "database/repository.h"
#include "skill.h"

class SkillModel : public Repository
{
    Q_OBJECT
public:
    /**
     * @brief instance
     * @return Singleton instance of SkillModel
     */
    static SkillModel* instance() {
        static SkillModel instance;
        return &instance;
    }

    ~SkillModel();
    
    //QAbstractTableModel
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

protected:
    //DataObject
    virtual DataObject *objectFactory(const QUuid &id = QUuid());
    virtual void dbInsert(DataObject* obj, QSqlQuery *query);
    virtual void dbUpdate(DataObject* obj, QSqlQuery *query);
    virtual void dbDelete(const QUuid &id, QSqlQuery *query);
    virtual void dbLoad(DataObject* object, QSqlQuery *query);
    
private:
    SkillModel();
    SkillModel(SkillModel const &);
    void operator=(SkillModel const&);
};

#endif // SKILLMODEL_H
