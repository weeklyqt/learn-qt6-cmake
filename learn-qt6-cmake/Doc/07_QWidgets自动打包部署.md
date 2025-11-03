# Qt6 CMake：QWidgets 自动打包部署

本节通过一个简单的 C++ Qt 项目示例展示如何部署 Qt Widgets 应用程序。我们将详细介绍如何使用CMake的部署功能。

## 工程结构
项目的基本结构如下：
```
BuildWidgetAppAndDeploy/
├── CMakeLists.txt
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
└── mainwindow.ui
```

## CMake部署配置
前面我们已经介绍了QWidget工程的基本结构，这里重点关注部署相关的CMake配置。以往使用qmake都需要手动使用windeployqt等工具进行打包，而现在CMake接口则可以自动完成这些工作。

首先在CMakeLists.txt中添加部署相关的配置：
```cmake
cmake_minimum_required(VERSION 3.16)
project(BuildWidgetAppAndDeploy VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# 设置安装目录，可根据需要修改
if(WIN32)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")
else()
    set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()

# 添加可执行文件
qt_add_executable(BuildWidgetAppAndDeploy
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# 链接Qt库
target_link_libraries(BuildWidgetAppAndDeploy PRIVATE Qt6::Widgets)

# 生成部署脚本
qt_generate_deploy_app_script(
    TARGET BuildWidgetAppAndDeploy
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR # 允许在所有平台上生成脚本
)

# 配置安装规则
install(TARGETS BuildWidgetAppAndDeploy
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
install(SCRIPT ${deploy_script})
```

## 部署命令详解
qt_generate_deploy_app_script() 命令的主要参数说明：
- TARGET：指定要部署的目标应用程序
- OUTPUT_SCRIPT：生成的部署脚本的变量名
- NO_UNSUPPORTED_PLATFORM_ERROR：允许在所有平台上生成脚本，即使某些平台可能不完全支持

## 部署步骤
1. 构建项目：
```bash
# 在项目根目录下
mkdir build
cd build
cmake ..
cmake --build .
```

2. 安装和部署：
```bash
# Windows/Linux
cmake --install . --prefix "./install"  # 指定安装目录为build/install

# macOS
cmake --install . --prefix "./BuildWidgetAppAndDeploy.app"
```

也可以在Qt Creator的项目页面选中部署目标install，再次运行将会自动部署。

## 部署后的目录结构
部署后的目录结构因平台而异：

### Windows
参考Windows平台效果
```
install/
├── bin/
│   ├── BuildWidgetAppAndDeploy.exe
│   ├── Qt6Core.dll
│   ├── Qt6Gui.dll
│   ├── Qt6Widgets.dll
│   └── platforms/
└── plugins/
```

## 处理第三方依赖
如果项目使用了Qt之外的第三方库，需要手动配置这些库的部署：

```cmake
# 示例：部署第三方动态库
if(WIN32)
    install(FILES 
        "${THIRD_PARTY_LIB_DIR}/example.dll"
        DESTINATION bin
    )
endif()
```

# 参考文献
- https://doc.qt.io/qt-6/cmake-deployment.html