set(HTMLPARSER_SOURCES 
  htmlparser/input_preprocessor.cpp
  htmlparser/lexer.cpp
  htmlparser/token.cpp
  htmlparser/treebuilder.cpp
  htmlparser/treebuilder_impl.cpp
  htmlparser/treebuilder_token.cpp
  htmlparser/unicode.cpp
)

set(HTMLPARSER_TEST_SOURCES 
  htmlparser/input_preprocessor_test.cpp
  htmlparser/lexer_test.cpp
  # htmlparser/token_test.cpp
  # htmlparser/treebuilder_test.cpp
  # htmlparser/treebuilder_impl_test.cpp
  # htmlparser/treebuilder_token_test.cpp
  # htmlparser/unicode_test.cpp
)

set(DOM_SOURCES 
  dom/attr.cpp
  dom/attrlist.cpp
  dom/document.cpp
  dom/element.cpp
  dom/node.cpp
  dom/nodelist.cpp
  dom/text.cpp
)

set(HTML_SOURCES 
  html/collection.cpp
  html/htmlanchorelement.cpp
  html/htmlbodyelement.cpp
  html/htmlbuttonelement.cpp
  html/htmldivelement.cpp
  html/htmlelement.cpp
  html/htmlformelement.cpp
  html/htmlheadelement.cpp
  html/htmlheadingelement.cpp
  html/htmlhtmlelement.cpp
  html/htmlimageelement.cpp
  html/htmlinputelement.cpp
  html/htmllinkelement.cpp
  html/htmlparagraphelement.cpp
  html/htmlspanelement.cpp
  html/htmlstyleelement.cpp
  html/htmltitleelement.cpp
  html/htmlunknownelement.cpp
  html/tagname.cpp
)

target_sources(webcore PRIVATE ${HTMLPARSER_SOURCES} ${HTML_SOURCES} ${DOM_SOURCES})
target_sources(parsertest PRIVATE ${HTMLPARSER_TEST_SOURCES})
target_compile_options(webcore PRIVATE -Wimplicit-fallthrough -DDCHECK_IS_ON)
