#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QPair>
#include <QDockWidget>

namespace Ui {
class MainWindow;
}

class MainWindowFacet {
public:
    MainWindowFacet() {
        widget = 0;
    }

    QString title;
    QWidget *widget;
    QList<QPair<Qt::DockWidgetArea, QDockWidget*> > facetDocks;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int addFacet(const MainWindowFacet &facet);
    
public slots:
    void setFacet(int index);

private slots:
    void activateToolBarAction(QAction *action);

private:
    Ui::MainWindow *ui;
    class MainWindowPrivate &d;

    void addFacetChrome(int id);
};

#endif // MAINWINDOW_H
