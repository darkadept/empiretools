#include "dataobject.h"

#include <QDebug>

class DataObjectPrivate {
public:
    QUuid uuid;
    QByteArray md5;
    QList<QByteArray> buildMd5;
};

/**
 * @brief DataObject::DataObject
 * @param uuid
 * @param parent
 * Creates a new DataObject. If the uuid is null automatically assigns a new uuid.
 */
DataObject::DataObject(const QUuid &uuid, QObject *parent) :
    QObject(parent),
    d(*new DataObjectPrivate)
{
    if (uuid.isNull()) {
        d.uuid = QUuid::createUuid();
    } else {
        d.uuid = uuid;
    }
}

DataObject::~DataObject() {
    delete &d;
}

/**
 * @brief DataObject::isChanged
 * @return True if the object has changed since it's last update.
 */
bool DataObject::isChanged() const {
    return (d.md5 != md5());
}

/**
 * @brief DataObject::id
 * @return The uuid of the object.
 */
QUuid DataObject::id() const {
    return d.uuid;
}
/**
 * @brief DataObject::setId
 * @param id
 * Sets the uuid of the object.
 */
void DataObject::setId(const QUuid &id) {
    d.uuid = id;
}

/**
 * @brief DataObject::md5
 * @return The object's current md5 hash.
 * Calculates the object's current md5 hash.
 */
QByteArray DataObject::md5() const {
    QCryptographicHash h(QCryptographicHash::Md5);
    foreach (const QByteArray &ba, d.buildMd5) {
        h.addData(ba);
    }
    return h.result();
}

/**
 * @brief DataObject::updateMd5
 * Updates the md5 of the object.
 */
void DataObject::updateMd5() {
    d.md5 = md5();
}

/**
 * @brief DataObject::clearMd5
 * Clears the object's md5 hash.
 */
void DataObject::clearMd5() {
    d.buildMd5.clear();
}

/**
 * @brief DataObject::addToMd5
 * @param data
 * Adds data to the md5 hash.
 */
void DataObject::addToMd5(const QByteArray &data) {
    d.buildMd5.append(data);
}
