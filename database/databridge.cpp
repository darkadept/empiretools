#include "databridge.h"

#include <QStringList>
#include <QMetaProperty>
#include <QDebug>
#include "orm.h"

class DataBridgePrivate {
public:
    QMetaObject meta;

    QString sqlSelect;
    QString sqlInsert;
    QString sqlUpdate;
    QString sqlDelete;
};

DataBridge::DataBridge(const QMetaObject &meta, QObject *parent) :
    QObject(parent),
    d(*new DataBridgePrivate)
{
    d.meta = meta;

    QStringList insertColumns;
    QStringList insertParameters;
    insertColumns.append("id");
    insertParameters.append("?");

    QStringList updateColumns;

    for (int i=d.meta.propertyOffset(); i<d.meta.propertyCount(); ++i) {
        insertColumns.append(d.meta.property(i).name());
        insertParameters.append("?");
        updateColumns.append(QString("%1=?").arg(d.meta.property(i).name()));
    }

    //Generate SQL select statement
    d.sqlSelect = QString("SELECT %1 FROM %2")
                    .arg(insertColumns.join(","))
                    .arg(d.meta.className());

    //Generate SQL update statement
    d.sqlUpdate = QString("UPDATE %1 SET %2 WHERE id=?")
                    .arg(d.meta.className())
                    .arg(updateColumns.join(","));

    //Generate SQL insert statement
    d.sqlInsert = QString("INSERT INTO %1 (%2) VALUES (%3)")
                    .arg(d.meta.className())
                    .arg(insertColumns.join(","))
                    .arg(insertParameters.join(","));

    //Generate SQL delete statement
    d.sqlDelete = QString("DELETE FROM %1 WHERE id = ?");
}

DataBridge::~DataBridge() {
    delete &d;
}

void DataBridge::dbLoad(DataObject *obj, QSqlQuery *q) {
    int column=1;
    for (int i=d.meta.propertyOffset(); i<d.meta.propertyCount(); ++i) {
        QMetaProperty property = d.meta.property(i);

        QVariant value = q->value(column);

        if (property.isEnumType()) {
            QMetaEnum e = Orm::instance()->metaEnum(property.typeName());
            QString s(e.valueToKey(value.toInt()));
            value = e.valueToKey(value.toInt());
        }

        bool works = property.write(obj, value);
        Q_ASSERT(works);

        column++;
    }
}

void DataBridge::dbInsert(DataObject *obj, QSqlQuery *q) {
    q->prepare(d.sqlInsert);
    q->addBindValue(obj->id());
    for (int i=d.meta.propertyOffset(); i<d.meta.propertyCount(); ++i) {
        QVariant value = d.meta.property(i).read(obj);
        q->addBindValue(value);
    }
}

void DataBridge::dbUpdate(DataObject *obj, QSqlQuery *q) {
    q->prepare(d.sqlUpdate);
    for (int i=d.meta.propertyOffset(); i<d.meta.propertyCount(); ++i) {
        QVariant value = d.meta.property(i).read(obj);
        q->addBindValue(value);
    }
    q->addBindValue(obj->id().toString());
}

void DataBridge::dbDelete(const QUuid &id, QSqlQuery *q) {
    q->prepare(d.sqlDelete.arg(d.meta.className()));
    q->addBindValue(id);
}

QString DataBridge::sqlSelect() const {
    return d.sqlSelect;
}
