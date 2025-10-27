cmake_minimum_required(VERSION 3.16)

project(BuildWidgetAppWithResource VERSION 0.1 LANGUAGES CXX)

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

add_executable(BuildWidgetAppWithResource
    ${PROJECT_SOURCES}
)

qt_add_resources(BuildWidgetAppWithResource imageresources
    PREFIX "/images"
    FILES assets/github.png
)

target_link_libraries(BuildWidgetAppWithResource PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(BuildWidgetAppWithResource PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
