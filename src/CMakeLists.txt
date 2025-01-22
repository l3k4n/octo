set(CMAKE_PREFIX_PATH ~/Qt/6.7.2/gcc_64/lib/cmake)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_subdirectory(octocore)
add_subdirectory(gui)
add_subdirectory(webcore)
