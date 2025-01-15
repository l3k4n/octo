#ifndef CSS_STYLE_DECLARATION_H
#define CSS_STYLE_DECLARATION_H

#include "cssomstring.h"
#include "propertyid.h"
#include "propertymap.h"
#include "values/value.h"

namespace CSS {

class CSSRule;

class CSSStyleDeclaration {
public:
    CSSStyleDeclaration(PropertyMap&& prop_map);

    unsigned long length();
    CSSRule* parentRule();
    Value* getProperty(CSSOMString property);
    Value* getProperty(CSS::PropertyId property);

    void setParent(CSSRule*);

private:
    unsigned long m_length = 0;
    CSSRule* m_parent_rule = nullptr;
    PropertyMap m_prop_map;
};

}  // namespace CSS

#endif  // !CSS_STYLE_DECLARATION_H
