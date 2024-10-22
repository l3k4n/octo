add_library(webcore)
add_subdirectory(src) # will add .cpp sources to webcore
target_include_directories(webcore PUBLIC include src)
target_link_libraries(webcore PRIVATE Loguru)
