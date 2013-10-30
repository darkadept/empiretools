#include "dataobject.h"

class DataObjectPrivate {
public:
    QUuid uuid;
};

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
