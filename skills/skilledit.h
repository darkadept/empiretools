#ifndef SKILLEDIT_H
#define SKILLEDIT_H

#include <QWidget>
#include "ui/imainwindowfacet.h"

namespace Ui {
class SkillEdit;
}

class SkillEdit : public QWidget, public IMainWindowFacet
{
    Q_OBJECT

public:
    explicit SkillEdit(QWidget *parent = 0);
    ~SkillEdit();

    //IMainWindowFacet
    QWidget* mainWidget();
    QList<QDockWidget*> dockWidgets();

signals:
    void skillCreateClicked();
    void skillRemoveClicked(const QModelIndex &index);
    void skillSelected(const QModelIndex &index);

public slots:


private slots:
    void setStateModified();
    void setStateUnmodified();

private:
    Ui::SkillEdit *ui;
    class SkillEditPrivate &d;
};

#endif // SKILLEDIT_H
