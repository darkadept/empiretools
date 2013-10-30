#include "character.h"

//#include <QString>
//#include <QHash>

//CharacterSkill2::CharacterSkill2() {
//    skill = 0;
//}
//QDataStream &operator<<(QDataStream &out, const CharacterSkill2 &skill) {
//    out << skill.skill->id().toString() << skill.isCareer << skill.rank;
//    return out;
//}
//QDataStream &operator>>(QDataStream &in, CharacterSkill2 &skill) {
//    skill = CharacterSkill2();
//    QString skillId;
//    in >> skillId >> skill.isCareer >> skill.rank;
//    skill.skill = 0;
//}

/*
QDataStream &operator<<(QDataStream &out, const CharacterSkill &skill) {
    out << skill.skill << skill.base << skill.isCareer << skill.rank << skill.category;
    return out;
}
QDataStream &operator>>(QDataStream &in, CharacterSkill &skill) {
    skill = CharacterSkill();
    in >> skill.skill >> skill.base >> skill.isCareer >> skill.rank >> skill.category;
    return in;
}
*/

/*
QDataStream &operator<<(QDataStream &out, const CharacterTalent &talent) {
    out << talent.talent << talent.activation << talent.isRanked;
    return out;
}
QDataStream &operator>>(QDataStream &in, CharacterTalent &talent) {
    talent = CharacterTalent();
    in >> talent.talent >> talent.activation >> talent.isRanked;
    return in;
}
*/

class CharacterPrivate {
public:
    // General
    QString name;
    QString career;
    QString specialization;
    QString species;
    QString faction;
    Character::CharacterType type;

    // Condition
    int soak;
    int woundThreshold;
    int woundCurrent;
    int strainThreshold;
    int strainCurrent;
    int defenseRanged;
    int defenseMelee;
    QString status;

    // Characteristics
    int brawn;
    int agility;
    int intellect;
    int cunning;
    int willpower;
    int presence;

//    QHash<QString, CharacterSkill> skills;
//    QHash<QString, CharacterTalent> talents;

    CharacterPrivate() {
        type = Character::Rival;
        soak = 0;
        woundThreshold = 0;
        woundCurrent = 0;
        strainThreshold = 0;
        strainCurrent = 0;
        defenseRanged = 0;
        defenseMelee = 0;
        brawn = 0;
        agility = 0;
        intellect = 0;
        cunning = 0;
        willpower = 0;
        presence = 0;
    }
};

Character::Character(const QUuid &id, QObject *parent) :
    DataObject(id, parent),
    d(*new CharacterPrivate)
{
}

Character::~Character()
{
    delete &d;
}

// General
QString Character::name() const { return d.name; }
void Character::setName(const QString &name) { d.name = name; setObjectName(name); }
QString Character::career() const { return d.career; }
void Character::setCareer(const QString &career) { d.career = career; }
QString Character::specialization() const { return d.specialization; }
void Character::setSpecialization(const QString &specialization) { d.specialization = specialization; }
QString Character::species() const { return d.species; }
void Character::setSpecies(const QString &species) { d.species = species; }
QString Character::faction() const { return d.faction; }
void Character::setFaction(const QString &faction) { d.faction = faction; }
Character::CharacterType Character::type() const { return d.type; }
void Character::setType(CharacterType type) { d.type = type; }

// Condition
int Character::soak() const { return d.soak; }
void Character::setSoak(int v) { d.soak = v; }
int Character::woundThreshold() const { return d.woundThreshold; }
void Character::setWoundThreshold(int v) { d.woundThreshold = v; }
int Character::woundCurrent() const { return d.woundCurrent; }
void Character::setWoundCurrent(int v) { d.woundCurrent = v; }
int Character::strainThreshold() const { return d.strainThreshold; }
void Character::setStrainThreshold(int v) { d.strainThreshold = v; }
int Character::strainCurrent() const { return d.strainCurrent; }
void Character::setStrainCurrent(int v) { d.strainCurrent = v; }
int Character::defenseRanged() const { return d.defenseRanged; }
void Character::setDefenseRanged(int v) { d.defenseRanged = v; }
int Character::defenseMelee() const { return d.defenseMelee; }
void Character::setDefenseMelee(int v) { d.defenseMelee = v; }

