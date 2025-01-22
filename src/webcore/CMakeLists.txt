find_package(ICU 70.1 COMPONENTS uc REQUIRED)

add_library(webcore)
target_include_directories(webcore PUBLIC include)
target_link_libraries(webcore PRIVATE Loguru ICU::uc octocore)

add_executable(webcore_test)
target_link_libraries(webcore_test PRIVATE webcore Loguru Catch2WithMain nlohmann_json::nlohmann_json octocore)

add_subdirectory(src)

catch_discover_tests(webcore_test)
