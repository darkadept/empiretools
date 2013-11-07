#include "skillsdockwidget.h"
#include "ui_skillsdockwidget.h"

#include <QDebug>
#include <QSortFilterProxyModel>
#include <QSet>
#include <QToolBar>
#include <QGridLayout>
#include <QIcon>
#include <QLine>
#include "database/orm.h"

class SkillsDockWidgetPrivate {
public:
    QSortFilterProxyModel *model;
    QToolBar *toolBar;
    Repository *repo;
};

SkillsDockWidget::SkillsDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::SkillsDockWidget),
    d(*new SkillsDockWidgetPrivate)
{
    ui->setupUi(this);

    //Find the Repository
    d.repo = Orm::instance()->repository("Skill");
    Q_ASSERT(d.repo);

    //Set up the filter model
    d.model = new QSortFilterProxyModel(this);
    d.model->setSourceModel(d.repo);
    d.model->setFilterKeyColumn(d.repo->column("name"));
    d.model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    connect(ui->filterLine, SIGNAL(textChanged(QString)), d.model, SLOT(setFilterFixedString(QString)));
    connect(ui->filterLine, SIGNAL(textChanged(QString)), ui->skillsTable, SLOT(resizeRowsToContents()));

    //Set up the skills list table
    QSet<int> visibleColumns = QSet<int>() << d.repo->column("name") << d.repo->column("base");
    ui->skillsTable->setModel(d.model);
    for (int i=0; i<d.repo->columnCount(); ++i) {
        if (!visibleColumns.contains(i))
            ui->skillsTable->hideColumn(i);
    }
    ui->skillsTable->resizeRowsToContents();
//    connect(ui->skillsTable->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SIGNAL(emitSkillSelected(QModelIndex)));

    d.toolBar = new QToolBar(this);
    d.toolBar->setIconSize(QSize(16,16));
    d.toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d.toolBar->setMovable(false);
    ui->toolbarLayout->insertWidget(0, d.toolBar);

//    d.toolBar->addAction(QIcon(":/icons/icons/add.png"), tr("New"), this, SIGNAL(skillCreateClicked()));
//    d.toolBar->addAction(QIcon(":/icons/icons/remove.png"), tr("Delete"), this, SLOT(emitSkillRemoveClicked(QModelIndex)));
}

SkillsDockWidget::~SkillsDockWidget()
{
    delete ui;
    delete &d;
}

void SkillsDockWidget::selectSkill(const QModelIndex &index) {
    ui->skillsTable->setCurrentIndex(d.model->mapFromSource(index));
}

void SkillsDockWidget::emitSkillSelected(const QModelIndex &index) {
    emit skillSelected(d.model->mapToSource(index));
}

void SkillsDockWidget::emitSkillRemoveClicked(const QModelIndex &index) {
    emit skillRemoveClicked(d.model->mapToSource(index));
}

//void SkillsDockWidget::addNewSkill() {
//    DataObject *object = d.repo->createObject();
//    int row = d.repo->indexOf(object).row();
//    ui->skillsTable->selectRow(row);
//    ui->skillsTable->resizeRowToContents(row);
//}

//void SkillsDockWidget::removeSelectedSkill() {
//    d.repo->remove(ui->skillsTable->currentIndex());
//    d.repo->submit();
//}
