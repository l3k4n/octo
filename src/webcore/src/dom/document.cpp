#include "dom/document.h"

#include "check.h"
#include "dom/domstring.h"
#include "dom/node.h"
#include "dom/text.h"
#include "html/collection.h"
#include "html/htmlanchorelement.h"
#include "html/htmlbodyelement.h"
#include "html/htmlbuttonelement.h"
#include "html/htmldivelement.h"
#include "html/htmlelement.h"
#include "html/htmlformelement.h"
#include "html/htmlheadelement.h"
#include "html/htmlheadingelement.h"
#include "html/htmlhtmlelement.h"
#include "html/htmlimageelement.h"
#include "html/htmlinputelement.h"
#include "html/htmllinkelement.h"
#include "html/htmlparagraphelement.h"
#include "html/htmlspanelement.h"
#include "html/htmlstyleelement.h"
#include "html/htmltitleelement.h"
#include "html/htmlunknownelement.h"
#include "html/tagname.h"

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
