#TEMPLATE = lib
TEMPLATE = app
TARGET = mep_vision
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11

LIBS += -L"/usr/lib/x86_64-linux-gnu" -lboost_system -lopencv_imgproc
LIBS += -lopencv_highgui -lopencv_core

DEFINES += MEP_LIBRARY

SOURCES += main.cpp \
    meptypes.cpp \
    core/mepobject.cpp \
    core/mepcomposite.cpp \
    core/mepgene.cpp \
    core/mepchromosome.cpp \
    core/meppopulation.cpp \
    generator/mepobjectgenerator.cpp \
    generator/mepgenerator.cpp \
    fitness/mepfitness.cpp \
    fitness/hamming.cpp \
    fitness/hausdorff.cpp \
    fitness/hausdorffcanny.cpp \
    fitness/hausdorffsmall.cpp \
    gene/functiongene.cpp \
    gene/functionset.cpp \
    gene/terminalgene.cpp \
    gene/terminalset.cpp \
    gene/gene.cpp

HEADERS += \
    mep_global.h \
    meptypes.h \
    core/mepobject.h \
    core/mepcomposite.h \
    core/mepgene.h \
    core/mepchromosome.h \
    core/meppopulation.h \
    generator/generator.h \
    generator/mepobjectgenerator.h \
    generator/mepgenerator.h \
    fitness/mepfitness.h \
    fitness/hamming.h \
    fitness/hausdorff.h \
    fitness/hausdorffcanny.h \
    fitness/hausdorffsmall.h \
    gene/functiongene.h \
    gene/functionset.h \
    gene/terminalgene.h \
    gene/terminalset.h \
    gene/gene.h \
    functions.h

    library.path = $$_PRO_FILE_PWD_/../lib
    library.files = $$OUT_PWD/*.so*
INSTALLS += library
    includes.path = $$_PRO_FILE_PWD_/../inc
    includes.files = $$_PRO_FILE_PWD_/*.h
INSTALLS += includes

message($$OUT_PWD)
