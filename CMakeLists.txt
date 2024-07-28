cmake_minimum_required(VERSION 3.16)

project(main VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_PREFIX_PATH ~/Qt/6.7.2/gcc_64/lib/cmake)
set(SKIP_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()
qt_add_executable(main main.cpp)

target_link_libraries(main PRIVATE Qt6::Widgets)

set_target_properties(main PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
