#include "skilledit.h"
#include "ui_skilledit.h"

#include <QPushButton>
#include <QMetaEnum>
#include <QDebug>
#include <QModelIndex>
#include "database/orm.h"
#include "ui/datawidgetmapper.h"
#include "skillsdockwidget.h"

class SkillEditPrivate {
public:
    QSortFilterProxyModel *model;

    DataWidgetMapper *mapper;
    SkillsDockWidget *dockWidget;
};

SkillEdit::SkillEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkillEdit),
    d(*new SkillEditPrivate)
{
    ui->setupUi(this);

    //Find repository
    Repository *repo = REPOSITORY("Skill");
    Q_ASSERT(repo);

    //Set up the filter model
    d.model = new QSortFilterProxyModel(this);
    d.model->setSourceModel(repo);
    d.model->setFilterKeyColumn(repo->column("name"));
    d.model->setFilterCaseSensitivity(Qt::CaseInsensitive);

    //Create the dock widget
    d.dockWidget = new SkillsDockWidget(d.model);


    //Configure the button box
    ui->buttonBox->setStandardButtons(QDialogButtonBox::Save | QDialogButtonBox::Cancel);

    //Add skill bases to their combobox
    QMetaEnum skillBaseEnum = ORM()->metaEnum("SkillBase");
    for (int i=0; i<skillBaseEnum.keyCount(); ++i) {
        ui->base->addItem(skillBaseEnum.key(i));
    }

    //Add skill categories to their combobox
    QMetaEnum skillCategoryEnum = ORM()->metaEnum("SkillCategory");
    for (int i=0; i<skillCategoryEnum.keyCount(); ++i) {
        ui->category->addItem(skillCategoryEnum.key(i));
    }

    //Set up the data widget mapper
    d.mapper = new DataWidgetMapper(this);
    d.mapper->setSubmitPolicy(DataWidgetMapper::ManualSubmit);
    d.mapper->setModel(repo);
    d.mapper->addMapping(ui->name, repo->column("name"));
    d.mapper->addMapping(ui->base, repo->column("base"), "currentIndex");
    d.mapper->addMapping(ui->category, repo->column("category"), "currentIndex");
    d.mapper->addMapping(ui->rulesPage, repo->column("rulesPage"));
    d.mapper->addMapping(ui->description, repo->column("description"));
    d.mapper->addMapping(ui->dieResults, repo->column("dieResults"));
    d.mapper->toFirst();
    setStateUnmodified();

    //Connect signals for un/modified data
    connect(d.mapper, SIGNAL(dataChanged()), this, SLOT(setStateModified()));

    //Connect signals for the button box
    connect(ui->buttonBox, SIGNAL(accepted()), d.mapper, SLOT(submit()));
    connect(ui->buttonBox, SIGNAL(rejected()), d.mapper, SLOT(revert()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(setStateUnmodified()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(setStateUnmodified()));
}

SkillEdit::~SkillEdit()
{
    delete ui;
    delete &d;
}

QWidget* SkillEdit::mainWidget() {
    return this;
}

QList<QDockWidget*> SkillEdit::dockWidgets() {
    return QList<QDockWidget*>() << d.dockWidget;
}

void SkillEdit::setStateModified() {
    ui->buttonBox->setEnabled(true);
}

void SkillEdit::setStateUnmodified() {
    ui->buttonBox->setDisabled(true);
}
