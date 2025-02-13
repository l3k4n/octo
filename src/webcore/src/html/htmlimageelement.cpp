#include "webcore/html/htmlimageelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLImageElement;

HTMLImageElement::HTMLImageElement(DOM::Document* owner)
    : HTMLElement(owner, HTMLTagName::ImageTag) {}
