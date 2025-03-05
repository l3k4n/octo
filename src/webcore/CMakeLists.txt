find_package(ICU 70.1 COMPONENTS uc REQUIRED)

set(WEBCORE_GENERATED_DIR "${CMAKE_BINARY_DIR}/_generated")
set(WEBCORE_SCRIPTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/scripts")

add_library(webcore)
target_include_directories(webcore PUBLIC include ${WEBCORE_GENERATED_DIR})
target_link_libraries(webcore PRIVATE Loguru ICU::uc octocore)

add_executable(webcore_test)
target_link_libraries(webcore_test PRIVATE webcore Loguru Catch2WithMain nlohmann_json::nlohmann_json octocore)

add_subdirectory(src)

catch_discover_tests(webcore_test)
