#include "skillview.h"
#include "ui_skillview.h"

SkillView::SkillView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkillView)
{
    ui->setupUi(this);
}

SkillView::~SkillView()
{
    delete ui;
}

QWidget *SkillView::mainWidget() {
    //Return self
    return this;
}

QList<QDockWidget*> SkillView::dockWidgets() {
    //Return no dock widgets
    return QList<QDockWidget*>();
}
