#include "webcore/internal/cssparser/lexer.h"

#include "catch2/catch_test_macros.hpp"
#include "webcore/internal/cssparser/token.h"

#define Expect(_type)                     \
    do {                                  \
        auto tok = lexer.next();          \
        REQUIRE(tok.type() == _type);     \
        REQUIRE(tok.value().size() == 0); \
        REQUIRE(tok.unit().size() == 0);  \
    } while (false)

#define Expect2(_type, val)              \
    do {                                 \
        auto tok = lexer.next();         \
        REQUIRE(tok.type() == _type);    \
        REQUIRE(tok.value() == u##val);  \
        REQUIRE(tok.unit().size() == 0); \
    } while (false)

#define Expect3(_type, val, unt)        \
    do {                                \
        auto tok = lexer.next();        \
        REQUIRE(tok.type() == _type);   \
        REQUIRE(tok.value() == u##val); \
        REQUIRE(tok.unit() == u##unt);  \
    } while (false)

auto src = R"(abcdef {
    /* .......... */
               color 


    : red;
               margin   : 1px

    ;}/* 
    color: blue;
               }
               )";

class TestLexer : CssLexer {
public:
    TestLexer(const std::string& in) : CssLexer(in) {}

    using CssLexer::next;
};

TEST_CASE("CSSLexer emits proper tokens", "[cssparser]") {
    TestLexer lexer(src);

    Expect2(Ident, "abcdef");
    Expect(WhiteSpace);
    Expect(LeftBrace);
    Expect(WhiteSpace);
    Expect(WhiteSpace);
    Expect2(Ident, "color");
    Expect(WhiteSpace);
    Expect(Colon);
    Expect(WhiteSpace);
    Expect2(Ident, "red");
    Expect(SemiColon);
    Expect(WhiteSpace);
    Expect2(Ident, "margin");
    Expect(WhiteSpace);
    Expect(Colon);
    Expect(WhiteSpace);
    Expect3(Dimension, "1", "px");
    Expect(WhiteSpace);
    Expect(SemiColon);
    Expect(RightBrace);
    Expect(EndOfFile);
}
