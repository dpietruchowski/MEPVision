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
    gene/gene.cpp \
    selection/mepselectiontypes.cpp \
    selection/mepselection.cpp \
    selection/rouletteselection.cpp \
    selection/tournamentselection.cpp \
    operation/mepoperationtypes.cpp \
    operation/mepoperation.cpp \
    operation/mepmutation.cpp \
    operation/mepcrossover.cpp \
    operation/attributemutation.cpp \
    operation/argumentmutation.cpp \
    operation/combinedmutation.cpp \
    operation/mepoperationgenerator.cpp \
    fitness/mepfitnessgenerator.cpp \
    gene/morphogene.cpp

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
    functions.h \
    selection/mepselectiontypes.h\
    selection/mepselection.h \
    selection/rouletteselection.h \
    selection/tournamentselection.h \
    operation/mepoperationtypes.h \
    operation/mepoperation.h \
    operation/mepmutation.h \
    operation/mepcrossover.h \
    operation/attributemutation.h \
    operation/argumentmutation.h \
    operation/combinedmutation.h \
    operation/operation.h \
    operation/mepoperationgenerator.h \
    fitness/mepfitnessgenerator.h \
    gene/morphogene.h


    library.path = $$_PRO_FILE_PWD_/../lib
    library.files = $$OUT_PWD/*.so*
INSTALLS += library
    includes.path = $$_PRO_FILE_PWD_/../inc
    includes.files = $$_PRO_FILE_PWD_/*.h
INSTALLS += includes
    core.path = $$_PRO_FILE_PWD_/../inc/core
    core.files += $$_PRO_FILE_PWD_/core/*.h
INSTALLS += core
    gene.path = $$_PRO_FILE_PWD_/../inc/gene
    gene.files += $$_PRO_FILE_PWD_/gene/*.h
INSTALLS += gene
    fitness.path = $$_PRO_FILE_PWD_/../inc/fitness
    fitness.files += $$_PRO_FILE_PWD_/fitness/*.h
INSTALLS += fitness
    generator.path = $$_PRO_FILE_PWD_/../inc/generator
    generator.files += $$_PRO_FILE_PWD_/generator/*.h
INSTALLS += generator
    selection.path = $$_PRO_FILE_PWD_/../inc/selection
    selection.files += $$_PRO_FILE_PWD_/selection/*.h
INSTALLS += selection

message($$OUT_PWD)
