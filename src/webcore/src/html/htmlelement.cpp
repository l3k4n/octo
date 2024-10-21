#include "html/htmlelement.h"

#include "html/tagname.h"

using HTML::HTMLElement;

HTMLElement::HTMLElement(const HTML::HTMLTagName& tagName) : Element(tagName) {}

HTMLElement::~HTMLElement() {}
