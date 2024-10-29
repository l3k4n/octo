#include "webcore/html/htmlelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLElement;

HTMLElement::HTMLElement(const HTML::HTMLTagName& tagName) : Element(tagName) {}

HTMLElement::~HTMLElement() {}
