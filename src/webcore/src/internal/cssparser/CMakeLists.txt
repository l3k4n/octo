set(CSSPARSER_SOURCES
  token.cpp
  tokenstream.cpp
)

set(CSSPARSER_TEST_SOURCES
  tokenstream_test.cpp
)

target_sources(webcore PRIVATE ${CSSPARSER_SOURCES})
target_sources(parsertest PRIVATE ${CSSPARSER_TEST_SOURCES})
