#ifndef SKILLVIEW_H
#define SKILLVIEW_H

#include <QWidget>
#include "ui/imainwindowfacet.h"

namespace Ui {
class SkillView;
}

class SkillView : public QWidget, public IMainWindowFacet
{
    Q_OBJECT

public:
    explicit SkillView(QWidget *parent = 0);
    ~SkillView();

    QWidget* mainWidget();
    QList<QDockWidget*> dockWidgets();

private:
    Ui::SkillView *ui;
};

#endif // SKILLVIEW_H
