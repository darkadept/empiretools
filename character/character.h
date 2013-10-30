#ifndef PLAYER_H
#define PLAYER_H

#include "database/dataobject.h"
//#include <QDataStream>
//#include "skills/skill.h"

//class CharacterSkill2 {
//public:
//    explicit CharacterSkill2();
//    Skill *skill;
//    bool isCareer;
//    int rank;
//};
//QDataStream &operator<<(QDataStream &out, const PlayerSkill2 &skill);
//QDataStream &operator>>(QDataStream &in, PlayerSkill2 &skill);

/*
class CharacterSkill {
public:
    enum SkillBase { None = 0, Brawn = 1, Agility = 2, Intellect = 3, Cunning = 4, Willpower = 5, Presence = 6 };
    enum SkillCategory { GeneralSkills = 0, CombatSkills = 1, KnowledgeSkills = 2 };

    QString skill;
    int base;
    bool isCareer;
    int rank;
    int category;
};
QDataStream &operator<<(QDataStream &out, const CharacterSkill &skill);
QDataStream &operator>>(QDataStream &in, CharacterSkill &skill);
*/

/*
class CharacterTalent {
public:
    enum TalentActivation { Passive = 0, ActiveIncidental = 1, ActiveAction = 2, ActiveManeuver = 3 };

    QString talent;
    int activation;
    bool isRanked;
};
QDataStream &operator<<(QDataStream &out, const CharacterTalent &talent);
QDataStream &operator>>(QDataStream &in, CharacterTalent &talent);
*/

class Character : public DataObject
{
    Q_OBJECT

    // General
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString career READ career WRITE setCareer)
    Q_PROPERTY(QString specialization READ specialization WRITE setSpecialization)
    Q_PROPERTY(QString species READ species WRITE setSpecies)
    Q_PROPERTY(QString faction READ faction WRITE setFaction)
    Q_PROPERTY(CharacterType type READ type WRITE setType)

    // Condition
    Q_PROPERTY(int soak READ soak WRITE setSoak)
    Q_PROPERTY(int woundThreshold READ woundThreshold WRITE setWoundThreshold)
    Q_PROPERTY(int woundCurrent READ woundCurrent WRITE setWoundCurrent)
    Q_PROPERTY(int strainThreshold READ strainThreshold WRITE setStrainThreshold)
    Q_PROPERTY(int strainCurrent READ strainCurrent WRITE setStrainCurrent)
    Q_PROPERTY(int defenseRanged READ defenseRanged WRITE setDefenseRanged)
    Q_PROPERTY(int defenseMelee READ defenseMelee WRITE setDefenseMelee)

    // Characteristics
    Q_PROPERTY(int brawn READ brawn WRITE setBrawn)
    Q_PROPERTY(int agility READ agility WRITE setAgility)
    Q_PROPERTY(int intellect READ intellect WRITE setIntellect)
    Q_PROPERTY(int cunning READ cunning WRITE setCunning)
    Q_PROPERTY(int willpower READ willpower WRITE setWillpower)
    Q_PROPERTY(int presence READ presence WRITE setPresence)

    Q_ENUMS(CharacterType)

public:
    enum CharacterType { PC = 0, Minion = 1, Rival = 2, Nemesis = 3 };

    Q_INVOKABLE explicit Character(const QUuid &id = QUuid(), QObject *parent = 0);
    ~Character();

    // General
    QString name() const;
    void setName(const QString &name);
    QString career() const;
    void setCareer(const QString &career);
    QString specialization() const;
    void setSpecialization(const QString &specialization);
    QString species() const;
    void setSpecies(const QString &species);
    QString faction() const;
    void setFaction(const QString &faction);
    Character::CharacterType type() const;
    void setType(Character::CharacterType type);

    // Condition
    int soak() const;
    void setSoak(int);
    int woundThreshold() const;
    void setWoundThreshold(int);
    int woundCurrent() const;
    void setWoundCurrent(int);
    int strainThreshold() const;
    void setStrainThreshold(int);
    int strainCurrent() const;
    void setStrainCurrent(int);
    int defenseRanged() const;
    void setDefenseRanged(int);
    int defenseMelee() const;
    void setDefenseMelee(int);

    // Characteristics
    int brawn() const;
    void setBrawn(int);
    int agility() const;
    void setAgility(int);
    int intellect() const;
    void setIntellect(int);
    int cunning() const;
    void setCunning(int);
    int willpower() const;
    void setWillpower(int);
    int presence() const;
    void setPresence(int);

    // Skills
//    void setSkills(const QList<CharacterSkill> &skills);
//    void addSkill(const QString &skill, int base, bool isCareer, int rank, int category);
//    void addSkill(const CharacterSkill &skill);
//    void updateSkill(const QString &skill, int rank);
//    void updateSkill(const QString &skill, bool isCareer);
//    void deleteSkill(const QString &skill);
//    CharacterSkill skill(const QString &skill) const;
//    QList<CharacterSkill> skills() const;
//    QList<CharacterSkill> skills(int category) const;

    // Talents
//    void setTalents(const QList<CharacterTalent> &talents);
//    void addTalent(const QString &talent, int activation, bool isRanked);
//    void addTalent(const CharacterTalent &talent);
//    void updateTalent(const QString &talent);
//    void deleteTalent(const QString &talent);
//    CharacterTalent talent(const QString &talent) const;
//    QList<CharacterTalent> talents() const;

//protected:
//    virtual void buildMd5();

private:
    class CharacterPrivate &d;
};

#endif // PLAYER_H
