add_subdirectory(loguru)
add_subdirectory(Catch2)
add_subdirectory(nlohmann_json)

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(Catch)
