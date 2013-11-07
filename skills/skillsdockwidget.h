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
    void skillCreateClicked();
    void skillRemoveClicked(const QModelIndex &index);
    void skillSelected(const QModelIndex &index);

public slots:
    void selectSkill(const QModelIndex &index);

private slots:
    void emitSkillSelected(const QModelIndex &index);
    void emitSkillRemoveClicked(const QModelIndex &index);

private:
    Ui::SkillsDockWidget *ui;
    class SkillsDockWidgetPrivate &d;
};

#endif // SKILLSDOCKWIDGET_H
