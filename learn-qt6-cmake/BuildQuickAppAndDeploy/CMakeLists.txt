cmake_minimum_required(VERSION 3.16)

project(BuildQuickAppAndDeploy VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appBuildQuickAppAndDeploy
    main.cpp
)

#详细参考https://doc.qt.io/qt-6/qt-add-qml-module.html
qt_add_qml_module(appBuildQuickAppAndDeploy
    URI BuildQuickAppAndDeploy
    VERSION 1.0
    QML_FILES
        Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appBuildQuickAppAndDeploy PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appBuildQuickAppAndDeploy
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appBuildQuickAppAndDeploy
    PRIVATE Qt6::Quick
)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/output)
include(GNUInstallDirs)
install(TARGETS appBuildQuickAppAndDeploy
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

#参考文档 https://doc-snapshots.qt.io/qt6-6.8/cmake-deployment.html
qt_generate_deploy_qml_app_script(
    TARGET appBuildQuickAppAndDeploy
    OUTPUT_SCRIPT deploy_script
)
install(SCRIPT ${deploy_script})
