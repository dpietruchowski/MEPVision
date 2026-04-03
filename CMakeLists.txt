cmake_minimum_required(VERSION 3.10)
project(MEPVision)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(OpenCV REQUIRED COMPONENTS core highgui imgcodecs imgproc)
find_package(Boost REQUIRED COMPONENTS system)

add_definitions(-DMEP_LIBRARY)

set(SOURCES
    main.cpp
    core/meptypes.cpp
    core/mepobject.cpp
    core/mepcomposite.cpp
    core/mepgene.cpp
    core/mepchromosome.cpp
    core/meppopulation.cpp
    generator/mepobjectgenerator.cpp
    generator/mepgenerator.cpp
    fitness/mepfitness.cpp
    fitness/hamming.cpp
    fitness/hausdorff.cpp
    fitness/hausdorffcanny.cpp
    fitness/hausdorffsmall.cpp
    gene/functiongene.cpp
    gene/functionset.cpp
    gene/terminalgene.cpp
    gene/terminalset.cpp
    gene/gene.cpp
    selection/mepselectiontypes.cpp
    selection/mepselection.cpp
    selection/rouletteselection.cpp
    selection/tournamentselection.cpp
    operation/mepoperationtypes.cpp
    operation/mepoperation.cpp
    operation/mepmutation.cpp
    operation/mepcrossover.cpp
    operation/attributemutation.cpp
    operation/argumentmutation.cpp
    operation/combinedmutation.cpp
    operation/mepoperationgenerator.cpp
    fitness/mepfitnessgenerator.cpp
    gene/morphogene.cpp
    gene/threshgene.cpp
    parser/mepparser.cpp
    mepalgorithm.cpp
    steadystatealgorithm.cpp
    generationalalgorithm.cpp
)

add_executable(mep_vision ${SOURCES})

target_include_directories(mep_vision PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(mep_vision PRIVATE
    Qt5::Core
    ${OpenCV_LIBS}
    Boost::system
)
