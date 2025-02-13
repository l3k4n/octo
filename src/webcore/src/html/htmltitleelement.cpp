#include "webcore/html/htmltitleelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLTitleElement;

HTMLTitleElement::HTMLTitleElement(DOM::Document* owner) : HTMLElement(owner, HTMLTagName::TitleTag) {}
