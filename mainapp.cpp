#include "mainapp.h"

#include "database/orm.h"
#include "mainwindow.h"

#include "map/mapview.h"

#include "skills/skill.h"
#include "skills/skillcontroller.h"
#include "skills/skillview.h"

#include "character/character.h"

class MainAppPrivate {
public:
    MainWindow *mainWindow;

    SkillController *skillController;
    SkillView *skillView;

    MapView *mapView;
};

MainApp::MainApp(QObject *parent) :
    QObject(parent),
    d(*new MainAppPrivate)
{
    //Register data objects
    ORM()->registerDataObject<Skill>();
    ORM()->registerDataObject<Character>();

    //Load all objects from the database
    ORM()->loadAll();

    //Create the main window
    d.mainWindow = new MainWindow();

    //Create the controllers
    d.skillController = new SkillController(this);

    //Create the views
    d.skillView = new SkillView;
    d.mainWindow->addFacet(d.skillView);

    //Create map facet
    d.mapView = new MapView(this);
    d.mainWindow->addFacet(d.mapView);
}

MainApp::~MainApp() {
    delete d.mainWindow;
    delete &d;
}

void MainApp::start() {    
    //Set the default facet
    d.mainWindow->setFacet(d.mapView);

    //Show the main window
    d.mainWindow->show();
}
