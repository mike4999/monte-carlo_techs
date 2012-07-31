TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    process_mem_usage.h \
    performancesaver.h \
    solving_ode.h \
    pathbuilder.h \
    simulationcontextfactory.h \
    typicalsimcontextfactory.h \
    treesimcontextfactory.h

SOURCES += \
    test.cpp \
    process_mem_usage.cpp \
    performancesaver.cpp \
    pathbuilder.cpp \
    treesimcontextfactory.cpp

OTHER_FILES += \
    run.sh \
    plots.rb \
    Makefile \
    README.md

unix:!macx:!symbian: LIBS += -L$$PWD/../../lib/ -lmonte_carlo

INCLUDEPATH += $$PWD/../../lib/
DEPENDPATH += $$PWD/../../lib/