#include "skillview.h"

#include <QSortFilterProxyModel>
#include "skillsdockwidget.h"
#include "skilledit.h"
#include "database/orm.h"

class SkillViewPrivate {
public:
    QSortFilterProxyModel *model;

    SkillsDockWidget *dockWidget;
    SkillEdit *skillEdit;
};

SkillView::SkillView(QObject *parent) :
    QObject(parent),
    d(*new SkillViewPrivate)
{
    Repository *repo = REPOSITORY("Skill");

    //Set up the filter model
    d.model = new QSortFilterProxyModel(this);
    d.model->setSourceModel(repo);
    d.model->setFilterKeyColumn(repo->column("name"));
    d.model->setFilterCaseSensitivity(Qt::CaseInsensitive);

    d.dockWidget = new SkillsDockWidget(d.model);
    d.skillEdit = new SkillEdit;

    connect(d.dockWidget, SIGNAL(skillCreateClicked()), this, SIGNAL(createSkillClicked()));
//    connect(d.dockWidget, SIGNAL(skillRemoveClicked(QModelIndex))
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
