#include "webcore/internal/htmlparser/treebuilder.h"

#include <string>

#include "catch2/catch_message.hpp"
#include "catch2/catch_test_macros.hpp"
#include "jsoncompare.hpp"
#include "snapshots.dom.h"
#include "webcore/dom/document.h"
#include "webcore/internal/generic/inputstream.h"
#include "webcore/internal/htmlparser/jsonserializeddom.h"
#include "webcore/internal/htmlparser/lexer.h"

#define TEST_SNAPSHOT(snapshot, section_name)                \
    SECTION(section_name) {                                  \
        GenericInputStream stream(snapshot.input);           \
        HTMLLexer lexer(stream);                             \
                                                             \
        DOM::Document doc;                                   \
        HTMLTreeBuilder builder(&doc, lexer);                \
        JSONSerializedDOMVisitor v;                          \
        doc.accept(v);                                       \
                                                             \
        JSONCompare result(v.root(), snapshot.expected_ast); \
                                                             \
        INFO(v.root().dump(2));                              \
        INFO(result.warnings());                             \
        REQUIRE(result.ok());                                \
    }

TEST_CASE("ss", "[tb]") {
    TEST_SNAPSHOT(DOMSnapshots::empty, "empty body");
    TEST_SNAPSHOT(DOMSnapshots::simple_body_content, "simple content in body");
    TEST_SNAPSHOT(DOMSnapshots::nested_elements, "nested elements");
    TEST_SNAPSHOT(DOMSnapshots::mixed_content, "text placed around elements");
    TEST_SNAPSHOT(DOMSnapshots::invalid_tag_moved, "invalid tag in head");
    TEST_SNAPSHOT(DOMSnapshots::attributes_and_nested_elements, "elements with attributes");
}
