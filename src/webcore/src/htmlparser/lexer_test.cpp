#include "htmlparser/lexer.h"

#include <sstream>

#include "catch2/catch_test_macros.hpp"
#include "htmlparser/input_preprocessor.h"
#include "htmlparser/token.h"

struct LexerFixture {
    LexerFixture()
        : input(
              "<bODy><div attr1 attr2 = \"value\"attr3='value' attr4 = 'value'>< / div></Div   >"),
          preprocessor(input),
          lexer(preprocessor),
          token(lexer.next()) {}

    std::istringstream input;
    HTMLInputPreprocessor preprocessor;
    mutable HTMLLexer lexer;
    HTMLToken& token;
};

#define ExpectToken(tokenType, tokenData, attrCount)          \
    REQUIRE(token.type() == HTMLToken::TokenType::tokenType); \
    REQUIRE(token.data() == tokenData);                       \
    REQUIRE(token.attributes().size() == attrCount);

#define ExpectAttribute(attr, attrName, attrVal) \
    REQUIRE(attr.name == attrName);              \
    REQUIRE(attr.value == attrVal);

TEST_CASE_PERSISTENT_FIXTURE(LexerFixture, "Tests with MyFixture") {
    REQUIRE(!lexer.eof());

    SECTION("properly handles mixed case tag name") { ExpectToken(StartTag, "body", 0); }

    SECTION("properly handles attributes") {
        token = lexer.next();
        ExpectToken(StartTag, "div", 4);
        ExpectAttribute(token.attributes()[0], "attr1", "");
        ExpectAttribute(token.attributes()[1], "attr2", "value");
        ExpectAttribute(token.attributes()[2], "attr3", "value");
        ExpectAttribute(token.attributes()[3], "attr4", "value");
    }

    SECTION("does not create tag for text that look like tags") {
        token = lexer.next();
        ExpectToken(CharacterBuffer, "<", 0);
        token = lexer.next();
        ExpectToken(CharacterBuffer, " / div>", 0);
    }

    SECTION("properly handles end tag") {
        token = lexer.next();
        ExpectToken(EndTag, "div", 0);
    }
}
