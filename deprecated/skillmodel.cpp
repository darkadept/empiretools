#include "skillmodel.h"

#include "skill.h"
#include <QDebug>

const QString skillModelSqlSelect = "SELECT id,name,base,category,description,dieResults,rulesPage FROM skills";

SkillModel::SkillModel() :
    Repository(skillModelSqlSelect, 0)
{
}

SkillModel::~SkillModel() { }

DataObject *SkillModel::objectFactory(const QUuid &id) {
    Skill *skill = new Skill(id, this);
    return skill;
}

void SkillModel::dbInsert(DataObject *obj, QSqlQuery *q) {
    Skill *s = qobject_cast<Skill*>(obj);
    q->prepare("INSERT INTO skills ("
              "id,"
              "name,"
              "base,"
              "category,"
              "description,"
              "dieResults,"
              "rulesPage"
              ") VALUES (?, ?, ?, ?, ?, ?, ?)");
    q->addBindValue(s->id());
    q->addBindValue(s->name());
    q->addBindValue(s->base());
    q->addBindValue(s->category());
    q->addBindValue(s->description());
    q->addBindValue(s->dieResults());
    q->addBindValue(s->rulesPage());
}

void SkillModel::dbUpdate(DataObject *obj, QSqlQuery *q) {
    Skill *s = qobject_cast<Skill*>(obj);
    q->prepare("UPDATE skills SET "
              "name=?,"
              "base=?,"
              "category=?,"
              "description=?,"
              "dieResults=?,"
              "rulesPage=?"
              " WHERE id=?");
    q->addBindValue(s->name());
    q->addBindValue(s->base());
    q->addBindValue(s->category());
    q->addBindValue(s->description());
    q->addBindValue(s->dieResults());
    q->addBindValue(s->rulesPage());
    q->addBindValue(s->id().toString());
}

void SkillModel::dbDelete(const QUuid &id, QSqlQuery *q) {
    q->prepare("DELETE FROM skills WHERE id = ?");
    q->addBindValue(id);
}

void SkillModel::dbLoad(DataObject *object, QSqlQuery *q) {
    Skill *s = qobject_cast<Skill*>(object);
    s->setName(q->value(1).toString());
    s->setBase(q->value(2).toInt());
    s->setCategory(q->value(3).toInt());
    s->setDescription(q->value(4).toString());
    s->setDieResults(q->value(5).toString());
    s->setRulesPage(q->value(6).toInt());
}

int SkillModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

QVariant SkillModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) return QVariant();

    Skill *s = fetchByRow<Skill>(index.row());
    switch (index.column()) {
    case 0:
        return s->name();
    default:
        return QVariant();
    }
}

QVariant SkillModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return QVariant();
    if (section < 0 && section >= columnCount()) return QVariant();

    switch(section) {
    case 0:
        return tr("Name");
    default:
        return QVariant();
    }
}

Qt::ItemFlags SkillModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
