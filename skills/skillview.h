#ifndef SKILLVIEW_H
#define SKILLVIEW_H

#include <QObject>
#include "ui/imainwindowfacet.h"

class SkillView : public QObject, public IMainWindowFacet
{
    Q_OBJECT
public:
    explicit SkillView(QObject *parent = 0);
    virtual ~SkillView();

    //IMainWindowFacet
    virtual QWidget *mainWidget();
    virtual QList<QDockWidget*> dockWidgets();

private:
    class SkillViewPrivate &d;
};

#endif // SKILLVIEW_H
