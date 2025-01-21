#include "webcore/internal/htmlparser/jsonserializeddom.h"
#include "nlohmann/json.hpp"
#include "webcore/dom/text.h"
#include "webcore/html/htmlelement.h"

#include <algorithm>

template <typename T>
inline std::string stringify(T t) {
    std::string str(t.size(), '\0');
    std::transform(t.begin(), t.end(), str.begin(),
                   [](char16_t c) { return static_cast<char>(c); });
    return str;
}

JSONSerializedDOMVisitor::JSONSerializedDOMVisitor() : DOMVisitor(), m_root(), m_current(&m_root) {}

void JSONSerializedDOMVisitor::visit(DOM::Document& doc) {
    (*m_current)["type"] = "Document";

    visitChildNodes(doc.childNodes);
}

void JSONSerializedDOMVisitor::visit(HTML::HTMLElement& el) {
    (*m_current)["type"] = "HTMLElement";
    (*m_current)["tagName"] = stringify(DOM::DOMString(el.tagName));

    for (auto& attr : el.attrList) attr.accept(*this);

    visitChildNodes(el.childNodes);
}

void JSONSerializedDOMVisitor::visit(DOM::Text& text) {
    (*m_current)["type"] = "Text";
    (*m_current)["wholeText"] = stringify(DOM::DOMString(text.wholeText()));
}

void JSONSerializedDOMVisitor::visit(DOM::Attr& attr) {
    (*m_current)["attributes"][stringify(attr.name())] = stringify(attr.value);
}

void JSONSerializedDOMVisitor::visitChildNodes(DOM::NodeList& list) {
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
