#include "webcore/internal/cssparser/propertyvalueparser.h"

#include "catch2/catch_test_macros.hpp"
#include "webcore/css/values/colorvalue.h"
#include "webcore/css/values/value_cast.h"
#include "webcore/css/values/widekeywordvalue.h"
#include "webcore/internal/cssparser/tokenstream.h"

using namespace CSS;

#define EXPECT_COLOR(_r, _g, _b, _a)                                                               \
    {                                                                                              \
        stream.skipWhitespace();                                                                   \
        auto value = css_value_cast<ColorValue*>(CssPropertyValueParser::parseColorValue(stream)); \
        REQUIRE(value);                                                                            \
        REQUIRE(int(value->rgba().r) == _r);                                                       \
        REQUIRE(int(value->rgba().g) == _g);                                                       \
        REQUIRE(int(value->rgba().b) == _b);                                                       \
        REQUIRE(int(value->rgba().a) == _a);                                                       \
    }

#define EXPECT_WIDE_KEYWORD(_k)                                                      \
    {                                                                                \
        stream.skipWhitespace();                                                     \
        WideKeywordValue* value;                                                     \
        REQUIRE_NOTHROW(value = css_value_cast<WideKeywordValue*>(                   \
                            CssPropertyValueParser::parseWideKeywordValue(stream))); \
        REQUIRE(value);                                                              \
        REQUIRE(*value == _k);                                                       \
    }

TEST_CASE("PropertyValue parser correctly parses values", "[cssparser]") {
    SECTION("Parse wide keywords") {
        CssTokenStream stream("initial inherit unset");

        EXPECT_WIDE_KEYWORD(WideKeywordValue::Initial);
        EXPECT_WIDE_KEYWORD(WideKeywordValue::Inherit);
        EXPECT_WIDE_KEYWORD(WideKeywordValue::Unset);
    }

    SECTION("Parse color keywords") {
        CssTokenStream stream("red transparent");

        EXPECT_COLOR(255, 0, 0, 255);
        EXPECT_COLOR(0, 0, 0, 0);
    }

    SECTION("Parse hex colors") {
        CssTokenStream stream("#ABCDEFD4 #abcdefd4");

        EXPECT_COLOR(171, 205, 239, 212);
        EXPECT_COLOR(171, 205, 239, 212);
    }

    SECTION("Resolve and parse values from property id") {
        CssTokenStream stream("#ABCDEFD4 inherit");
        CssPropertyValueParser parser(stream);
        PropertyMap map;

        REQUIRE(parser.parseValue(PropertyId::Color, map));
        REQUIRE(map.get(PropertyId::Color));
        auto color_val = css_value_cast<ColorValue*>(map.get(PropertyId::Color));
        REQUIRE(int(color_val->rgba().r) == 171);
        REQUIRE(int(color_val->rgba().g) == 205);
        REQUIRE(int(color_val->rgba().b) == 239);
        REQUIRE(int(color_val->rgba().a) == 212);

        stream.skipWhitespace();
        REQUIRE(parser.parseValue(PropertyId::BackgroundColor, map));
        REQUIRE(map.get(PropertyId::BackgroundColor));
        auto bg_val = css_value_cast<WideKeywordValue*>(map.get(PropertyId::BackgroundColor));
        REQUIRE(*bg_val == WideKeywordValue::Inherit);
    }
}
