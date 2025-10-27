
find_package(Qt6 REQUIRED COMPONENTS Gui Quick)

qt_add_qml_module(CControls
    URI CControls
    VERSION 1.0
    SOURCES
        ctheme.h
        ctheme.cpp
    QML_FILES
        CButton.qml
)

target_link_libraries(CControls PRIVATE Qt6::Gui Qt6::Quick)
