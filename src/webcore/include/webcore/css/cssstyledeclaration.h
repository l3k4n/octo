#ifndef CSS_STYLE_DECLARATION_H
#define CSS_STYLE_DECLARATION_H

#include "propertyid.h"
#include "values/value.h"

namespace CSS {

class CSSRule;

class CSSStyleDeclaration {
    struct PropertyDeclaration {
        CSS::Value* value;
        CSS::PropertyId id;
        bool important = false;
    };

public:
    unsigned long length() const;
    CSSRule* parentRule() const;
    Value* getProperty(CSS::PropertyId) const;
    void setProperty(CSS::PropertyId, CSS::Value*, bool important = false);
    void setParent(CSSRule*);
    std::vector<PropertyDeclaration>::const_iterator begin() const;
    std::vector<PropertyDeclaration>::const_iterator end() const;

private:
    std::vector<PropertyDeclaration>::iterator findProperty(CSS::PropertyId);
    std::vector<PropertyDeclaration>::const_iterator findProperty(CSS::PropertyId) const;

private:
    CSSRule* m_parent_rule = nullptr;

    // TODO: create a `m_partial` flag to indicate whether this contains all or some properties.
    //       when partial is set: properties can just be appended and retrieved by searching
    //       when partial isn't set: initialize m_properties with size=`PROPERTIES_COUNT` then
    //       propeties can be indexed into
    std::vector<PropertyDeclaration> m_properties;
};

}  // namespace CSS

#endif  // !CSS_STYLE_DECLARATION_H
