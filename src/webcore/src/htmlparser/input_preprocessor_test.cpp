#include "htmlparser/input_preprocessor.h"

#include <sstream>

#include "catch2/catch_test_macros.hpp"
#include "htmlparser/unicode.h"

TEST_CASE("preprocessor properly handles peek and putback", "[HTMLInputPreprocessor]") {
    std::istringstream input("ABC");
    HTMLInputPreprocessor preprocessor(input);

    REQUIRE(preprocessor.peek() == 'A');
    REQUIRE(preprocessor.advance() == 'A');
    REQUIRE(preprocessor.peek() == 'B');

    preprocessor.put_back('A');

    REQUIRE(preprocessor.peek() == 'A');
    REQUIRE(preprocessor.advance() == 'A');
    REQUIRE(preprocessor.peek() == 'B');
}

TEST_CASE("preprocessor correctly processes valid UTF-8 input", "[HTMLInputPreprocessor]") {
    SECTION("ascii input") {
        std::istringstream input("Hello");
        HTMLInputPreprocessor preprocessor(input);

        REQUIRE(preprocessor.advance() == 'H');
        REQUIRE(preprocessor.advance() == 'e');
        REQUIRE(preprocessor.advance() == 'l');
        REQUIRE(preprocessor.advance() == 'l');
        REQUIRE(preprocessor.advance() == 'o');
    }

    SECTION("two-byte UTF-8") {
        std::istringstream input("\xC2\xA9");  // Copyright symbol ©
        HTMLInputPreprocessor preprocessor(input);

        codepoint_t codepoint = preprocessor.advance();
        REQUIRE(codepoint == 0xA9);
    }

    SECTION("three-byte UTF-8") {
        std::istringstream input("\xE2\x82\xAC");  // Euro sign €
        HTMLInputPreprocessor preprocessor(input);

        codepoint_t codepoint = preprocessor.advance();
        REQUIRE(codepoint == 0x20AC);
    }

    SECTION("four-byte UTF-8") {
        std::istringstream input("\xF0\x9F\x98\x81");  // Smiling emoji 😁
        HTMLInputPreprocessor preprocessor(input);

        codepoint_t codepoint = preprocessor.advance();
        REQUIRE(codepoint == 0x1F601);
    }
}

TEST_CASE("preprocessor correctly processes invalid input", "[HTMLInputPreprocessor]") {
    std::istringstream input("\xE2\x28\xA1");  // Invalid sequence
    HTMLInputPreprocessor preprocessor(input);

    codepoint_t codepoint = preprocessor.advance();
    REQUIRE(codepoint == REPLACEMENT_CHAR);
}
