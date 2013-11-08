#ifndef SKILLCONTROLLER_H
#define SKILLCONTROLLER_H

#include <QObject>

class SkillController : public QObject
{
    Q_OBJECT
public:
    explicit SkillController(QObject *parent = 0);

public slots:
    void createSkill();

};

#endif // SKILLCONTROLLER_H
