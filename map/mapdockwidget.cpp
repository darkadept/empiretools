#include "mapdockwidget.h"
#include "ui_mapdockwidget.h"

#include <QDebug>

MapDockWidget::MapDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::MapDockWidget)
{
    ui->setupUi(this);

    connect(ui->hyperdriveClass, SIGNAL(valueChanged(double)), this, SIGNAL(hyperdriveClassChanged(double)));
}

MapDockWidget::~MapDockWidget()
{
    delete ui;
}

double MapDockWidget::hyperdriveClass() const {
    return ui->hyperdriveClass->value();
}

void MapDockWidget::setHours(double slow, double fast, double avg, double lightyears) {

    //=TEXT(INT(H6/168),"0""w "";;")&TEXT(INT(MOD(H6,168)/24),"0""d "";;")&ROUND(MOD(H6,24),1)&"h"

    int weeks = slow / 168;
    int days = ((int)slow % 168) / 24;
    int hours = ((int)slow % 24);
    double pointHours = (slow / 24);

    qDebug() << weeks << days << hours << pointHours;

    ui->fastSpeed->setText(tr("%0").arg(fast));
    ui->slowSpeed->setText(tr("%0").arg(slow));
    ui->avgSpeed->setText(tr("%0").arg(avg));
    ui->lightyears->setText(tr("%0").arg(lightyears));
}
