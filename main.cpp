#include <stdlib.h>
#include <time.h>
#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QFile>
#include <QDir>

#include "controller.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //Initialize random generator
    srand(time(NULL));

    qDebug() << "Starting up...";
    QApplication a(argc, argv);

    //Set database
    QDir dbPath = QDir(a.applicationDirPath());
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath.absoluteFilePath("empiretools.db"));

    //Open database
    if (!db.open()) {
        qDebug() << "Can't open database";
        return -1;
    }

    Controller c;
    c.start();
    return a.exec();
}
