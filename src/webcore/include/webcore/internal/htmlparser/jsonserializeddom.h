#ifndef HTMLPARSER_JSON_SERIALIZED_DOM_H
#define HTMLPARSER_JSON_SERIALIZED_DOM_H

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "webcore/dom/document.h"
#include "webcore/internal/visitor/domvisitor.h"

class JSONSerializedDOMVisitor : public DOMVisitor {
public:
    JSONSerializedDOMVisitor();

    void visit(DOM::Document& doc) override;
    void visit(HTML::HTMLElement& el) override;
    void visit(DOM::Text& text) override;
    void visit(DOM::Attr& attr) override;

    nlohmann::ordered_json& root();
    std::string str();

private:
    void visitChildNodes(const DOM::NodeList& list);

private:
    nlohmann::ordered_json m_root;
    nlohmann::ordered_json* m_current;
};

#endif  // !HTMLPARSER_JSON_SERIALIZED_DOM_H
