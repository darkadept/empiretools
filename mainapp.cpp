#include "mainapp.h"

#include "database/orm.h"
#include "mainwindow.h"

#include "skills/skill.h"
#include "skills/skillview.h"

#include "character/character.h"

class MainAppPrivate {
public:
    MainWindow *mainWindow;

    SkillView *skillView;
};

MainApp::MainApp(QObject *parent) :
    QObject(parent),
    d(*new MainAppPrivate)
{
//    ORM()->registerDataObject<Skill>();
//    ORM()->registerDataObject<Character>();
//    ORM()->loadAll();
}

MainApp::~MainApp() {
    delete d.mainWindow;
    delete &d;
}

void MainApp::start() {
    d.mainWindow = new MainWindow();

    d.skillView = new SkillView(this);
    //d.mainWindow->addFacet(d.skillView);

    d.mainWindow->show();
    //d.mainWindow->setFacet(d.skillView);
}
