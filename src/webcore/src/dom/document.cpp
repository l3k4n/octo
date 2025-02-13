#include "webcore/dom/document.h"

#include "webcore/dom/domstring.h"
#include "webcore/dom/node.h"
#include "webcore/dom/text.h"
#include "webcore/html/collection.h"
#include "webcore/html/htmlanchorelement.h"
#include "webcore/html/htmlbodyelement.h"
#include "webcore/html/htmlbuttonelement.h"
#include "webcore/html/htmldivelement.h"
#include "webcore/html/htmlformelement.h"
#include "webcore/html/htmlheadelement.h"
#include "webcore/html/htmlheadingelement.h"
#include "webcore/html/htmlhtmlelement.h"
#include "webcore/html/htmlimageelement.h"
#include "webcore/html/htmlinputelement.h"
#include "webcore/html/htmllinkelement.h"
#include "webcore/html/htmlparagraphelement.h"
#include "webcore/html/htmlspanelement.h"
#include "webcore/html/htmlstyleelement.h"
#include "webcore/html/htmltitleelement.h"
#include "webcore/html/htmlunknownelement.h"
#include "webcore/html/tagname.h"
#include "webcore/internal/visitor/domvisitor.h"

using DOM::Document, DOM::DOMString, DOM::Text;
using namespace HTML;

Document::Document() : Node(nullptr, NodeType::DOCUMENT_NODE) {}

HTML::HTMLBodyElement* Document::body() const {
    if (!m_body && documentElement()) {
        for (auto& node : documentElement()->childNodes()) {
            if ((m_body = dynamic_cast<HTMLBodyElement*>(&node))) break;
        }
    }
    return m_body;
}

HTML::HTMLHtmlElement* Document::documentElement() const {
    return dynamic_cast<HTMLHtmlElement*>(firstElementChild());
}

DOM::Element* Document::createElement(HTML::HTMLTagName tagName) {
    switch (tagName) {
            // clang-format off
        case HTMLTagName::HtmlTag:   return new HTMLHtmlElement(this);
        case HTMLTagName::HeadTag:   return new HTMLHeadElement(this);
        case HTMLTagName::TitleTag:  return new HTMLTitleElement(this);
        case HTMLTagName::LinkTag:   return new HTMLLinkElement(this);
        case HTMLTagName::StyleTag:  return new HTMLStyleElement(this);
        case HTMLTagName::H1Tag:     return new HTMLHeadingElement(this, HTMLHeadingElement::H1);
        case HTMLTagName::H2Tag:     return new HTMLHeadingElement(this, HTMLHeadingElement::H2);
        case HTMLTagName::H3Tag:     return new HTMLHeadingElement(this, HTMLHeadingElement::H3);
        case HTMLTagName::H4Tag:     return new HTMLHeadingElement(this, HTMLHeadingElement::H4);
        case HTMLTagName::H5Tag:     return new HTMLHeadingElement(this, HTMLHeadingElement::H5);
        case HTMLTagName::H6Tag:     return new HTMLHeadingElement(this, HTMLHeadingElement::H6);
        case HTMLTagName::BodyTag:   return new HTMLBodyElement(this);
        case HTMLTagName::DivTag:    return new HTMLDivElement(this);
        case HTMLTagName::PTag:      return new HTMLParagraphElement(this);
        case HTMLTagName::ButtonTag: return new HTMLButtonElement(this);
        case HTMLTagName::FormTag:   return new HTMLFormElement(this);
        case HTMLTagName::InputTag:  return new HTMLInputElement(this);
        case HTMLTagName::ATag:      return new HTMLAnchorElement(this);
        case HTMLTagName::ImgTag:    return new HTMLImageElement(this);
        case HTMLTagName::ImageTag:  return new HTMLImageElement(this);
        case HTMLTagName::SpanTag :  return new HTMLSpanElement(this);
        default:                     return new HTMLUnknownElement(this, tagName);
            // clang-format on
    }
}

DOMString Document::nodeName() const { return u"#document"; }

Text* Document::createTextNode(DOMString data) { return new Text(this, data); }

void Document::accept(DOMVisitor& visitor) { visitor.visit(*this); }

void Document::setBody(HTML::HTMLBodyElement* body) {
    if (!body) return;
    m_body = body;
}
