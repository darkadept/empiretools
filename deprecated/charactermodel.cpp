#include "charactermodel.h"

#include "character.h"

const QString characterModelSqlSelect = "SELECT id,name,soak,woundThreshold,woundCurrent,strainThreshold,strainCurrent,defenseRanged,defenseMelee,brawn,agility,intellect,cunning,willpower,presence,skills,talents FROM characters";

CharacterModel::CharacterModel() :
    Repository(characterModelSqlSelect, 0)
{
}

CharacterModel::~CharacterModel() {
}

int CharacterModel::columnCount(const QModelIndex &/*parent*/) const {
    return 2;
}

QVariant CharacterModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) return QVariant();

    Player *p = fetchByRow<Player>(index.row());
    switch (index.column()) {
    case 0:
        return p->id();
    case 1:
        return p->name();
    default:
        return QVariant();
    }
}

QVariant CharacterModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return QVariant();
    if (section < 0 && section >= columnCount()) return QVariant();

    switch(section) {
    case 0:
        return tr("Id");
    case 1:
        return tr("Name");
    default:
        return QVariant();
    }
}

Qt::ItemFlags CharacterModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

DataObject *CharacterModel::objectFactory(const QUuid &id) {
    Player *p = new Player(id, this);
    return p;
}

void CharacterModel::dbInsert(DataObject *obj, QSqlQuery *q) {
    Character *p = qobject_cast<Character*>(obj);
    q->prepare("INSERT INTO characters ("
               "id,"
               "name,"
               "soak,"
               "woundThreshold,"
               "woundCurrent,"
               "strainThreshold,"
               "strainCurrent,"
               "defenseRanged,"
               "defenseMelee,"
               "brawn,"
               "agility,"
               "intellect,"
               "cunning,"
               "willpower,"
               "presence,"
               "skills,"
               "talents) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    q->addBindValue(p->id());
    q->addBindValue(p->name());
    q->addBindValue(p->soak());
    q->addBindValue(p->woundThreshold());
    q->addBindValue(p->woundCurrent());
    q->addBindValue(p->strainThreshold());
    q->addBindValue(p->strainCurrent());
    q->addBindValue(p->defenseRanged());
    q->addBindValue(p->defenseMelee());
    q->addBindValue(p->brawn());
    q->addBindValue(p->agility());
    q->addBindValue(p->intellect());
    q->addBindValue(p->cunning());
    q->addBindValue(p->willpower());
    q->addBindValue(p->presence());

    q->addBindValue(QVariant());
    q->addBindValue(QVariant());
}

void CharacterModel::dbUpdate(DataObject *obj, QSqlQuery *q) {
    Character *p = qobject_cast<Character*>(obj);
    q->prepare("UPDATE characters SET "
              "name=?,"
              "soak=?,"
              "woundThreshold=?,"
              "woundCurrent=?,"
              "strainThreshold=?,"
              "strainCurrent=?,"
              "defenseRanged=?,"
              "defenseMelee=?,"
              "brawn=?,"
              "agility=?,"
              "intellect=?,"
              "cunning=?,"
              "willpower=?,"
              "presence=?,"
              "skills=?,"
              "talents=? WHERE id = ?");
    q->addBindValue(p->name());
    q->addBindValue(p->soak());
    q->addBindValue(p->woundThreshold());
    q->addBindValue(p->woundCurrent());
    q->addBindValue(p->strainThreshold());
    q->addBindValue(p->strainCurrent());
    q->addBindValue(p->defenseRanged());
    q->addBindValue(p->defenseMelee());
    q->addBindValue(p->brawn());
    q->addBindValue(p->agility());
    q->addBindValue(p->intellect());
    q->addBindValue(p->cunning());
    q->addBindValue(p->willpower());
    q->addBindValue(p->presence());

    q->addBindValue(QVariant());
    q->addBindValue(QVariant());
    q->addBindValue(p->id().toString());
}

void CharacterModel::dbDelete(const QUuid &id, QSqlQuery *q) {
    q->prepare("DELETE FROM characters WHERE id = ?");
    q->addBindValue(id);
}

void CharacterModel::dbLoad(DataObject *obj, QSqlQuery *q) {
    Character *p = qobject_cast<Character*>(obj);
    p->setName(q->value(1).toString());
    p->setSoak(q->value(2).toInt());
    p->setWoundThreshold(q->value(3).toInt());
    p->setWoundCurrent(q->value(4).toInt());
    p->setStrainThreshold(q->value(5).toInt());
    p->setStrainCurrent(q->value(6).toInt());
    p->setDefenseRanged(q->value(7).toInt());
    p->setDefenseMelee(q->value(8).toInt());
    p->setBrawn(q->value(9).toInt());
    p->setAgility(q->value(10).toInt());
    p->setIntellect(q->value(11).toInt());
    p->setCunning(q->value(12).toInt());
    p->setWillpower(q->value(13).toInt());
    p->setPresence(q->value(14).toInt());
}
