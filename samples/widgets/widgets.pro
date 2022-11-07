TARGET = qgeoview-samples-widgets
TEMPLATE = app
CONFIG-= console

include(../../lib/lib.pri)

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h
