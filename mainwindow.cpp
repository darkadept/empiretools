#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolBar>
#include <QDebug>
#include <QStatusBar>

class MainWindowPrivate {
public:
    QToolBar *toolBar;
    QHash<int, IMainWindowFacet*> facets;
    int currentFacet;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    d(*new MainWindowPrivate)
{
    ui->setupUi(this);

    d.currentFacet = -1;

    //Create main toolbar
    d.toolBar = new QToolBar();
    d.toolBar->setIconSize(QSize(64,32));
    d.toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d.toolBar->setMovable(false);
    addToolBar(Qt::TopToolBarArea, d.toolBar);

    connect(d.toolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(activateToolBarAction(QAction*)));
}

MainWindow::~MainWindow() {
    delete ui;
    delete &d;
}

int MainWindow::addFacet(IMainWindowFacet *facet) {
    if (!facet) return -1;
    Q_ASSERT(facet->mainWidget());

    //Add mainWidget to stack
    int index = ui->stack->addWidget(facet->mainWidget());
    d.facets.insert(index, facet);

    //Create toolbar action
    QAction *action = d.toolBar->addAction(facet->mainWidget()->windowIcon(), facet->mainWidget()->windowTitle());
    action->setData(index);
    action->setCheckable(true);

    //Add DockWidgets
    foreach (QDockWidget *dock, facet->dockWidgets()) {
        dock->setParent(this);
        addDockWidget(Qt::LeftDockWidgetArea, dock);
        dock->hide();
    }

    qDebug() << "Adding facet:" << facet->mainWidget()->windowTitle() << "at" << index;

    return index;
}

void MainWindow::setFacet(int index) {
    if (!d.facets.contains(index)) return;
    if (d.facets.count()==0) return;

    if (index >= 0 && d.currentFacet != index) {

        //Hide all DockWidgets
        foreach(IMainWindowFacet* facet, d.facets.values()) {
            foreach(QDockWidget* dock, facet->dockWidgets()) {
                dock->hide();
            }
        }

        //Show this facet's DockWidgets
        foreach(QDockWidget* dock, d.facets.value(index)->dockWidgets()) {
            dock->show();
        }

        //Enable action
        /** TODO Uncheck other actions */
        foreach (QAction* action, d.toolBar->actions()) {
            if (action->data().toInt() == index) {
                action->setChecked(true);
            }
        }

        d.currentFacet = index;
        ui->stack->setCurrentIndex(index);

    }
}

void MainWindow::setFacet(IMainWindowFacet *facet) {
    setFacet(d.facets.key(facet));
}

void MainWindow::activateToolBarAction(QAction *action) {
    setFacet(action->data().toInt());
    action->setChecked(true);
    foreach (QAction *act, d.toolBar->actions()) {
        if (act != action && act->isChecked()) act->setChecked(false);
    }
}
