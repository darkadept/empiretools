#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>
#include <QUuid>

class DataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUuid id READ id WRITE setId)

public:
    explicit DataObject(const QUuid &uuid, QObject *parent = 0);
    ~DataObject();

    QUuid id() const;
    void setId(const QUuid &id);

private:
    class DataObjectPrivate &d;
};

#endif // DATAOBJECT_H
