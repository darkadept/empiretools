#ifndef MAINAPP_H
#define MAINAPP_H

#include <QObject>

class MainApp : public QObject
{
    Q_OBJECT
public:
    explicit MainApp(QObject *parent = 0);
    ~MainApp();

    void start();

private:
    class MainAppPrivate &d;
};

#endif // MAINAPP_H
