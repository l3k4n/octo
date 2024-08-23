set(HTMLPARSER_SOURCES 
	src/input_preprocessor.cpp
	src/lexer.cpp
	src/token.cpp
	src/unicode.cpp
)

add_library(htmlparser ${HTMLPARSER_SOURCES})
target_include_directories(htmlparser PUBLIC include src)

# build test executable
add_executable(parser src/main.cpp)
target_link_libraries(parser PRIVATE htmlparser)
