# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(BuildQuickAppWithSampleTranslations LANGUAGES CXX)

#1.添加 LinguistTools
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml LinguistTools)

#2..添加要支持的语言，需要符合 bcp47names标准
qt_standard_project_setup(REQUIRES 6.8 I18N_TRANSLATED_LANGUAGES en fr ja_JP zh_CN)

qt_add_executable(appBuildQuickAppWithSampleTranslations WIN32 MACOSX_BUNDLE main.cpp)

target_link_libraries(appBuildQuickAppWithSampleTranslations PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

#3.Main.qml将会被放在资源文件的 :/qt/qml/Translation/Main.qml
qt_add_qml_module(appBuildQuickAppWithSampleTranslations
    URI Translation
    QML_FILES
        Main.qml
)

#4.QtQuick可以支持自动翻译，设置 Qt.uiLanguage 就会自动加载qm文件，并发出语言更新的信号。
# Qt.uiLanguage 更新之后就会自动触发翻译更新，Qt源码在如下位置：
# C:\Qt\6.8.0\Src\qtdeclarative\src\qml\qml\qqmlapplicationengine.cpp +65

# void QQmlApplicationEnginePrivate::_q_loadTranslations()
# ...
# Locale locale(uiLanguage);
# translator->load(locale, QLatin1String("qml"), QLatin1String("_"), translationsDirectory, QLatin1String(".qm")))
# ...

# 具体加载文件为 translationsDirectory + "/" + "qml" + "_" + Qt.uiLanguage + ".qm"。
# 比如： QQmlApplicationEngine root qml文件：":/qt/qml/Translation/Main.qml"
# translationsDirectory 即为：":/qt/qml/Translation" +"/i18n"

# 如果 CMakeLists中没有正确配置qm文件的位置，会出现翻译失败的问题。
# 注意这里的 RESOURCE_PREFIX /qt/qml/Translation/i18n 和 Main.qml保持了一致。
qt_add_translations(appBuildQuickAppWithSampleTranslations
    RESOURCE_PREFIX /qt/qml/Translation/i18n
    TS_FILE_BASE qml
)

install(TARGETS appBuildQuickAppWithSampleTranslations
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_qml_app_script(
    TARGET appBuildQuickAppWithSampleTranslations
    OUTPUT_SCRIPT deploy_script
    MACOS_BUNDLE_POST_BUILD
    NO_UNSUPPORTED_PLATFORM_ERROR
    DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
)
install(SCRIPT ${deploy_script})
