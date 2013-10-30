#ifndef MAPDOCKWIDGET_H
#define MAPDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class MapDockWidget;
}

class MapDockWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit MapDockWidget(QWidget *parent = 0);
    ~MapDockWidget();

    double hyperdriveClass() const;

public slots:
    void setHours(double slow, double fast, double avg, double lightyears);

signals:
    void hyperdriveClassChanged(double value);
    
private:
    Ui::MapDockWidget *ui;
};

#endif // MAPDOCKWIDGET_H
