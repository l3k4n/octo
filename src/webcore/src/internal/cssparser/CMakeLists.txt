set(CSSPARSER_SOURCES
  lexer.cpp
  token.cpp
)

set(CSSPARSER_TEST_SOURCES
  lexer_test.cpp
)

target_sources(webcore PRIVATE ${CSSPARSER_SOURCES})
target_sources(parsertest PRIVATE ${CSSPARSER_TEST_SOURCES})
