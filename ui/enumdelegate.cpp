#include "enumdelegate.h"

#include <QComboBox>
#include <QLabel>
#include <QDebug>

EnumDelegate::EnumDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

//QWidget* EnumDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
////    QComboBox *combo = new QComboBox(parent);

//    qDebug() << index.data();

////    return combo;
//}

//void EnumDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
//    int value = index.model()->data(index, Qt::EditRole).toInt();
//    QComboBox *combo = static_cast<QComboBox*>(editor);
//    //combo->setCurrentIndex(value);
//}

//void EnumDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
//    QComboBox *combo = static_cast<QComboBox*>(editor);
//    //model->setData(index, value, Qt::EditRole);
//}
