#include "skill.h"

#include <QString>
#include <QMetaProperty>

class SkillPrivate {
public:
    QString name;
    Skill::SkillBase base;
    Skill::SkillCategory category;
    QString description;
    QString dieResults;
    int rulesPage;
};

Skill::Skill(const QUuid &id, QObject *parent) :
    DataObject(id, parent),
    d(*new SkillPrivate)
{
    d.base = Skill::NoBase;
    d.category = Skill::General;
    d.rulesPage = 0;
}

Skill::~Skill() {
    delete &d;
}

QString Skill::name() const { return d.name; }
void Skill::setName(const QString &name) { d.name = name; setObjectName(name); }
Skill::SkillBase Skill::base() const { return d.base; }
void Skill::setBase(Skill::SkillBase base) { d.base = base; }
Skill::SkillCategory Skill::category() const { return d.category; }
void Skill::setCategory(Skill::SkillCategory category) { d.category = category; }
QString Skill::description() const { return d.description; }
void Skill::setDescription(const QString &description) { d.description = description; }
QString Skill::dieResults() const { return d.dieResults; }
void Skill::setDieResults(const QString &dieResults) { d.dieResults = dieResults; }
int Skill::rulesPage() const { return d.rulesPage; }
void Skill::setRulesPage(int page) { d.rulesPage = page; }

//void Skill::buildMd5() {
//    clearMd5();
//    addToMd5(d.name.toLatin1());
//    QByteArray v;
//    QDataStream vs(&v, QIODevice::WriteOnly);
//    vs << d.base << d.category << d.description.toLatin1() << d.dieResults.toLatin1() << d.rulesPage;
//    addToMd5(v);
//}
