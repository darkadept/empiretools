#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolBar>
#include <QDebug>
#include <QStatusBar>

class MainWindowPrivate {
public:
    QToolBar *toolBar;
//    QHash<int, IMainWindowFacet*> facets;
    int currentFacet;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    d(*new MainWindowPrivate)
{
    d.currentFacet = -1;

    //Create main toolbar
//    d.toolBar = new QToolBar();
//    d.toolBar->setIconSize(QSize(64,32));
//    d.toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    d.toolBar->setMovable(false);
//    addToolBar(Qt::TopToolBarArea, d.toolBar);

    //connect(ui->stack, SIGNAL(currentChanged(int)), this, SLOT(setFacet(int)));
    //connect(d.toolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(activateToolBarAction(QAction*)));

    ui->stack->addWidget(new QWidget);

}

MainWindow::~MainWindow() {
    delete ui;
    delete &d;
}

//int MainWindow::addFacet(IMainWindowFacet *facet) {
//    if (!facet) return -1;
//    Q_ASSERT(facet->mainWidget());

//    Q_ASSERT(ui);
//    Q_ASSERT(ui->stack);

//    QList<QDockWidget*> list = facet->dockWidgets();
//    qDebug() << list.count();


//    //Add mainWidget to stack
//    QWidget *mainWidget = facet->mainWidget();
//    Q_ASSERT(mainWidget);
//    ui->stack->addWidget(mainWidget);
////    int index = ui->stack->addWidget(mainWidget);
//    //int index = ui->stack->addWidget(new QWidget());
//    int index = 1;

//    d.facets.insert(index, facet);

//    //Create toolbar action
//    QAction *action = d.toolBar->addAction(facet->mainWidget()->windowIcon(), facet->mainWidget()->windowTitle());
//    action->setData(index);
//    action->setCheckable(true);

//    //Add DockWidgets
//    foreach (QDockWidget *dock, facet->dockWidgets()) {
//        dock->setParent(this);
//        addDockWidget(Qt::LeftDockWidgetArea, dock);
//        dock->hide();
//    }

//    return index;
//}

//void MainWindow::setFacet(int index) {
//    if (!d.facets.contains(index)) return;
//    if (d.facets.count()==0) return;

//    if (d.currentFacet >= 0 && d.currentFacet != index) {

//        //Hide all DockWidgets
//        foreach(IMainWindowFacet* facet, d.facets.values()) {
//            foreach(QDockWidget* dock, facet->dockWidgets()) {
//                dock->hide();
//            }
//        }

//        //Show this facet's DockWidgets
//        foreach(QDockWidget* dock, d.facets.value(index)->dockWidgets()) {
//            dock->show();
//        }
//        d.currentFacet = index;
//    }
//}

//void MainWindow::setFacet(IMainWindowFacet *facet) {
//    setFacet(d.facets.key(facet));
//}
