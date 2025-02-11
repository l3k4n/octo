#include "webcore/dom/text.h"

#include "webcore/dom/domstring.h"
#include "webcore/dom/node.h"

using DOM::Text;

Text::Text() : Node(NodeType::TEXT_NODE) {}

Text::Text(DOMString text) : Node(NodeType::TEXT_NODE), m_wholeText(text) {}

Text Text::splitText(unsigned long offset) {
    DOMString substr = m_wholeText.substr(0, offset);
    m_wholeText.erase(0, offset);

    return Text(substr);
}

void Text::insertData(unsigned long offset, const DOMString& data) {
    m_wholeText.insert(offset, data);
}

const DOM::DOMString& Text::wholeText() const { return m_wholeText; }

unsigned long Text::length() const { return m_wholeText.length(); }

DOM::DOMString Text::nodeName() const { return u"#text"; }

void Text::accept(DOMVisitor& visitor) { return visitor.visit(*this); }
