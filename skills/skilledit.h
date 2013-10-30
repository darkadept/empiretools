#ifndef SKILLEDIT_H
#define SKILLEDIT_H

#include <QWidget>

namespace Ui {
class SkillEdit;
}

class SkillEdit : public QWidget
{
    Q_OBJECT

public:
    explicit SkillEdit(QWidget *parent = 0);
    ~SkillEdit();

public slots:
    void setCurrentIndex(const QModelIndex &index);

private slots:
    void setStateModified();
    void setStateUnmodified();

private:
    Ui::SkillEdit *ui;
    class SkillEditPrivate &d;
};

#endif // SKILLEDIT_H
