#include "mapwidget.h"
#include "ui_mapwidget.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QFile>
#include <QPair>
#include "mapgraphicsview.h"
#include <QDebug>

class Region {
public:
    QPainterPath path;
    double modifier;
    QString description;
    QColor legColor;
};

class MapWidgetPrivate {
public:
    MapGraphicsView *gv;
    QGraphicsScene *scene;

    QList<QGraphicsLineItem*> legs;
    QPointF lastPos;

    QList<Region> regions;
    Region outerRimRegion;

    double lyPerPixel;// = 96.0;
    double slowClass1;// = 427.786; // LY per Hour
    double fastClass1;// = 1289.062;
    double avgClass1;// = 858.424;

    MapDockWidget *dockWidget;

    MapWidgetPrivate() {
        lyPerPixel = 96.0;
        slowClass1 = 427.786; //LY per Hour for a Class 1 Hyperdrive (slowest possible calculation)
        fastClass1 = 1289.062; //LY per Hour for a Class 1 Hyperdrive (fastest possible calculation)
        avgClass1 = 858.424; //LY per Hour for a Class 1 Hyperdrive (average calculation)
    }

};

MapWidget::MapWidget(MapDockWidget *dockWidget, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapWidget),
    d(*new MapWidgetPrivate)
{
    ui->setupUi(this);

    d.dockWidget = dockWidget;

    d.scene = new QGraphicsScene(this);

    d.gv = new MapGraphicsView(this);
    d.gv->setRenderHints(QPainter::Antialiasing);
    d.gv->setScene(d.scene);
    ui->verticalLayout->addWidget(d.gv);

    QImage img(":/images/galacticmap.jpg");
    d.scene->addPixmap(QPixmap::fromImage(img));
    d.scene->setSceneRect(img.rect());

    connect(d.gv, SIGNAL(mouseDoubleClicked(QPointF)), this, SLOT(addPoint(QPointF)));
    connect(d.gv, SIGNAL(keyPressed(int)), this, SLOT(pressKey(int)));
    connect(d.dockWidget, SIGNAL(hyperdriveClassChanged(double)), this, SLOT(calculateTrip(double)));
    connect(this, SIGNAL(tripCalculated(double,double,double,double)), d.dockWidget, SLOT(setHours(double,double,double,double)));

    loadRegions();
}

MapWidget::~MapWidget()
{
    delete ui;
    delete &d;
}

void MapWidget::addPoint(const QPointF &pos) {
    if (d.lastPos.isNull()) {
        d.lastPos = pos;
    } else {

        QList<QLineF> currentLegs;

        currentLegs.append(QLineF(d.lastPos, pos));

        // For each region and each leg, break the legs up
        foreach (const Region &region, d.regions) {
            foreach (const QLineF &leg, currentLegs) {                
                if (region.path.intersects(createFakeLine(leg))) {
                    if (!(region.path.contains(leg.p1()) && region.path.contains(leg.p2()))) {
                        QList<QLineF> newLegs = splitLine(leg, region.path);
                        currentLegs.removeOne(leg);
                        currentLegs.append(newLegs);
                    }
                }
            }
        }

        double length = 0.0;

        // For each leg and each region, determine which region each leg is in and draw it        
        foreach (const QLineF &leg, currentLegs) {
            Region currentRegion = d.outerRimRegion;
            QPointF midPoint = leg.pointAt(0.5);
            for (int i=d.regions.count()-1; i>=0; --i) {
                if (d.regions.at(i).path.contains(midPoint)) {
                    currentRegion = d.regions.at(i);
                    break;
                }
            }

            QPen pen;
            pen.setColor(currentRegion.legColor);
            pen.setWidth(2);
            QGraphicsLineItem *item = d.scene->addLine(leg,pen);
            item->setData(MapWidget::SceneData_Type, MapWidget::SceneType_Leg);
            item->setData(MapWidget::SceneData_Modifier, currentRegion.modifier);
            item->setData(MapWidget::SceneData_Description, currentRegion.description);
            d.legs.append(item);
            length += leg.length();
            qDebug() << "Traveling through:" << currentRegion.description;            
        }

        d.lastPos = pos;
        calculateTrip();
    }
}

void MapWidget::pressKey(int key) {
    if (key == Qt::Key_Delete) {
        if (d.legs.count() == 0) {
            d.lastPos = QPointF();
        } else {
            d.scene->removeItem(d.legs.takeLast());
            if (d.legs.count() == 0) {
                d.lastPos = QPointF();
            } else {
                d.lastPos = d.legs.last()->line().p2();
            }
        }
        calculateTrip();
    }
}

