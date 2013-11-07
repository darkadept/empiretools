#-------------------------------------------------
#
# Project created by QtCreator 2013-10-19T14:07:19
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = empiretools
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database/repository.cpp \
    database/dataobject.cpp \
    map/mapwidget.cpp \
    map/mapgraphicsview.cpp \
    map/mapdockwidget.cpp \
    character/character.cpp \
    skills/skill.cpp \
    database/orm.cpp \
    database/databridge.cpp \
    skills/skillsdockwidget.cpp \
    ui/enumdelegate.cpp \
    skills/skilledit.cpp \
    ui/datawidgetmapper.cpp \
    character/charactersdockwidget.cpp \
    skills/skillview.cpp \
    mainapp.cpp \
    map/mapview.cpp

HEADERS  += mainwindow.h \
    database/repository.h \
    database/dataobject.h \
    map/mapwidget.h \
    map/mapgraphicsview.h \
    map/mapdockwidget.h \
    character/character.h \
    skills/skill.h \
    database/orm.h \
    database/databridge.h \
    skills/skillsdockwidget.h \
    ui/enumdelegate.h \
    skills/skilledit.h \
    ui/datawidgetmapper.h \
    character/charactersdockwidget.h \
    ui/imainwindowfacet.h \
    skills/skillview.h \
    mainapp.h \
    map/mapview.h

FORMS    += mainwindow.ui \
    map/mapwidget.ui \
    map/mapdockwidget.ui \
    skills/skillsdockwidget.ui \
    skills/skilledit.ui \
    character/charactersdockwidget.ui

RESOURCES += \
    resources.qrc
