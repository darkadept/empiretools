#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>
#include <QUuid>
#include <QByteArray>
#include <QCryptographicHash>
#include <QDataStream>

class DataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUuid id READ id WRITE setId)

public:
    explicit DataObject(const QUuid &uuid, QObject *parent = 0);
    ~DataObject();

    bool isChanged() const;
    QUuid id() const;
    void setId(const QUuid &id);

    QByteArray md5() const;
    void updateMd5();

protected:
    void clearMd5();
    void addToMd5(const QByteArray &data);

    /**
     * @brief buildMd5
     * Override to build the md5 hash. Call clearMd5() and then addToMd5() in this method.
     */
    virtual void buildMd5() = 0;

private:
    class DataObjectPrivate &d;
};

#endif // DATAOBJECT_H
