# Qt6 CMake：Qt 多目录工程搭建
在 qmake 里，较大的工程都会考虑创建单独的 pri 文件，对项目子模块进行独立管理。本篇我们也介绍一下 CMake 的子目录功能。
当我们计划用更多编译目标扩展项目时，我们会把应用程序的源文件移到一个子目录中，并在其中创建一个新的 CMakeLists.txt 。
```
<project root>
|-- CMakeLists.txt
`-- src
    `-- app
        |-- CMakeLists.txt
        |-- main.cpp
        |-- mainwindow.cpp
        |-- mainwindow.h
        `-- mainwindow.ui
```
顶层的CMakeLists.txt
顶层的CMakeLists.txt 包含整个项目的配置、find_package 和add_subdirectory 调用：
```
cmake_minimum_required(VERSION 3.16)

project(BuildWidgetAppWithSubDir VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_subdirectory(src/app)
```
在该文件中配置的变量在子目录CMakeLists.txt文件中是可见的。
这里主要关注 add_subdirectory() ，函数原型：
```
add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL] [SYSTEM])
```
将一个子目录添加到构建系统中。
- source_dir：指定包含源代码和 CMakeLists.txt 文件的目录。可以是相对路径（相对于当前源码目录，这是最常见用法），也可以是绝对路径。
- binary_dir：指定编译输出文件（如目标文件、可执行文件等）的存放目录。同样支持相对路径（相对于当前构建目录）或绝对路径。如果未显式指定 binary_dir，则默认使用 source_dir 作为输出目录。
- EXCLUDE_FROM_ALL：可选参数。如果指定，该子目录中的目标（targets）默认不会被包含在“全部构建”中，除非被其他目标显式依赖。
- SYSTEM：可选参数。表示该目录中的头文件为“系统头文件”，在编译时会以系统包含路径的方式处理（例如，忽略某些警告）。
执行此命令时，CMake 会立即读取并处理 source_dir 中的 CMakeLists.txt 文件。处理完成后，再继续执行当前 CMakeLists.txt 中该命令之后的内容。
子目录CMakeLists.txt
应用程序的项目文件src/app/CMakeLists.txt 包含一个可执行程序：
```
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
```
这样的结构便于在项目中添加更多编译目标，如：库或单元测试。