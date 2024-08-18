qt_add_library(core
    Tab.cpp
    Tab.h
    Window.cpp
    Window.h
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_link_libraries(core PRIVATE Qt6::Widgets)
