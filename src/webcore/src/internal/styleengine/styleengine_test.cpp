#include "webcore/internal/styleengine/styleengine.h"

#include "catch2/catch_test_macros.hpp"
#include "webcore/css/cssstylesheet.h"
#include "webcore/dom/document.h"
#include "webcore/html/htmlhtmlelement.h"
#include "webcore/internal/cssparser/parser.h"
#include "webcore/internal/htmlparser/lexer.h"
#include "webcore/internal/htmlparser/treebuilder.h"

TEST_CASE("style engine test", "[styleengine]") {
    auto parser = CssParser(R"(
      html > body > div > span { background-color: red; }
      body { margin-left: initial; }
      div * { margin-right: initial; }
      span { color: blue; };
    )");
    auto stylessheet = std::make_unique<CSS::CSSStyleSheet>(parser.parseStyleSheet());
    REQUIRE(stylessheet->cssRules().length() == 4);

    GenericInputStream stream(R"(<html><body><div><span>hello world</span></div></body></html>)");
    HTMLLexer lexer(stream);
    DOM::Document doc;
    HTMLTreeBuilder builder(&doc, lexer);

    auto& style_engine = doc.styleEngine();
    style_engine.addStyleSheet(std::move(stylessheet));
    style_engine.computeStyles();

    auto body = doc.documentElement()->lastElementChild();
    auto span = body->firstElementChild()->firstElementChild();

    printf("%ld\n", span->computedStyle()->width());
}
