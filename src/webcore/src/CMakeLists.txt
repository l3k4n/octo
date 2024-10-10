set(HTMLPARSER_SOURCES 
	htmlparser/input_preprocessor.cpp
	htmlparser/lexer.cpp
	htmlparser/token.cpp
	htmlparser/unicode.cpp
)

target_sources(webcore PRIVATE ${HTMLPARSER_SOURCES})
