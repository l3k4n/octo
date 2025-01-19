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

Document::Document() : Node(NodeType::DOCUMENT_NODE, u"#document") {}

DOM::Element* Document::createElement(HTML::HTMLTagName tagName) const {
    switch (tagName) {
            // clang-format off
        case HTMLTagName::HtmlTag:   return new HTMLHtmlElement();
        case HTMLTagName::HeadTag:   return new HTMLHeadElement();
        case HTMLTagName::TitleTag:  return new HTMLTitleElement();
        case HTMLTagName::LinkTag:   return new HTMLLinkElement();
        case HTMLTagName::StyleTag:  return new HTMLStyleElement();
        case HTMLTagName::H1Tag:     return new HTMLHeadingElement(HTMLHeadingElement::H1);
        case HTMLTagName::H2Tag:     return new HTMLHeadingElement(HTMLHeadingElement::H2);
        case HTMLTagName::H3Tag:     return new HTMLHeadingElement(HTMLHeadingElement::H3);
        case HTMLTagName::H4Tag:     return new HTMLHeadingElement(HTMLHeadingElement::H4);
        case HTMLTagName::H5Tag:     return new HTMLHeadingElement(HTMLHeadingElement::H5);
        case HTMLTagName::H6Tag:     return new HTMLHeadingElement(HTMLHeadingElement::H6);
        case HTMLTagName::BodyTag:   return new HTMLBodyElement();
        case HTMLTagName::DivTag:    return new HTMLDivElement();
        case HTMLTagName::PTag:      return new HTMLParagraphElement();
        case HTMLTagName::ButtonTag: return new HTMLButtonElement();
        case HTMLTagName::FormTag:   return new HTMLFormElement();
        case HTMLTagName::InputTag:  return new HTMLInputElement();
        case HTMLTagName::ATag:      return new HTMLAnchorElement();
        case HTMLTagName::ImgTag:    return new HTMLImageElement();
        case HTMLTagName::ImageTag:  return new HTMLImageElement();
        case HTMLTagName::SpanTag :  return new HTMLSpanElement();
        default:                     return new HTMLUnknownElement();
            // clang-format on
    }
}

Text* Document::createTextNode(DOMString data) const { return new Text(); }

void Document::accept(DOMVisitor& visitor) { visitor.visit(*this); }
