cmake_minimum_required(VERSION 3.25)
project(HW1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/Sources/Headers
        ${PROJECT_SOURCE_DIR}/Sources/Resources
        D:/cpplib/eigen
)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# qrc
set(QRC_SOURCE_FILES Sources/res.qrc)
qt_add_resources(${QRC_SOURCE_FILES})

add_executable(
        HW1 Sources/main.cpp
        Sources/mainwindow.cpp
        Sources/Headers/mainwindow.h
        Sources/Forms/mainwindow.ui
        Sources/OGLManager.cpp
        Sources/Headers/OGLManager.h
        Sources/Headers/Grid.h
        ${QRC_SOURCE_FILES}
        Sources/Points.cpp
        Sources/Headers/Points.h
        Sources/Shader.cpp
        Sources/Headers/Shader.h
        Sources/Grid.cpp
        Sources/Headers/Grid.h Sources/CurveAlgorithms.cpp Sources/Headers/CurveAlgorithms.h)

target_link_libraries(HW1
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )