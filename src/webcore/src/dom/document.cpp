#include "webcore/dom/document.h"

#include "webcore/internal/check.h"
#include "webcore/dom/domstring.h"
#include "webcore/dom/node.h"
#include "webcore/dom/text.h"
#include "webcore/html/collection.h"
#include "webcore/html/htmlanchorelement.h"
#include "webcore/html/htmlbodyelement.h"
#include "webcore/html/htmlbuttonelement.h"
#include "webcore/html/htmldivelement.h"
#include "webcore/html/htmlelement.h"
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

using DOM::Document, DOM::DOMString, DOM::Text;
using namespace HTML;

Document::Document() : Node(NodeType::DOCUMENT_NODE, u"#document") {}

DOM::Element* Document::createElement(HTML::HTMLTagName tagName) const {
    HTML::HTMLElement* element;
    switch (tagName) {
            // clang-format off
        case HTMLTagName::HtmlTag: element =  new HTMLHtmlElement(); break;
        case HTMLTagName::HeadTag: element =  new HTMLHeadElement(); break;
        case HTMLTagName::TitleTag: element =  new HTMLTitleElement(); break;
        case HTMLTagName::LinkTag: element =  new HTMLLinkElement(); break;
        case HTMLTagName::StyleTag: element =  new HTMLStyleElement(); break;
        case HTMLTagName::H1Tag: element =  new HTMLHeadingElement(HTMLHeadingElement::H1); break;
        case HTMLTagName::H2Tag: element =  new HTMLHeadingElement(HTMLHeadingElement::H2); break;
        case HTMLTagName::H3Tag: element =  new HTMLHeadingElement(HTMLHeadingElement::H3); break;
        case HTMLTagName::H4Tag: element =  new HTMLHeadingElement(HTMLHeadingElement::H4); break;
        case HTMLTagName::H5Tag: element =  new HTMLHeadingElement(HTMLHeadingElement::H5); break;
        case HTMLTagName::H6Tag: element =  new HTMLHeadingElement(HTMLHeadingElement::H6); break;
        case HTMLTagName::BodyTag: element =  new HTMLBodyElement(); break;
        case HTMLTagName::DivTag: element =  new HTMLDivElement(); break;
        case HTMLTagName::PTag: element =  new HTMLParagraphElement(); break;
        case HTMLTagName::ButtonTag: element =  new HTMLButtonElement(); break;
        case HTMLTagName::FormTag: element =  new HTMLFormElement(); break;
        case HTMLTagName::InputTag: element =  new HTMLInputElement(); break;
        case HTMLTagName::ATag: element =  new HTMLAnchorElement(); break;
        case HTMLTagName::ImgTag: element =  new HTMLImageElement(); break;
        case HTMLTagName::ImageTag: element =  new HTMLImageElement(); break;
        case HTMLTagName::SpanTag : element =  new HTMLSpanElement(); break;
        // TODO: set tag name of unknown element
        default: element = new HTMLUnknownElement();
            // clang-format on
    }

    DCHECK(element != nullptr);
    return element;
}

Text* Document::createTextNode(DOMString data) const { return new Text(); }
