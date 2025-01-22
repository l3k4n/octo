set(CSSPARSER_SOURCES
  parser.cpp
  propertyidparser.cpp
  propertyvalueparser.cpp
  selectorparser.cpp
  token.cpp
  tokenstream.cpp
)

set(CSSPARSER_TEST_SOURCES
  parser_test.cpp
  propertyidparser_test.cpp
  propertyvalueparser_test.cpp
  selectorparser_test.cpp
  tokenstream_test.cpp
)

target_sources(webcore PRIVATE ${CSSPARSER_SOURCES})
target_sources(webcore_test PRIVATE ${CSSPARSER_TEST_SOURCES})
