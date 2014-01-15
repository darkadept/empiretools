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
    ui/enumdelegate.cpp \
    ui/datawidgetmapper.cpp \
    character/charactersdockwidget.cpp \
    mainapp.cpp \
    map/mapview.cpp \
    skills/skillcontroller.cpp \
    skills/skillview.cpp \
    ui/searchlistview.cpp

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
    ui/enumdelegate.h \
    ui/datawidgetmapper.h \
    character/charactersdockwidget.h \
    ui/imainwindowfacet.h \
    mainapp.h \
    map/mapview.h \
    skills/skillcontroller.h \
    skills/skillview.h \
    ui/searchlistview.h

FORMS    += mainwindow.ui \
    map/mapwidget.ui \
    map/mapdockwidget.ui \
    character/charactersdockwidget.ui \
    skills/skillview.ui \
    ui/searchlistview.ui

RESOURCES += \
    resources.qrc \
    skills/skills.qrc \
    map/map.qrc
