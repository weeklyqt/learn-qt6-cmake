# Qt6 CMake：QWidgets 自动打包部署

本节通过一个简单的 C++ Qt 项目示例展示如何部署 Qt Widgets 应用程序。
```
cmake_minimum_required(VERSION 3.16)

project(BuildWidgetAppAndDeploy VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

qt_add_executable(BuildWidgetAppAndDeploy main.cpp)
target_link_libraries(BuildWidgetAppAndDeploy PRIVATE Qt6::Core)
```
您需要指示 CMake 将应用程序目标安装到适当的位置。在 macOS 上，捆绑包直接安装到 ${CMAKE_INSTALL_PREFIX} 中，在其他平台上则安装到其下的 "bin" 目录中。
```
install(TARGETS BuildWidgetAppAndDeploy
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
```

请注意， qt_standard_project_setup() 会拉入 CMake 的 GNUInstallDirs.cmake 。这就是定义 CMAKE_INSTALL_BINDIR 变量的内容。

您还需要生成一个部署脚本 。部署脚本是在安装时执行的 CMake 代码。此代码负责收集运行时依赖项并将其复制到安装目录。
```
qt_generate_deploy_app_script(
    TARGET BuildWidgetAppAndDeploy
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
```
qt_generate_deploy_app_script() 命令在构建目录中生成部署脚本。生成的脚本文件的文件名存储在 deploy_script 变量中。install install(SCRIPT) 调用指示 CMake 在安装时运行该脚本。
该项目可以使用 cmake --install . 或 ninja install 安装，就像任何其他基于 CMake 的项目一样。安装完成后，安装目录包含运行应用程序所需的共享库和资源。换句话说，安装会生成一个独立的目录，可供打包，例如使用 cpack 打包。