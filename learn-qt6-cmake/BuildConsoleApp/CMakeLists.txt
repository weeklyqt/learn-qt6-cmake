#配置项目所需的最低 CMake 版本
#最低版本要求参考  https://doc-snapshots.qt.io/qt6-6.8/cmake-supported-cmake-versions.html
cmake_minimum_required(VERSION 3.16)

#设置 Project Name （项目名称） 和 Default Project Version （默认项目版本）。该参数告诉 CMake 该程序是用 C++ 编写的
project(BuildConsoleApp LANGUAGES CXX)

#Qt6 需要支持 C++ 版本 17 或更高版本的编译器。
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#CMake 查找 Qt6 并导入模块。REQUIRED表示不可或缺，缺少这些模块无法构建。
#如果找到对应的模块，也可能会设置部分变量，模块相关的变量在此 https://doc-snapshots.qt.io/qt6-6.8/cmake-variable-reference.html#module-variables
#实际上这个CMakeLists.txt不是直接由cmake.exe运行，在windows上而是一个qt-cmake.bat，比如：C:\Qt\6.5.7\mingw_64\bin\qt-cmake.bat
#在qt-cmake.bat中会设置一个toolchain.cmake,代码：set toolchain_path=%script_dir_path%\../lib/cmake/Qt6\qt.toolchain.cmake，里面指定了编译器的位置
#如果要使用cmake.exe直接构建，要设置CMAKE_PREFIX_PATH变量，在命令行里这么写-DCMAKE_PREFIX_PATH=$HOME/Qt/6.8.2/gcc_64
#还有一个非常重要的函数 qt_standard_project_setup ，封装在内部，会配置qt标准工程所需的内容，比如：CMAKE_AUTOMOC等
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

#添加可执行程序
add_executable(BuildConsoleApp
  main.cpp
)

#添加可执行程序要链接的库，自动包含对应模块的头文件
target_link_libraries(BuildConsoleApp Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS BuildConsoleApp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
