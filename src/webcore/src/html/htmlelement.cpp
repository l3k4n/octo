#include "webcore/html/htmlelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLElement;

HTMLElement::HTMLElement(DOM::Document* owner, const HTML::HTMLTagName& tagName)
    : Element(owner, tagName) {}

HTMLElement::~HTMLElement() {}

void HTMLElement::accept(DOMVisitor& visitor) { return visitor.visit(*this); }
