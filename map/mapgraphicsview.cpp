#include "mapgraphicsview.h"

#include <QMouseEvent>

MapGraphicsView::MapGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
     setDragMode(ScrollHandDrag);
}

void MapGraphicsView::mousePressEvent(QMouseEvent *e) {
    //QPointF point = mapToScene(e->pos());
    QGraphicsView::mousePressEvent(e);
}

void MapGraphicsView::mouseDoubleClickEvent(QMouseEvent *e) {
    QPointF point = mapToScene(e->pos());
    emit mouseDoubleClicked(point);
    QGraphicsView::mouseDoubleClickEvent(e);
}

void MapGraphicsView::wheelEvent(QWheelEvent *event) {
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Scale the view / do the zoom
    double scaleFactor = 1.15;
        if(event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void MapGraphicsView::keyPressEvent(QKeyEvent *event) {
    emit keyPressed(event->key());
    QGraphicsView::keyPressEvent(event);
}
