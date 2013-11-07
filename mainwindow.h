#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui/imainwindowfacet.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//    int addFacet(IMainWindowFacet *facet);
    
//public slots:
//    void setFacet(int index);
//    void setFacet(IMainWindowFacet *facet);

private:
    Ui::MainWindow *ui;
    class MainWindowPrivate &d;

};

#endif // MAINWINDOW_H
