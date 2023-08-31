cmake_minimum_required(VERSION 3.25)
project(2D-Curve-Design-Tool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.15.2/5.15.2/mingw81_64")

include_directories(
        src/include
        C:/cpplib/eigen
)

# link_libraries(
#     D:/Anaconda/envs/UniverseEnv/libs/python310.lib
# )

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# qrc
set(QRC_SOURCE_FILES src/res.qrc)
qt_add_resources(${QRC_SOURCE_FILES})

file(GLOB_RECURSE SOURCE_FILES
        src/*.cpp
        src/*.h
        src/*.ui
        )
add_executable(${PROJECT_NAME}
        ${QRC_SOURCE_FILES}
        ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )