
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

qt_add_executable(BuildWidgetAppWithLib
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(BuildWidgetAppWithLib PRIVATE
    controls
    Qt${QT_VERSION_MAJOR}::Widgets
)
