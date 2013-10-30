#ifndef MAPGRAPHICSVIEW_H
#define MAPGRAPHICSVIEW_H

#include <QGraphicsView>

class MapGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MapGraphicsView(QWidget *parent = 0);
    
signals:
    void mouseDoubleClicked(const QPointF &pos);
    void keyPressed(int key);
    
public slots:

protected:
    void mousePressEvent(QMouseEvent * e);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAPGRAPHICSVIEW_H
