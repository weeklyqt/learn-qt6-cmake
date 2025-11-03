# Qt6 CMake：Qt Quick 程序构建
和构建Qt Widget应用类似，Qt Quick应用也可以使用CMake构建。本节将介绍如何使用CMake构建Qt Quick应用。

## 1. 创建项目
首先，我们需要创建一个Qt Quick项目。可以使用Qt Creator创建一个新的Qt Quick项目。

## 2. 配置CMakeLists.txt
```
cmake_minimum_required(VERSION 3.16)

project(BuildQuickApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appBuildQuickApp
    main.cpp
)

#详细参考https://doc.qt.io/qt-6/qt-add-qml-module.html
qt_add_qml_module(appBuildQuickApp
    URI BuildQuickApp
    VERSION 1.0
    QML_FILES
        Main.qml
    RESOURCES
        assets/github.png
)

target_link_libraries(appBuildQuickApp
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appBuildQuickApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

```
和QWidget不同的是，这里新引入了`qt_add_qml_module`函数，用于添加Qt Quick模块。最重要的几个参数：
- `URI`：模块的URI，用于在QML中引用模块。
- `VERSION`：模块的版本号。
- `QML_FILES`：模块中的QML文件。
- `RESOURCES`：模块中的资源文件。
```
qt_add_qml_module(appBuildQuickApp
    URI BuildQuickApp
    VERSION 1.0
    QML_FILES
        Main.qml
    RESOURCES
        assets/github.png
)
```
这个命令把BuildQuickApp模块添加到appBuildQuickApp可执行文件中。
比如github.png文件的资源文件的路径是qrc:/qt/qml/BuildQuickApp/assets/github.png。其中qrc:/qt/qml/是QML引擎默认导入的路径之一。
并且这个脚本还会执行 QML script complier，把QML文件编译成C++代码，并生成对应的头文件和源文件，供C++代码使用。

QML里一共有三个加速qml代码运行效率的工具，分别是：
- qmlcachegen: 提前编译 QML 文档生成缓存的工具。
- QML type compiler：一种提前将 QML 类型编译为 C++ 的工具。
- QML script compiler（仅商业版可用）：用于编译 QML 中的函数和表达式的工具。


## 3. 编写代码
在`main.cpp`中，我们需要初始化Qt Quick应用，并加载QML文件。
```
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qDebug() << "Import paths:" << engine.importPathList();

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("BuildQuickApp", "Main");

    return app.exec();
}
```

这里需要注意，Qt加载QML的曾经是直接使用`engine.load(QUrl(QStringLiteral("qrc:/Main.qml")))`，但是从Qt6开始，QML引擎默认导入的路径之一是`qrc:/qt/qml/`，所以这里需要使用`engine.loadFromModule("BuildQuickApp", "Main")`来加载QML文件。

另外一种方式还支持QQuickView，但是这种方式不推荐使用，因为QQuickView已经过时了。

# 参考材料
https://doc.qt.io/qt-6/qtqml-tooling.html
https://doc.qt.io/qt-6/cmake-build-qml-application.html