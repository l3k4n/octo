set(HTMLPARSER_SOURCES 
  lexer.cpp
  lexer_impl.cpp
  token.cpp
  treebuilder.cpp
  treebuilder_impl.cpp
  treebuilder_token.cpp
)

set(HTMLPARSER_TEST_SOURCES 
  lexer_test.cpp
)

target_sources(webcore PRIVATE ${HTMLPARSER_SOURCES})
target_sources(parsertest PRIVATE ${HTMLPARSER_SOURCES} ${HTMLPARSER_TEST_SOURCES})
