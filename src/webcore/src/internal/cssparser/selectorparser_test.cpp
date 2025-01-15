#include "webcore/internal/cssparser/selectorparser.h"

#include "catch2/catch_test_macros.hpp"
#include "webcore/css/selector.h"
#include "webcore/css/selectorlist.h"
#include "webcore/internal/cssparser/tokenstream.h"

#define EASY_SETUP(str, num_selectors)       \
    CssTokenStream stream(str);              \
    CssSelectorParser parser(stream);        \
    CSS::SelectorList list;                  \
    REQUIRE(parser.parseSelectorList(list)); \
    REQUIRE(list.size() == num_selectors);   \
    REQUIRE(stream.eof())

#define EXPECT_SIMPLE_SELECTOR(sel, sel_type, sel_value)  \
    REQUIRE(sel.type() == CSS::Selector::Type::sel_type); \
    REQUIRE(sel.value() == u##sel_value);                 \
    REQUIRE(sel.combinator() == CSS::Selector::Combinator::None)

#define EXPECT_SIMPLE_ATTR_SELECTOR(sel, sel_value, match_type, match_val) \
    EXPECT_SIMPLE_SELECTOR(sel, Attr, sel_value);                          \
    REQUIRE(sel.matchType() == CSS::Selector::MatchType::match_type);      \
    REQUIRE(sel.matchValue() == u##match_val)

#define EXPECT_COMPOUND_SELECTOR(sel, sel_type, sel_value, sel_combinator) \
    REQUIRE(sel.type() == CSS::Selector::Type::sel_type);                  \
    REQUIRE(sel.value() == u##sel_value);                                  \
    REQUIRE(sel.combinator() == CSS::Selector::Combinator::sel_combinator)

#define EXPECT_COMPOUND_ATTR_SELECTOR(sel, sel_value, sel_combinator, match_type, match_val) \
    EXPECT_COMPOUND_SELECTOR(sel, Attr, sel_value, sel_combinator);                          \
    REQUIRE(sel.matchType() == CSS::Selector::MatchType::match_type);                        \
    REQUIRE(sel.matchValue() == u##match_val)

TEST_CASE("Parse css selectors", "[cssparser]") {
    SECTION("parse univeral selector") {
        EASY_SETUP("*", 1);
        EXPECT_SIMPLE_SELECTOR(list[0], Universal, "");
    }

    SECTION("parse type selector") {
        EASY_SETUP("div", 1);
        EXPECT_SIMPLE_SELECTOR(list[0], Tag, "div");
    }

    SECTION("parse class selector") {
        EASY_SETUP(".class", 1);
        EXPECT_SIMPLE_SELECTOR(list[0], Class, "class");
    }

    SECTION("parse id selector") {
        EASY_SETUP("#id", 1);
        EXPECT_SIMPLE_SELECTOR(list[0], Id, "id");
    }

    SECTION("parse attr selector") {
        EASY_SETUP("[attr]", 1);
        EXPECT_SIMPLE_SELECTOR(list[0], Attr, "attr");
    }

    SECTION("parse attr selector with matcher") {
        EASY_SETUP("[attr=value]", 1);
        EXPECT_SIMPLE_ATTR_SELECTOR(list[0], "attr", Equal, "value");
    }

    SECTION("parse attr selector with string value") {
        EASY_SETUP("[attr=\"value\"]", 1);
        EXPECT_SIMPLE_ATTR_SELECTOR(list[0], "attr", Equal, "value");
    }

    SECTION("parse compound selector") {
        EASY_SETUP("div.class#id[attr=value]", 4);
        EXPECT_COMPOUND_SELECTOR(list[0], Tag, "div", Joined);
        EXPECT_COMPOUND_SELECTOR(list[1], Class, "class", Joined);
        EXPECT_COMPOUND_SELECTOR(list[2], Id, "id", Joined);
        EXPECT_COMPOUND_ATTR_SELECTOR(list[3], "attr", None, Equal, "value");
    }

    SECTION("parse complex selector") {
        EASY_SETUP("div > span + a.class#id[attr=value], section article .content", 9);

        // div >
        EXPECT_COMPOUND_SELECTOR(list[0], Tag, "div", Child);
        // span +
        EXPECT_COMPOUND_SELECTOR(list[1], Tag, "span", Sibling);
        // a.class#id[attr=value],
        EXPECT_COMPOUND_SELECTOR(list[2], Tag, "a", Joined);
        EXPECT_COMPOUND_SELECTOR(list[3], Class, "class", Joined);
        EXPECT_COMPOUND_SELECTOR(list[4], Id, "id", Joined);
        EXPECT_COMPOUND_ATTR_SELECTOR(list[5], "attr", None, Equal, "value");
        // section article .content
        EXPECT_COMPOUND_SELECTOR(list[6], Tag, "section", Descendant);
        EXPECT_COMPOUND_SELECTOR(list[7], Tag, "article", Descendant);
        EXPECT_COMPOUND_SELECTOR(list[8], Class, "content", None);
    }
}
