#include "webcore/html/htmlformelement.h"

#include "webcore/dom/domstring.h"
#include "webcore/dom/usvstring.h"
#include "webcore/html/htmlelement.h"
#include "webcore/html/tagname.h"

using DOM::DOMString, DOM::USVString, HTML::HTMLFormElement;

HTMLFormElement::HTMLFormElement() : HTMLElement(HTMLTagName::FormTag) {}
