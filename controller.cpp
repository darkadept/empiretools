#include "controller.h"
#include "mainwindow.h"

// Map Facet
#include "map/mapwidget.h"
#include "map/mapdockwidget.h"

#include "skills/skill.h"
#include "character/character.h"

#include "skills/skillsdockwidget.h"
#include "skills/skilledit.h"

#include "character/charactersdockwidget.h"

class ControllerPrivate {
public:
};

class ControllerUiPrivate {
public:
    MainWindow *mainWindow;
};

Controller::Controller(QObject *parent) :
    QObject(parent),
    d(*new ControllerPrivate),
    ui(*new ControllerUiPrivate)
{
    ORM()->registerDataObject<Skill>();
    ORM()->registerDataObject<Character>();

    ORM()->loadAll();

    //Init ui
    ui.mainWindow = new MainWindow;
}

Controller::~Controller() {
    delete ui.mainWindow;
    delete &ui;
    delete &d;
}

void Controller::start() {
//    initMap();
//    initSkills();
//    initCharacters();

//    ui.mainWindow->setFacet(0);
//    ui.mainWindow->show();
}

void Controller::createSkill() {
//    DataObject *object = REPOSITORY("Skill")->createObject();

}


//void Controller::initMap() {
//    MainWindowFacet facet;
//    facet.title = tr("Maps");

//    MapDockWidget *dock = new MapDockWidget(ui.mainWindow);
//    facet.facetDocks.append(qMakePair(Qt::RightDockWidgetArea, qobject_cast<QDockWidget*>(dock)));

//    MapWidget *mapWidget = new MapWidget(dock, ui.mainWindow);
//    facet.widget = mapWidget;

//    ui.mainWindow->addFacet(facet);
//}


//void Controller::initSkills() {
//    MainWindowFacet facet;
//    facet.title = tr("Skills");

//    SkillEdit *skillEdit = new SkillEdit(ui.mainWindow);
//    facet.widget = skillEdit;

//    SkillsDockWidget* dock = new SkillsDockWidget(ui.mainWindow);
//    facet.facetDocks.append(qMakePair(Qt::LeftDockWidgetArea, qobject_cast<QDockWidget*>(dock)));

//    connect(dock, SIGNAL(currentIndexChanged(QModelIndex)), skillEdit, SLOT(setCurrentIndex(QModelIndex)));

//    ui.mainWindow->addFacet(facet);
//}

//void Controller::initCharacters() {
//    MainWindowFacet facet;
//    facet.title = tr("Characters");

//    facet.widget = new QWidget();

//    CharactersDockWidget* dock = new CharactersDockWidget(ui.mainWindow);
//    facet.facetDocks.append(qMakePair(Qt::LeftDockWidgetArea, qobject_cast<QDockWidget*>(dock)));

//    ui.mainWindow->addFacet(facet);
//}
