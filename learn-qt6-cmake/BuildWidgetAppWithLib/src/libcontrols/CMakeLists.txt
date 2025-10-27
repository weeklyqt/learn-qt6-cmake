qt_add_library(controls SHARED
    cpushbutton.cpp
    cpushbutton.h
)
target_link_libraries(controls PRIVATE Qt6::Widgets)
target_include_directories(controls INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
