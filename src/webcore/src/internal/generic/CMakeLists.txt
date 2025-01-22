set(GENERIC_SOURCES inputstream.cpp)
set(GENERIC_TEST_SOURCES inputstream_test.cpp)

target_sources(webcore PRIVATE ${GENERIC_SOURCES})
target_sources(webcore_test PRIVATE ${GENERIC_TEST_SOURCES})
