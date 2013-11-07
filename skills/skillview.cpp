#include "skillview.h"

#include <QDockWidget>
//#include "skillsdockwidget.h"
//#include "skilledit.h"

class SkillViewPrivate {
public:
//    SkillsDockWidget *dockWidget;
//    SkillEdit *skillEdit;
    QWidget *widget;
};

SkillView::SkillView(QObject *parent) :
    QObject(parent),
    d(*new SkillViewPrivate)
{
//    d.dockWidget = new SkillsDockWidget;
//    d.skillEdit = new SkillEdit;
    d.widget = new QWidget;
}

SkillView::~SkillView() {
    delete &d;
}

QWidget* SkillView::mainWidget() {
    //return d.skillEdit;
    return d.widget;
}

QList<QDockWidget*> SkillView::dockWidgets() {
    return QList<QDockWidget*>(); // << d.dockWidget;
}
