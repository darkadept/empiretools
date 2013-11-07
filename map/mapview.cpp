#include "mapview.h"

#include "mapdockwidget.h"
#include "mapwidget.h"

class MapViewPrivate {
public:
    MapDockWidget *dock;
    MapWidget *mapWidget;
};

MapView::MapView(QObject *parent) :
    QObject(parent),
    d(*new MapViewPrivate)
{
    d.dock = new MapDockWidget;
    d.mapWidget = new MapWidget(d.dock);
}

MapView::~MapView() {
    delete &d;
}

QWidget* MapView::mainWidget() {
    return d.mapWidget;
}

QList<QDockWidget*> MapView::dockWidgets() {
    return QList<QDockWidget*>() << d.dock;
}