// Characteristics
int Character::brawn() const { return d.brawn; }
void Character::setBrawn(int v) { d.brawn = v; }
int Character::agility() const { return d.agility; }
void Character::setAgility(int v) { d.agility = v; }
int Character::intellect() const { return d.intellect; }
void Character::setIntellect(int v) { d.intellect = v; }
int Character::cunning() const { return d.cunning; }
void Character::setCunning(int v) { d.cunning = v; }
int Character::willpower() const { return d.willpower; }
void Character::setWillpower(int v) { d.willpower = v; }
int Character::presence() const { return d.presence; }
void Character::setPresence(int v) { d.presence = v; }

// Skills
/*
void Character::setSkills(const QList<CharacterSkill> &skills) {
    d.skills.clear();
    foreach(const CharacterSkill &s, skills) {
        d.skills.insert(s.skill, s);
    }
}

void Character::addSkill(const QString &skill, int base, bool isCareer, int rank, int category) {
    CharacterSkill s;
    s.skill = skill;
    s.base = base;
    s.isCareer = isCareer;
    s.rank = rank;
    s.category = category;
    if (!d.skills.contains(skill)) {
        d.skills.insert(skill, s);
    }
}

void Character::addSkill(const CharacterSkill &skill) {
    if (!d.skills.contains(skill.skill)) {
        d.skills.insert(skill.skill, skill);
    }
}

void Character::updateSkill(const QString &skill, int rank) {
    if (d.skills.contains(skill)) {
        CharacterSkill s = d.skills.value(skill);
        s.rank = rank;
        d.skills.insert(skill, s);
    }
}

void Character::updateSkill(const QString &skill, bool isCareer) {
    if (d.skills.contains(skill)) {
        CharacterSkill s = d.skills.value(skill);
        s.isCareer = isCareer;
        d.skills.insert(skill, s);
    }
}

void Character::deleteSkill(const QString &skill) {
    if (d.skills.contains(skill)) {
        d.skills.remove(skill);
    }
}

CharacterSkill Character::skill(const QString &skill) const {
    if (d.skills.contains(skill)) {
        return d.skills.value(skill);
    } else {
        return CharacterSkill();
    }
}

QList<CharacterSkill> Character::skills() const {
    return d.skills.values();
}

QList<CharacterSkill> Character::skills(int category) const {
    QList<CharacterSkill> skls;
    foreach (const CharacterSkill &skill, d.skills.values()) {
        if (skill.category == category) {
            skls << skill;
        }
    }
    return skls;
}
*/


// Talents
/*
void Character::setTalents(const QList<CharacterTalent> &talents) {
    d.talents.clear();
    foreach (const CharacterTalent &talent, talents) {
        d.talents.insert(talent.talent, talent);
    }
}

void Character::addTalent(const QString &talent, int activation, bool isRanked) {
    CharacterTalent tlnt;
    tlnt.talent = talent;
    tlnt.activation = activation;
    tlnt.isRanked = isRanked;
    if (!d.talents.contains(tlnt.talent)) {
        d.talents.insert(tlnt.talent, tlnt);
    }
}

void Character::addTalent(const CharacterTalent &talent) {
    if (!d.talents.contains(talent.talent)) {
        d.talents.insert(talent.talent, talent);
    }
}

void Character::updateTalent(const QString &talent) {

}

void Character::deleteTalent(const QString &talent) {

}

CharacterTalent Character::talent(const QString &talent) const {
    if (d.talents.contains(talent)) {
        return d.talents.value(talent);
    } else {
        return CharacterTalent();
    }
}

QList<CharacterTalent> Character::talents() const {
    return d.talents.values();
}
*/


//void Character::buildMd5() {
//    clearMd5();
//    addToMd5(d.name.toLatin1());
//    QByteArray values;
//    QDataStream valueStream(&values, QIODevice::WriteOnly);
//    valueStream << d.soak << d.woundThreshold << d.woundCurrent << d.strainThreshold << d.strainCurrent <<
//                   d.defenseRanged << d.defenseMelee << d.brawn << d.agility << d.intellect << d.cunning <<
//                   d.willpower << d.presence;
////    valueStream << d.skills.values() << d.talents.values();
//    addToMd5(values);
//}

