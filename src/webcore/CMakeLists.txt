add_library(webcore)
target_include_directories(webcore PUBLIC include src)

add_subdirectory(src)

add_executable(parser src/main.cpp)
target_link_libraries(parser PRIVATE webcore)
