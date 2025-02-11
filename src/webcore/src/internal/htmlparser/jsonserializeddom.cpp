#include "webcore/internal/htmlparser/jsonserializeddom.h"

#include "nlohmann/json.hpp"
#include "webcore/dom/text.h"
#include "webcore/html/htmlelement.h"

JSONSerializedDOMVisitor::JSONSerializedDOMVisitor() : DOMVisitor(), m_root(), m_current(&m_root) {}

void JSONSerializedDOMVisitor::visit(DOM::Document& doc) {
    (*m_current)["type"] = "Document";

    visitChildNodes(doc.childNodes());
}

void JSONSerializedDOMVisitor::visit(HTML::HTMLElement& el) {
    (*m_current)["type"] = "HTMLElement";
    (*m_current)["tagName"] = el.tagName.str().u8_str();

    for (auto& attr : el.attrList) attr.accept(*this);

    visitChildNodes(el.childNodes());
}

void JSONSerializedDOMVisitor::visit(DOM::Text& text) {
    (*m_current)["type"] = "Text";
    (*m_current)["wholeText"] = text.wholeText().u8_str();
}

void JSONSerializedDOMVisitor::visit(DOM::Attr& attr) {
    (*m_current)["attributes"][attr.name().u8_str()] = attr.value.u8_str();
}

void JSONSerializedDOMVisitor::visitChildNodes(const DOM::NodeList& list) {
    if (!list.length()) return;

    auto& parent = *m_current;
    auto& children = parent["children"];

    for (auto& child : list) {
        children.push_back(nullptr);
        m_current = &children.back();
        child.accept(*this);
    }

    m_current = &parent;
}

nlohmann::ordered_json& JSONSerializedDOMVisitor::root() { return m_root; }

std::string JSONSerializedDOMVisitor::str() { return m_root.dump(2); }
