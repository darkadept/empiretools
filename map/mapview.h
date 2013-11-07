#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QObject>
#include "ui/imainwindowfacet.h"

class MapView : public QObject, public IMainWindowFacet
{
    Q_OBJECT
public:
    explicit MapView(QObject *parent = 0);
    ~MapView();

    virtual QWidget* mainWidget();
    virtual QList<QDockWidget*> dockWidgets();

private:
    class MapViewPrivate &d;

};

#endif // MAPVIEW_H
