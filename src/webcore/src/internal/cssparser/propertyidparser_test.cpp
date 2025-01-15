#include "webcore/internal/cssparser/propertyidparser.h"

#include <algorithm>
#include <cctype>
#include <string>

#include "catch2/catch_test_macros.hpp"
#include "webcore/css/propertyid.h"
#include "webcore/internal/cssparser/tokenstream.h"

#define EXPECT(expected_id)                                 \
    {                                                       \
        stream.skipWhitespace();                            \
        auto val = parser.parseId();                        \
        REQUIRE(val.has_value());                           \
        REQUIRE(*val == int(CSS::PropertyId::expected_id)); \
    }

TEST_CASE("PropertyId parser correctly parses id's", "[cssparser]") {
#define APPEND_PROPERTY(_, css_name, ___) " " css_name
    std::string src = LONGHAND_PROPERTY_LIST(APPEND_PROPERTY);
#undef APPEND_PROPERTY
    std::string src_upper(src.size(), '\0');
    std::transform(src.begin(), src.end(), src_upper.begin(),
                   [](char c) { return std::toupper(c); });

    SECTION("parse regular property id") {
        CssTokenStream stream(src);
        CssPropertyIdParser parser(stream);

#define TEST_PROPERTY(name, _, __) EXPECT(name)
        LONGHAND_PROPERTY_LIST(TEST_PROPERTY);
#undef TEST_PROPERTY
    }

    SECTION("parse case-insensitive property id") {
        CssTokenStream stream(src_upper);
        CssPropertyIdParser parser(stream);

#define TEST_PROPERTY(name, _, __) EXPECT(name)
        LONGHAND_PROPERTY_LIST(TEST_PROPERTY);
#undef TEST_PROPERTY
    }
}
