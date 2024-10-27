find_package(ICU 70.1 COMPONENTS uc REQUIRED)

add_library(webcore)
target_include_directories(webcore PUBLIC include src)
target_link_libraries(webcore PRIVATE Loguru ICU::uc)

add_executable(parsertest)
target_link_libraries(parsertest PRIVATE webcore Loguru Catch2WithMain)

add_subdirectory(src) # adds webcore and parsertest targets
