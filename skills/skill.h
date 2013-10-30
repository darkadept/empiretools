#ifndef SKILL_H
#define SKILL_H

#include "database/dataobject.h"

class Skill : public DataObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(SkillBase base READ base WRITE setBase)
    Q_PROPERTY(SkillCategory category READ category WRITE setCategory)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(QString dieResults READ dieResults WRITE setDieResults)
    Q_PROPERTY(int rulesPage READ rulesPage WRITE setRulesPage)

    Q_CLASSINFO("description", "VARCHAR(512) NULL")
    Q_CLASSINFO("dieResults", "VARCHAR(512) NULL")

    Q_ENUMS(SkillBase)
    Q_ENUMS(SkillCategory)

public:
    enum SkillBase { NoBase = 0, Brawn = 1, Agility = 2, Intellect = 3, Cunning = 4, Willpower = 5, Presence = 6 };
    enum SkillCategory { General = 0, Combat = 1, Knowledge = 2 };

    Q_INVOKABLE explicit Skill(const QUuid &id = QUuid(), QObject *parent = 0);
    ~Skill();

    QString name() const;
    void setName(const QString &name);
    Skill::SkillBase base() const;
    void setBase(SkillBase base);
    SkillCategory category() const;
    void setCategory(SkillCategory category);
    QString description() const;
    void setDescription(const QString &description);
    QString dieResults() const;
    void setDieResults(const QString &dieResults);
    int rulesPage() const;
    void setRulesPage(int page);

//protected:
//    virtual void buildMd5();
    
private:
    class SkillPrivate &d;
};

#endif // SKILL_H
