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
    QToolBar *toolBar;
};

SkillsDockWidget::SkillsDockWidget(QSortFilterProxyModel *model, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::SkillsDockWidget),
    d(*new SkillsDockWidgetPrivate)
{
    ui->setupUi(this);

    //Find the Repository
    Repository *repo = REPOSITORY("Skill");
    Q_ASSERT(repo);

    connect(ui->filterLine, SIGNAL(textChanged(QString)), model, SLOT(setFilterFixedString(QString)));
    connect(ui->filterLine, SIGNAL(textChanged(QString)), ui->skillsTable, SLOT(resizeRowsToContents()));

    //Set up the skills list table
    QSet<int> visibleColumns = QSet<int>() << repo->column("name") << repo->column("base");
    ui->skillsTable->setModel(model);
    for (int i=0; i<repo->columnCount(); ++i) {
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

    d.toolBar->addAction(QIcon(":/icons/icons/add.png"), tr("New"), this, SIGNAL(skillCreateClicked()));
    d.toolBar->addAction(QIcon(":/icons/icons/remove.png"), tr("Delete"), this, SLOT(emitSkillRemoveClicked()));
}

SkillsDockWidget::~SkillsDockWidget()
{
    delete ui;
    delete &d;
}

//void SkillsDockWidget::selectSkill(const QModelIndex &index) {
//    ui->skillsTable->setCurrentIndex(d.model->mapFromSource(index));
//}

//void SkillsDockWidget::emitSkillSelected(const QModelIndex &index) {
//    emit skillSelected(d.model->mapToSource(index));
//}

void SkillsDockWidget::emitSkillRemoveClicked() {
    emit skillRemoveClicked(ui->skillsTable->selectionModel()->currentIndex());
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
