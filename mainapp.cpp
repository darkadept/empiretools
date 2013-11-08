#include "mainapp.h"

#include "database/orm.h"
#include "mainwindow.h"

#include "map/mapview.h"

#include "skills/skill.h"
#include "skills/skillview.h"
#include "skills/skillcontroller.h"

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
    ORM()->registerDataObject<Skill>();
    ORM()->registerDataObject<Character>();
    ORM()->loadAll();

    d.mainWindow = new MainWindow();

    d.skillController = new SkillController(this);
    d.skillView = new SkillView(this);
    connect(d.skillView, SIGNAL(createSkillClicked()), d.skillController, SLOT(createSkill()));
    d.mainWindow->addFacet(d.skillView);

    d.mapView = new MapView(this);
    d.mainWindow->addFacet(d.mapView);
}

MainApp::~MainApp() {
    delete d.mainWindow;
    delete &d;
}

void MainApp::start() {    
    d.mainWindow->setFacet(d.skillView);
    d.mainWindow->show();
}
