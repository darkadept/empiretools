#include "skillview.h"

#include "skillsdockwidget.h"
#include "skilledit.h"

class SkillViewPrivate {
public:
    SkillsDockWidget *dockWidget;
    SkillEdit *skillEdit;
    QWidget *widget;
};

SkillView::SkillView(QObject *parent) :
    QObject(parent),
    d(*new SkillViewPrivate)
{
    d.dockWidget = new SkillsDockWidget;
    d.skillEdit = new SkillEdit;
}

SkillView::~SkillView() {
    delete &d;
}

QWidget* SkillView::mainWidget() {
    return d.skillEdit;
}

QList<QDockWidget*> SkillView::dockWidgets() {
    return QList<QDockWidget*>() << d.dockWidget;
}
