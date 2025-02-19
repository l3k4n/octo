#ifndef CSS_PROPERTIES_PROPERTY_H
#define CSS_PROPERTIES_PROPERTY_H

#include "webcore/internal/styleengine/propertysignificancescore.h"

class CssTokenStream;

namespace StyleEngine {
class StyleBuilder;
class ComputedStyle;
}  // namespace StyleEngine

namespace CSS {
class Value;

class Property {
public:
    Property(bool isLonghand) : m_longhand(isLonghand) {}
    virtual ~Property() {}

    bool isLonghand() { return m_longhand; }
    bool isShorthand() { return !m_longhand; }

private:
    bool m_longhand;
};

class LonghandProperty : public Property {
public:
    LonghandProperty() : Property(true) {}
    virtual ~LonghandProperty() {}

    virtual Value* parseValue(CssTokenStream&) = 0;
    virtual void setComputedValue(StyleEngine::ComputedStyle*, CSS::Value*) = 0;
};

class ShorthandProperty : public Property {
public:
    ShorthandProperty() : Property(false) {}
    virtual ~ShorthandProperty() {}

    virtual void applyLonghands(StyleEngine::StyleBuilder&, CSS::Value*,
                                StyleEngine::PropertySignificanceScore score) = 0;
};

}  // namespace CSS

#endif  // !CSS_PROPERTIES_PROPERTY_H
