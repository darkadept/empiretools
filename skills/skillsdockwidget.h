#ifndef SKILLSDOCKWIDGET_H
#define SKILLSDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class SkillsDockWidget;
}

class SkillsDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit SkillsDockWidget(QWidget *parent = 0);
    ~SkillsDockWidget();

signals:
    void currentIndexChanged(const QModelIndex &index);

private slots:
    void addNewSkill();
    void removeSelectedSkill();

private:
    Ui::SkillsDockWidget *ui;
    class SkillsDockWidgetPrivate &d;
};

#endif // SKILLSDOCKWIDGET_H
