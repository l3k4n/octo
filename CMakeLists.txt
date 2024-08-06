cmake_minimum_required(VERSION 3.16)

project(octo VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_PREFIX_PATH ~/Qt/6.7.2/gcc_64/lib/cmake)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/gui/tabbar.cpp
    src/gui/delegates/tabbutton.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)


qt_standard_project_setup()
qt_add_executable(octo ${SOURCES})

target_include_directories(octo PRIVATE src/gui src/gui/delegates)
target_link_libraries(octo PRIVATE Qt6::Widgets)

set_target_properties(octo PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
