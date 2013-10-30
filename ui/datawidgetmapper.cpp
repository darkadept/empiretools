#include "datawidgetmapper.h"

#include <QWidget>
#include <QMetaProperty>
#include <QMetaMethod>
#include <QDebug>

class DataWidgetMapperPrivate {
public:

};

DataWidgetMapper::DataWidgetMapper(QObject *parent) :
    QDataWidgetMapper(parent),
    d(*new DataWidgetMapperPrivate)
{
}

DataWidgetMapper::~DataWidgetMapper() {
    delete &d;
}

void DataWidgetMapper::addMapping(QWidget *widget, int section) {
    QMetaProperty property = widget->metaObject()->userProperty();
    Q_ASSERT(property.isValid());
    QMetaMethod notifySignal = property.notifySignal();
    Q_ASSERT(notifySignal.isValid());
    connect(widget, notifySignal, this, QMetaMethod::fromSignal(&DataWidgetMapper::dataChanged));

    QDataWidgetMapper::addMapping(widget, section);
}

void DataWidgetMapper::addMapping(QWidget *widget, int section, const QByteArray &propertyName) {
    QMetaProperty property;
    for (int i=0; i<widget->metaObject()->propertyCount(); ++i) {
        if (QString(widget->metaObject()->property(i).name()) == propertyName) {
            property = widget->metaObject()->property(i);
            break;
        }
    }
    Q_ASSERT(property.isValid());
    QMetaMethod notifySignal = property.notifySignal();
    Q_ASSERT(notifySignal.isValid());
    connect(widget, notifySignal, this, QMetaMethod::fromSignal(&DataWidgetMapper::dataChanged));

    QDataWidgetMapper::addMapping(widget, section, propertyName);
}
