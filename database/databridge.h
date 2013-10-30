#ifndef DATABRIDGE_H
#define DATABRIDGE_H

#include <QObject>
#include <QMetaObject>
#include <QSqlQuery>
#include "dataobject.h"

class DataBridge : public QObject
{
    Q_OBJECT
public:
    DataBridge(const QMetaObject &meta, QObject *parent=0);
    ~DataBridge();

    void dbLoad(DataObject *obj, QSqlQuery *q);
    void dbInsert(DataObject *obj, QSqlQuery *q);
    void dbUpdate(DataObject *obj, QSqlQuery *q);
    void dbDelete(const QUuid &id, QSqlQuery *q);

    QString sqlSelect() const;

private:
    class DataBridgePrivate &d;
};

#endif // DATABRIDGE_H
