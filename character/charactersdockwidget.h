#ifndef CHARACTERSDOCKWIDGET_H
#define CHARACTERSDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class CharactersDockWidget;
}

class CharactersDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CharactersDockWidget(QWidget *parent = 0);
    ~CharactersDockWidget();

private:
    Ui::CharactersDockWidget *ui;
    class CharactersDockWidgetPrivate &d;
};

#endif // CHARACTERSDOCKWIDGET_H
