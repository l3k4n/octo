add_library(webcore)
target_include_directories(webcore PUBLIC include src)
target_link_libraries(webcore PRIVATE Loguru)

add_executable(parsertest)
target_link_libraries(parsertest PRIVATE webcore Loguru Catch2WithMain)

add_subdirectory(src) # adds webcore and parsertest targets
