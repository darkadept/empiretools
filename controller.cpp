#include "controller.h"
#include "mainwindow.h"

// Map Facet
#include "map/mapwidget.h"
#include "map/mapdockwidget.h"

#include "skills/skill.h"
#include "character/character.h"

#include "skills/skillsdockwidget.h"
#include "skills/skilledit.h"

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
    Orm::instance()->registerDataObject<Skill>();
    Orm::instance()->registerDataObject<Character>();

    Orm::instance()->loadAll();

    //Init ui
    ui.mainWindow = new MainWindow;
}

Controller::~Controller() {
    delete ui.mainWindow;
    delete &ui;
    delete &d;
}

void Controller::start() {
//    initPlayers();
    initMap();
    initSkills();

    ui.mainWindow->setFacet(0);
    ui.mainWindow->show();
}

/*
void Controller::initPlayers() {
    MainWindowFacet facet;
    facet.title = tr("Characters");

    // player dock
    QTableView *playerView = new QTableView();
    //playerView->setModel(d.playerModel);
    //    connect(d.playerView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(selectPlayer(QModelIndex)));
    QDockWidget *dock = new QDockWidget(tr("Characters"));
    dock->setAllowedAreas((Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea));
    dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock->setWidget(playerView);

    facet.facetDocks.append(qMakePair(Qt::RightDockWidgetArea, dock));

    facet.widget = new QLabel("hello world");

    int id = ui.mainWindow->addFacet(facet);
    ui.mainWindow->setFacet(id);
}
*/

void Controller::initMap() {
    MainWindowFacet facet;
    facet.title = tr("Maps");

    MapDockWidget *dock = new MapDockWidget(ui.mainWindow);
    facet.facetDocks.append(qMakePair(Qt::RightDockWidgetArea, qobject_cast<QDockWidget*>(dock)));

    MapWidget *mapWidget = new MapWidget(dock, ui.mainWindow);
    facet.widget = mapWidget;

    ui.mainWindow->addFacet(facet);
}


void Controller::initSkills() {
    MainWindowFacet facet;
    facet.title = tr("Skills");

    SkillEdit *skillEdit = new SkillEdit(ui.mainWindow);
    facet.widget = skillEdit;

    SkillsDockWidget* dock = new SkillsDockWidget(ui.mainWindow);
    facet.facetDocks.append(qMakePair(Qt::LeftDockWidgetArea, qobject_cast<QDockWidget*>(dock)));

    connect(dock, SIGNAL(currentIndexChanged(QModelIndex)), skillEdit, SLOT(setCurrentIndex(QModelIndex)));

    ui.mainWindow->addFacet(facet);
}

