cmake_minimum_required(VERSION 3.16)

project(BuildWidgetAppWithTranslations VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

#添加国际化工具模块
find_package(Qt6 REQUIRED COMPONENTS LinguistTools)

#配置需要的国际化的语种
qt_standard_project_setup(I18N_TRANSLATED_LANGUAGES en zh_CN)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

add_executable(BuildWidgetAppWithTranslations
    ${PROJECT_SOURCES}
)

target_link_libraries(BuildWidgetAppWithTranslations PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

#添加翻译文件到目标中
qt_add_translations(BuildWidgetAppWithTranslations)

#然后会自动生成ts文件，要更新翻译在build目录中执行cmake --build . --target update_translations
#或者在 QTC 中项目配置里勾选更新 xxx_lupdate 目标

