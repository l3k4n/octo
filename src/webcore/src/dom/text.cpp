#include "dom/text.h"

#include "dom/domstring.h"
#include "dom/node.h"

using DOM::Text;

Text::Text() : Node(NodeType::TEXT_NODE, u"#text") {}

Text::Text(DOMString text) : Node(NodeType::TEXT_NODE, u"#text"), m_wholeText(text) {}

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
