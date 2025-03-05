#include "webcore/internal/cssparser/propertyidparser.h"

#include <cctype>
#include <string>

#include "catch2/catch_test_macros.hpp"
#include "webcore/css/properties/propertyid.h"
#include "webcore/internal/cssparser/tokenstream.h"

#define EXPECT(expected_id)                            \
    {                                                  \
        stream.skipWhitespace();                       \
        auto val = parser.parseId();                   \
        REQUIRE(val.has_value());                      \
        REQUIRE(*val == CSS::PropertyId::expected_id); \
    }

TEST_CASE("PropertyId parser correctly parses id's", "[cssparser]") {
    SECTION("parse property id's with irregular case") {
        CssTokenStream stream("BaCkGrOuNd-CoLoR margin-left PADDING-TOP");
        CssPropertyIdParser parser(stream);

        EXPECT(BackgroundColor);
        EXPECT(MarginLeft);
        EXPECT(PaddingTop);
    }
}
