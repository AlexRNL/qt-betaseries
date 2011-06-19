#-------------------------------------------------
#
# Project created by QtCreator 2011-04-28T21:39:14
#
#-------------------------------------------------

QT       += core gui network xml

TARGET = QtBetaseries
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    betaseries.cpp \
    showresult.cpp \
    request.cpp \
    requeststatus.cpp \
    requestshowsearch.cpp

HEADERS  += mainwindow.h \
    betaseries.h \
    showresult.h \
    request.h \
    requeststatus.h \
    requestshowsearch.h

FORMS    += mainwindow.ui

RESOURCES += \
    ressources.qrc
