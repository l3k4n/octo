project(Loguru CXX)

add_library(Loguru SHARED src/loguru.cpp)
target_include_directories(Loguru PUBLIC include)
