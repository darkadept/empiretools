#ifndef ORM_H
#define ORM_H

#include <QObject>
#include "repository.h"

class Orm : public QObject
{
    Q_OBJECT

public:
    static Orm* instance() {
        static Orm instance;
        return &instance;
    }
    ~Orm();

    template<class T> void registerDataObject();
    QMetaObject metaObject(const QString &className) const;
    QMetaEnum metaEnum(const QString &typeName) const;
    Repository *repository(const QString &className);

    void loadAll();

    void D_properties();

private:
    void addMetaObject(const QString &className, const QMetaObject &metaObj);
    bool tableExists(const QString &tableName) const;
    bool createTable(const QString &className) const;

    explicit Orm();
    Orm(Orm const &);
    Orm operator=(Orm const&);

    class OrmPrivate &d;
};

template<class T>
void Orm::registerDataObject() {
    addMetaObject(T::staticMetaObject.className(), T::staticMetaObject);
}

#endif // ORM_H
