#ifndef CSS_PROPERTIES_PROPERTY_H
#define CSS_PROPERTIES_PROPERTY_H

class CssTokenStream;

namespace CSS {
class Value;

class Property {
public:
    Property(bool isShorhand) : m_shorthand(isShorhand) {}
    virtual ~Property() {}

    bool isLonghand() { return !m_shorthand; }
    bool isShorthand() { return m_shorthand; }

private:
    bool m_shorthand;
};

class LonghandProperty : public Property {
public:
    LonghandProperty() : Property(true) {}
    virtual ~LonghandProperty() {}

    virtual Value* parseValue(CssTokenStream&) = 0;
};

class ShorthandProperty : public Property {
public:
    ShorthandProperty() : Property(false) {}
    virtual ~ShorthandProperty() {}
};

}  // namespace CSS

#endif  // !CSS_PROPERTIES_PROPERTY_H
