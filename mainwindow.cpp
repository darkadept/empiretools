#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolBar>
#include <QDebug>

class MainWindowPrivate {
public:
    int currentFacet;
    QHash<int, MainWindowFacet> facets;

    QToolBar *toolBar;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    d(*new MainWindowPrivate)
{
    d.currentFacet = -1;
    ui->setupUi(this);

    d.toolBar = new QToolBar();
    d.toolBar->setIconSize(QSize(64,32));
    d.toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d.toolBar->setMovable(false);
    addToolBar(Qt::TopToolBarArea, d.toolBar);

    connect(ui->stack, SIGNAL(currentChanged(int)), this, SLOT(setFacet(int)));
    connect(d.toolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(activateToolBarAction(QAction*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete &d;
}

/**
 * @brief MainWindow::addFacet
 * @param facet
 * @return
 * Adds a new facet to the MainWindow.
 */
int MainWindow::addFacet(const MainWindowFacet &facet) {
    if (!facet.widget) return -1;

    //int id = ui->stack->addTab(facet.widget, facet.title);
    int id = ui->stack->addWidget(facet.widget);

    QAction *action = d.toolBar->addAction(facet.widget->windowIcon(), facet.title);
    action->setData(id);
    action->setCheckable(true);

    d.facets.insert(id, facet);
    addFacetChrome(id);
    return id;
}

/**
 * @brief MainWindow::addFacetChrome
 * @param id
 * Adds the specified facet's chrome to the MainWindow. (ie. DockWidget's, etc.)
 */
void MainWindow::addFacetChrome(int id) {
    // Adds DockWidget chrome.
    QPair<Qt::DockWidgetArea, QDockWidget*> dock;
    foreach (dock, d.facets.value(id).facetDocks) {
        addDockWidget(dock.first, dock.second);
        dock.second->hide();
    }
}

/**
 * @brief MainWindow::setFacet
 * @param index
 * Sets the facet to the specified index.
 */
void MainWindow::setFacet(int index) {
    if (index == -1) return;
    if (index == d.currentFacet) return;
    if (d.facets.count()==0) return;

    //Hide old facet specific chrome
    if (d.currentFacet >= 0) {
        QPair<Qt::DockWidgetArea, QDockWidget*> dock;
        foreach (dock, d.facets.value(d.currentFacet).facetDocks) {
            dock.second->hide();
        }
    }

    //Show new facet chrome
    QPair<Qt::DockWidgetArea, QDockWidget*> dock;
    foreach (dock, d.facets.value(index).facetDocks) {
        dock.second->show();
    }

    d.currentFacet = index;
}

void MainWindow::activateToolBarAction(QAction *action) {
    ui->stack->setCurrentIndex(action->data().toInt());
    action->setChecked(true);
    foreach (QAction *act, d.toolBar->actions()) {
        if (act != action && act->isChecked()) act->setChecked(false);
    }
}
