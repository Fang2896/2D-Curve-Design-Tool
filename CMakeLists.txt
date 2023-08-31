cmake_minimum_required(VERSION 3.25)
project(2D-Curve-Design-Tool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.15.2/5.15.2/mingw81_64")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/Sources/Headers
        ${PROJECT_SOURCE_DIR}/Sources/Resources
        ${PROJECT_SOURCE_DIR}/Sources/Utils/Headers
        ${PROJECT_SOURCE_DIR}/Sources/Objects/Headers

        # python
        # D:/Anaconda/envs/UniverseEnv/include

        # third party lib
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
set(QRC_SOURCE_FILES Sources/res.qrc)
qt_add_resources(${QRC_SOURCE_FILES})

add_executable(${PROJECT_NAME}
        Sources/main.cpp
        Sources/mainwindow.cpp
        Sources/Headers/mainwindow.h
        Sources/Forms/mainwindow.ui
        Sources/OGLManager.cpp
        Sources/Headers/OGLManager.h
        Sources/Objects/Headers/Grid.h
        ${QRC_SOURCE_FILES}
        Sources/Objects/Points.cpp
        Sources/Objects/Headers/Points.h
        Sources/Utils/Shader.cpp
        Sources/Utils/Headers/Shader.h
        Sources/Objects/Grid.cpp
        Sources/Objects/Headers/Grid.h
        Sources/Objects/Curve.cpp
        Sources/Objects/Headers/Curve.h
        Sources/Utils/Algorithms.cpp
        Sources/Utils/Headers/Algorithms.h)

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )