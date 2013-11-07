#ifndef IMAINWINDOWFACET_H
#define IMAINWINDOWFACET_H

#include <QWidget>
#include <QList>
#include <QDockWidget>

class IMainWindowFacet {
public:
    virtual ~IMainWindowFacet() {}

    virtual QWidget* mainWidget() = 0;
    virtual QList<QDockWidget*> dockWidgets() = 0;
};

#endif // IMAINWINDOWFACET_H

