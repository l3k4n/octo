#ifndef CSS_PROPERTIES_PROPERTY_H
#define CSS_PROPERTIES_PROPERTY_H

class CssTokenStream;

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
};

class ShorthandProperty : public Property {
public:
    ShorthandProperty() : Property(false) {}
    virtual ~ShorthandProperty() {}
};

}  // namespace CSS

#endif  // !CSS_PROPERTIES_PROPERTY_H
