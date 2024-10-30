#include "lexer.h"

#include "catch2/catch_test_macros.hpp"
#include "token.h"
#include "webcore/internal/generic_input_stream.h"

struct LexerFixture {
    LexerFixture() : preprocessor(input), lexer(preprocessor), token(lexer.next()) {}

    const std::string input =
        "<bODy><div attr1 attr2 = \"value\"attr3='value' attr4 = 'value'>< / div></Div   >";
    GenericInputStream preprocessor;
    mutable HTMLLexer lexer;
    HTMLToken& token;
};

#define ExpectToken(tokenType, tokenData, attrCount)          \
    REQUIRE(token.type() == HTMLToken::TokenType::tokenType); \
    REQUIRE(token.data() == u##tokenData);                    \
    REQUIRE(token.attributes().size() == attrCount);

#define ExpectAttribute(attr, attrName, attrVal) \
    REQUIRE(attr.first == u##attrName);          \
    REQUIRE(attr.second == u##attrVal);

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
