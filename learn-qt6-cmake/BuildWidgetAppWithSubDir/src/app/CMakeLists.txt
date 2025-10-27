set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

add_executable(BuildWidgetAppWithSubDir
    ${PROJECT_SOURCES}
)

target_link_libraries(BuildWidgetAppWithSubDir PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(BuildWidgetAppWithSubDir PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
