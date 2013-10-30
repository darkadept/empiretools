#ifndef DATAWIDGETMAPPER_H
#define DATAWIDGETMAPPER_H

#include <QDataWidgetMapper>

class DataWidgetMapper : public QDataWidgetMapper
{
    Q_OBJECT
public:
    explicit DataWidgetMapper(QObject *parent = 0);
    ~DataWidgetMapper();

    void addMapping(QWidget *widget, int section);
    void addMapping(QWidget *widget, int section, const QByteArray &propertyName);

signals:
    void dataChanged();

private:
    class DataWidgetMapperPrivate &d;

};

#endif // DATAWIDGETMAPPER_H