void MapWidget::loadRegions() {
    QFile file(":/data/regions.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString descLine = in.readLine();
            QString dataLine = in.readLine();
            loadRegion(dataLine, descLine);
        }
    } else {
        qDebug() << file.errorString();
    }
    file.close();
}

void MapWidget::loadRegion(const QString &dataLine, const QString &descLine) {
    QPolygonF regionPoly;

    QStringList descList = descLine.split(',');

    if (dataLine == "NA") {
        d.outerRimRegion.description = descList[0];
        d.outerRimRegion.modifier = descList[1].toFloat();
        d.outerRimRegion.legColor = QColor(descList[2]);
        return;
    }

    // Build a polygon from the points string
    QStringList pointStringList = dataLine.split(' ', QString::SkipEmptyParts);
    foreach(const QString &pointString, pointStringList) {
        QStringList xy = pointString.split(',',QString::SkipEmptyParts);
        if (xy.count() == 2) {
            QPointF pos;
            pos.setX(xy.first().toDouble());
            pos.setY(xy.last().toDouble());
            regionPoly.append(pos);
        }
    }

    // Close the polygon end to start
    regionPoly.append(regionPoly.at(0));

    // Create a painter path
    QPainterPath regionPolyPath;
    regionPolyPath.addPolygon(regionPoly);

    Region region;
    region.path = regionPolyPath;
    region.modifier = descList[1].toFloat();
    region.description = descList[0];
    region.legColor = QColor(descList[2]);
    d.regions.append(region);

    // Set up the pen
    QPen pen(QColor(Qt::yellow));
    pen.setWidthF(2.0);
    pen.setStyle(Qt::DotLine);

    // Add the painter path to the scene (optional)
    QGraphicsPathItem *item = d.scene->addPath(regionPolyPath, pen);
    item->setData(MapWidget::SceneData_Type, MapWidget::SceneType_Region);
}

QPainterPath MapWidget::createFakeLine(const QLineF &line) {
    // Create a fake line (actually a polygon that is ALMOST a line).
    QPolygonF fakeLine;
    fakeLine << line.p1() << line.p2() << line.p2()-QPointF(0.0001,0.0001) << line.p1();
    QPainterPath fakeLinePath;
    fakeLinePath.addPolygon(fakeLine);
    return fakeLinePath;
}

QList<QLineF> MapWidget::splitLine(const QLineF &line, const QPainterPath &polyPath) {
    QPainterPath fakeLinePath = createFakeLine(line);

    // Intersect paths
    QPainterPath outside = fakeLinePath.subtracted(polyPath);
    QPainterPath inside = fakeLinePath.intersected(polyPath);

    // Iterate through fake line polys to create real lines
    QList<QLineF> lines;
    lines.append(fakeLineToQLineFList(outside));
    lines.append(fakeLineToQLineFList(inside));
    return lines;
}

QList<QLineF> MapWidget::fakeLineToQLineFList(const QPainterPath &fakeLine) {
    QList<QLineF> lines;
    for (int i=0; i<fakeLine.elementCount(); ++i) {
        QPainterPath::Element el = fakeLine.elementAt(i);
        if (el.isMoveTo()) { //Start a new line
            QLine line;
            line.setP1(QPointF(el).toPoint());
            i++;
            bool done = false;
            while (i<fakeLine.elementCount() && !done) {
                el = fakeLine.elementAt(i);
                if (el.isMoveTo()) {
                    i--;
                    done = true;
                } else {
                    QPoint elPoint(QPointF(el).toPoint());
                    if (elPoint != line.p1()) line.setP2(elPoint);
                    i++;
                }
            }
            lines.append(QLineF(line));
        }
    }
    return lines;
}

void MapWidget::calculateTrip(double hyperDriveClass) {
    if (hyperDriveClass == 0) {
        hyperDriveClass = d.dockWidget->hyperdriveClass();
    }

    double slowHours = 0.0;
    double fastHours = 0.0;
    double avgHours = 0.0;
    double totalLY = 0.0;

    foreach (QGraphicsLineItem *leg, d.legs) {
        double legLY = leg->line().length() * d.lyPerPixel;
        totalLY += legLY;

        double slowDriveSpeed = d.slowClass1 / hyperDriveClass;
        double fastDriveSpeed = d.fastClass1 / hyperDriveClass;
        double avgDriveSpeed = d.avgClass1 / hyperDriveClass;

        double regionModifier = leg->data(MapWidget::SceneData_Modifier).toFloat();
        slowHours += (legLY / slowDriveSpeed) * regionModifier;
        fastHours += (legLY / fastDriveSpeed) * regionModifier;
        avgHours += (legLY / avgDriveSpeed) * regionModifier;
    }

    emit tripCalculated(slowHours, fastHours, avgHours, totalLY);
}
