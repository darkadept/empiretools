#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include "mapdockwidget.h"

namespace Ui {
class MapWidget;
}

class MapWidget : public QWidget
{
    Q_OBJECT
    Q_ENUMS(MapSceneType)
    Q_ENUMS(MapSceneData)
    
public:
    explicit MapWidget(MapDockWidget *dockWidget, QWidget *parent = 0);
    ~MapWidget();

    enum MapSceneType { SceneType_Region, SceneType_Leg };
    enum MapSceneData { SceneData_Type=0, SceneData_Modifier, SceneData_Description };

signals:
    void tripCalculated(double slow, double fast, double avg, double lightyears);

public slots:
    void calculateTrip(double hyperDriveClass = 0);

private slots:
    void addPoint(const QPointF &pos);
    void pressKey(int key);
    
private:
    Ui::MapWidget *ui;
    class MapWidgetPrivate &d;

    void loadRegions();
    void loadRegion(const QString &dataLine, const QString &descLine);

    QPainterPath createFakeLine(const QLineF &line);
    QList<QLineF> splitLine(const QLineF &line, const QPainterPath &polyPath);
    QList<QLineF> fakeLineToQLineFList(const QPainterPath &fakeLine);
};

#endif // MAPWIDGET_H
