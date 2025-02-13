#include "webcore/html/htmlformelement.h"

#include "webcore/dom/usvstring.h"
#include "webcore/html/htmlelement.h"
#include "webcore/html/tagname.h"

using DOM::USVString, HTML::HTMLFormElement;

HTMLFormElement::HTMLFormElement(DOM::Document* owner) : HTMLElement(owner, HTMLTagName::FormTag) {}
