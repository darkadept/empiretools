#include "skilledit.h"
#include "ui_skilledit.h"

#include <QPushButton>
#include <QMetaEnum>
#include <QDebug>
#include <QModelIndex>
#include "database/orm.h"
#include "ui/datawidgetmapper.h"

class SkillEditPrivate {
public:
    DataWidgetMapper *mapper;
};

SkillEdit::SkillEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkillEdit),
    d(*new SkillEditPrivate)
{
    ui->setupUi(this);

    ui->buttonBox->setStandardButtons(QDialogButtonBox::Save | QDialogButtonBox::Cancel);

    QMetaEnum skillBaseEnum = Orm::instance()->metaEnum("SkillBase");
    for (int i=0; i<skillBaseEnum.keyCount(); ++i) {
        ui->base->addItem(skillBaseEnum.key(i));
    }

    QMetaEnum skillCategoryEnum = Orm::instance()->metaEnum("SkillCategory");
    for (int i=0; i<skillCategoryEnum.keyCount(); ++i) {
        ui->category->addItem(skillCategoryEnum.key(i));
    }

    Repository *skillRepo = Orm::instance()->repository("Skill");
    d.mapper = new DataWidgetMapper(this);
    d.mapper->setSubmitPolicy(DataWidgetMapper::ManualSubmit);
    d.mapper->setModel(skillRepo);
    d.mapper->addMapping(ui->name, skillRepo->column("name"));
    d.mapper->addMapping(ui->base, skillRepo->column("base"), "currentIndex");
    d.mapper->addMapping(ui->category, skillRepo->column("category"), "currentIndex");
    d.mapper->addMapping(ui->rulesPage, skillRepo->column("rulesPage"));
    d.mapper->addMapping(ui->description, skillRepo->column("description"));
    d.mapper->addMapping(ui->dieResults, skillRepo->column("dieResults"));
    d.mapper->toFirst();
    setStateUnmodified();

    connect(d.mapper, SIGNAL(dataChanged()), this, SLOT(setStateModified()));

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

void SkillEdit::setCurrentIndex(const QModelIndex &index) {
    if (!index.isValid()) return;
    d.mapper->submit();
    d.mapper->setCurrentIndex(index.row());
}

void SkillEdit::setStateModified() {
    ui->buttonBox->setEnabled(true);
}

void SkillEdit::setStateUnmodified() {
    ui->buttonBox->setDisabled(true);
}
