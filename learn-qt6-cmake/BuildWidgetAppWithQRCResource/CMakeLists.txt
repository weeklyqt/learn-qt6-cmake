cmake_minimum_required(VERSION 3.16)

project(BuildWidgetAppWithQRCResource VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

qt_add_resources(PROJECT_SOURCES resources.qrc)

add_executable(BuildWidgetAppWithQRCResource
    ${PROJECT_SOURCES}
)

target_link_libraries(BuildWidgetAppWithQRCResource PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(BuildWidgetAppWithQRCResource PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
