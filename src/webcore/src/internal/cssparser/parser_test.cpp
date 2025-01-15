#include "webcore/internal/cssparser/parser.h"

#include "catch2/catch_test_macros.hpp"
#include "webcore/css/cssrule.h"

TEST_CASE("Parse simple rule", "[cssparser]") {
    CssParser parser(".div { color: red; }");

    auto rules = parser.parseStyleSheet().cssRules();
    REQUIRE(rules.length() == 1);
    REQUIRE(rules.item(0)->ruleType() == CSS::CSSRule::Type::STYLE_RULE);
}
