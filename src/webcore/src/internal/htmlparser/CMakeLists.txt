set(HTMLPARSER_SOURCES 
  lexer.cpp
  lexer_impl.cpp
  token.cpp
  treebuilder.cpp
  treebuilder_impl.cpp
  treebuilder_token.cpp
)

set(HTMLPARSER_TEST_SOURCES 
  jsonserializeddom.cpp
  lexer_test.cpp
  treebuilder_test.cpp
)

target_sources(webcore PRIVATE ${HTMLPARSER_SOURCES})
target_sources(webcore_test PRIVATE ${HTMLPARSER_SOURCES} ${HTMLPARSER_TEST_SOURCES})
