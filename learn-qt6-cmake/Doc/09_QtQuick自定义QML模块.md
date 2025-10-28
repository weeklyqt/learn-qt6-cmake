# Qt6 CMake：Qt Quick 自定义QML模块

本节介绍如何在Qt6的CMake工程中创建和使用自定义QML模块。我们将创建一个包含自定义控件的模块，并在主应用程序中使用它。

## 项目结构
```
BuildQuickAppWithCustomModule/
├── CMakeLists.txt          # 主项目CMake配置
├── main.cpp                # 主程序入口
├── Main.qml               # 主QML界面
└── CControls/             # 自定义QML模块目录
    ├── CMakeLists.txt     # 模块CMake配置
    ├── CButton.qml        # 自定义按钮组件
    ├── ctheme.h          # C++主题类头文件
    └── ctheme.cpp        # C++主题类实现
```

## 主项目配置
在主项目的`CMakeLists.txt`中，我们需要：
1. 配置项目基本信息
2. 设置QML导入路径
3. 添加可执行文件
4. 配置QML模块
5. 添加子目录
6. 链接依赖库

```cmake
cmake_minimum_required(VERSION 3.16)
project(BuildQuickAppWithCustomModule VERSION 0.1 LANGUAGES CXX)

# 设置C++标准要求
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 配置QML模块导入路径，确保能找到自定义模块
set(QT_QML_IMPORT_PATH
    ${QT_QML_IMPORT_PATH}
    ${CMAKE_BINARY_DIR}/CControls
)

# 查找Qt Quick模块
find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

# 使用Qt标准项目设置
qt_standard_project_setup(REQUIRES 6.5)

# 添加可执行文件
qt_add_executable(appBuildQuickAppWithCustomModule
    main.cpp
)

# 配置主程序的QML模块
qt_add_qml_module(appBuildQuickAppWithCustomModule
    URI BuildQuickAppWithCustomModule
    VERSION 1.0
    QML_FILES
        Main.qml
)

# 添加自定义控件模块目录
add_subdirectory(CControls)

# 设置应用程序属性
set_target_properties(appBuildQuickAppWithCustomModule PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 链接Qt Quick和自定义模块
target_link_libraries(appBuildQuickAppWithCustomModule
    PRIVATE Qt6::Quick
    CControls
)
```

## 自定义QML模块配置
在`CControls/CMakeLists.txt`中配置自定义模块：

```cmake
# 查找需要的Qt组件
find_package(Qt6 REQUIRED COMPONENTS Gui Quick)

# 创建QML模块
qt_add_qml_module(CControls
    URI CControls           # 模块的URI，在QML中使用
    VERSION 1.0            # 模块版本
    SOURCES                # C++源文件
        ctheme.h
        ctheme.cpp
    QML_FILES             # QML文件
        CButton.qml
)

# 链接必要的Qt库
target_link_libraries(CControls PRIVATE Qt6::Gui Qt6::Quick)
```

## 使用自定义模块
1. 在`main.cpp`中注册自定义模块：
```cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    
    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/BuildQuickAppWithCustomModule/Main.qml")));
    
    return app.exec();
}
```

2. 在`Main.qml`中导入和使用自定义模块：
```qml
import QtQuick
import QtQuick.Window
import CControls 1.0  // 导入自定义模块

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Custom QML Module Demo")

    CButton {
        anchors.centerIn: parent
        text: "Custom Button"
    }
}
```

## CMake命令说明

### qt_add_qml_module
这个命令用于创建QML模块，主要参数包括：
- URI: 模块的唯一标识符，在QML中用于导入
- VERSION: 模块版本号
- SOURCES: C++源文件列表
- QML_FILES: QML文件列表
- RESOURCE_PREFIX: 资源前缀（可选）
- IMPORTS: 依赖的其他QML模块（可选）

### QML导入路径设置
```cmake
set(QT_QML_IMPORT_PATH
    ${QT_QML_IMPORT_PATH}
    ${CMAKE_BINARY_DIR}/CControls
)
```
这个设置确保Qt Creator和运行时都能找到自定义QML模块。

## 部署配置
为了正确部署应用程序，需要添加以下配置：

```cmake
# 设置安装目录
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/output)
include(GNUInstallDirs)

# 配置安装规则
install(TARGETS appBuildQuickAppWithCustomModule
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 生成部署脚本
qt_generate_deploy_qml_app_script(
    TARGET appBuildQuickAppWithCustomModule
    OUTPUT_SCRIPT deploy_script
)
install(SCRIPT ${deploy_script})
```

## 注意事项
1. 确保QML_IMPORT_PATH正确设置，否则Qt Creator可能无法识别自定义模块
2. C++类需要正确注册到QML系统中才能在QML中使用
3. 模块的URI在整个项目中必须唯一
4. 注意版本号的管理，确保兼容性
5. 部署时需要确保所有QML模块都被正确打包

## 参考文献
- https://doc.qt.io/qt-6/cmake-qt6-qml-module.html
- https://doc.qt.io/qt-6/qtqml-modules-qmldir.html
- https://doc.qt.io/qt-6/qtqml-modules-cppplugins.html