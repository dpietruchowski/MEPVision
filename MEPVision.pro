TEMPLATE = lib
TARGET = mep_vision
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11

LIBS += -L"/usr/lib/x86_64-linux-gnu" -lboost_system

DEFINES += MEP_LIBRARY

SOURCES += main.cpp \
    mepobject.cpp \
    mepcomposite.cpp \
    mepgene.cpp \
    meptypes.cpp

HEADERS += \
    mep_global.h \
    mepobject.h \
    meptypes.h \
    mepcomposite.h \
    mepgene.h

    library.path = $$_PRO_FILE_PWD_/../lib
    library.files = $$OUT_PWD/*.so*
INSTALLS += library
    includes.path = $$_PRO_FILE_PWD_/../inc
    includes.files = $$_PRO_FILE_PWD_/*.h
INSTALLS += includes

message($$OUT_PWD)
