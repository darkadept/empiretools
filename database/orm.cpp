#include "orm.h"

#include <QHash>
#include <QMetaProperty>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QStringList>
#include "repository.h"

class OrmPrivate {
public:
    QHash<QString, QMetaObject> meta;
    QHash<QString, QMetaEnum> enums;
    QHash<QString, Repository*> repos;
};

Orm::Orm() :
    QObject(0),
    d(*new OrmPrivate)
{
}

Orm::~Orm() {
    delete &d;
}

QMetaObject Orm::metaObject(const QString &className) const {
    return d.meta.value(className);
}

QMetaEnum Orm::metaEnum(const QString &typeName) const {
    return d.enums.value(typeName);
}

Repository* Orm::repository(const QString &className) {
    if (d.repos.contains(className))
        return d.repos.value(className);
    return 0;
}

void Orm::loadAll() {
    foreach (Repository *repo, d.repos.values()) {
        repo->load();
    }
}

void Orm::submitAll() {
    foreach (Repository *repo, d.repos.values()) {
        repo->submit();
    }
}

void Orm::addMetaObject(const QString &className, const QMetaObject &metaObj) {
    if (d.meta.contains(className)) return;

    //Add meta object
    d.meta.insert(className, metaObj);

    //Add enums
    for (int i=metaObj.enumeratorOffset(); i<metaObj.enumeratorCount(); ++i) {
        QMetaEnum e = metaObj.enumerator(i);
        d.enums.insert(QString(e.name()), e);
    }

    //Create table if needed
    if (!tableExists(className)) {
        createTable(className);
    }

    //Create repository for this type
    Repository *repo = new Repository(metaObj, this);
    d.repos.insert(className, repo);
}

bool Orm::tableExists(const QString &tableName) const {
    QSqlQuery q(QString("SELECT name FROM sqlite_master WHERE type='table' AND name='%1'").arg(tableName));
    if (!q.exec()) {
        qDebug() << q.lastError().text();
        return false;
    }
    if (!q.next()) {
        return false;
    }
    return true;
}

bool Orm::createTable(const QString &className) const {
    const QMetaObject &meta = d.meta.value(className);

    //Temporarily store classInfo
    QHash<QString, QString> classInfo;
    for (int i=meta.classInfoOffset(); i<meta.classInfoCount(); ++i) {
        classInfo.insert(meta.classInfo(i).name(), meta.classInfo(i).value());
    }

    QStringList columns;

    //Add ID column
    columns.append("id VARCHAR(40) NOT NULL");

    //Iterate through properties
    for (int i=meta.propertyOffset(); i<meta.propertyCount(); ++i) {
        QMetaProperty p = meta.property(i);
        QString name(p.name());
        QString type(p.typeName());

        //Check if there is a type override
        if (classInfo.contains(name)) {
            columns.append(QString("%1 %2")
                           .arg(name)
                           .arg(classInfo.value(name)));
            continue;
        }

        //Check if property is an enum
        if (p.isEnumType()) {
            columns.append(QString("%1 INTEGER DEFAULT '0' NOT NULL")
                           .arg(name));
            continue;
        }

        //Normal types
        QString sqlType;
        if (type == "int") sqlType = "INTEGER DEFAULT '0' NOT NULL";
        if (type == "QString") sqlType = "VARCHAR(64) NULL";

        columns.append(QString("%1 %2")
                       .arg(name)
                       .arg(sqlType));
    }

    //Prepare the SQL create statement
    QString sqlCreate = QString("CREATE TABLE %1 (%2)")
            .arg(className)
            .arg(columns.join(", "));

    //Create the table
    QSqlQuery q;
    if (!q.exec(sqlCreate)) {
        qDebug() << q.lastError().text();
        return false;
    }
    return true;
}
