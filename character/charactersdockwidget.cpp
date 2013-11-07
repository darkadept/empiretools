#include "charactersdockwidget.h"
#include "ui_charactersdockwidget.h"

#include <QSortFilterProxyModel>
#include "database/orm.h"

class CharactersDockWidgetPrivate {
public:
    Repository *repo;
    QSortFilterProxyModel *model;
};

CharactersDockWidget::CharactersDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::CharactersDockWidget),
    d(*new CharactersDockWidgetPrivate)
{
    ui->setupUi(this);

    //Find the Repository
    d.repo = REPOSITORY("Character");
    Q_ASSERT(d.repo);

    //Set up the filter model
    d.model = new QSortFilterProxyModel(this);
    d.model->setSourceModel(d.repo);
    d.model->setFilterKeyColumn(d.repo->column("name"));
    d.model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    connect(ui->filter, SIGNAL(textChanged(QString)), d.model, SLOT(setFilterFixedString(QString)));
    connect(ui->filter, SIGNAL(textChanged(QString)), ui->tableView, SLOT(resizeRowsToContents()));

    //Set up the skills list table
    QSet<int> visibleColumns = QSet<int>() << d.repo->column("name") << d.repo->column("faction") << d.repo->column("type");
    ui->tableView->setModel(d.model);
    for (int i=0; i<d.repo->columnCount(); ++i) {
        if (!visibleColumns.contains(i))
            ui->tableView->hideColumn(i);
    }
    ui->tableView->resizeRowsToContents();
//    connect(ui->skillsTable->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(selectSkill(QModelIndex)));

//    d.toolBar = new QToolBar(this);
//    d.toolBar->setIconSize(QSize(16,16));
//    d.toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    d.toolBar->setMovable(false);
//    ui->toolbarLayout->insertWidget(0, d.toolBar);

//    d.toolBar->addAction(QIcon(":/icons/icons/add.png"), tr("New"), this, SLOT(addNewSkill()));
//    d.toolBar->addAction(QIcon(":/icons/icons/remove.png"), tr("Delete"), this, SLOT(removeSelectedSkill()));
}

CharactersDockWidget::~CharactersDockWidget()
{
    delete ui;
    delete &d;
}
