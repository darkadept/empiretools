#include "skillcontroller.h"

#include "database/orm.h"

SkillController::SkillController(QObject *parent) :
    QObject(parent)
{
}

void SkillController::createSkill() {
    DataObject *object = REPOSITORY("Skill")->createObject();
}
