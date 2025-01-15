#ifndef CSS_PROPERTY_ID_H
#define CSS_PROPERTY_ID_H

#include <cstdint>
#include <functional>

#include "webcore/internal/check.h"

// name, css-name, return-type
#define LONGHAND_PROPERTY_LIST(X)                      \
    X(BackgroundColor, "background-color", ColorValue) \
    X(Color, "color", ColorValue)                      \
    X(Width, "width", SizeValue)                       \
    X(Height, "height", SizeValue)                     \
    X(MarginTop, "margin-top", SizeValue)              \
    X(MarginRight, "margin-right", SizeValue)          \
    X(MarginLeft, "margin-left", SizeValue)            \
    X(MarginBottom, "margin-bottom", SizeValue)        \
    X(PaddingTop, "padding-top", SizeValue)            \
    X(PaddingRight, "padding-right", SizeValue)        \
    X(PaddingLeft, "padding-left", SizeValue)          \
    X(PaddingBottom, "padding-bottom", SizeValue)      \
    X(BorderTop, "border-top", SizeValue)              \
    X(BorderRight, "border-right", SizeValue)          \
    X(BorderLeft, "border-left", SizeValue)            \
    X(BorderBottom, "border-bottom", SizeValue)

// name, css-name
#define SHORTHAND_PROPERTY_LIST(X) \
    X(Margin, "margin")            \
    X(Padding, "padding")          \
    X(Border, "border")

#define COUNT_LONGHAND(_, _1, _2) +1
#define COUNT_SHORTHAND(_, _1) +1
constexpr int LONGHAND_PROPERTY_COUNT = LONGHAND_PROPERTY_LIST(COUNT_LONGHAND);
constexpr int SHORTHAND_PROPERTY_COUNT = SHORTHAND_PROPERTY_LIST(COUNT_SHORTHAND);
constexpr int PROPERTY_COUNT = LONGHAND_PROPERTY_COUNT + SHORTHAND_PROPERTY_COUNT;
#undef COUNT_LONGHAND
#undef COUNT_SHORTHAND

namespace CSS {

class PropertyId {
public:
    // Note: Longhand must come first to satisfy
    // [0 .. LONGHAND_COUNT) precedes [LONGHAND_COUNT .. SHORTHAND_COUNT).
    enum Id : int8_t {
#define LONGHAND_ITEM(name, _, __) name,
#define SHORTHAND_ITEM(name, _) name,
        LONGHAND_PROPERTY_LIST(LONGHAND_ITEM) SHORTHAND_PROPERTY_LIST(SHORTHAND_ITEM)
#undef LONGHAND_ITEM
#undef SHORTHAND_ITEM
    };

    constexpr PropertyId(Id id) : m_id(id) {}

    operator int() const {
        DCHECK(m_id >= 0 && m_id < PROPERTY_COUNT)
        return m_id;
    }

    inline Id longhandId() const {
        DCHECK(!isShorthand() && m_id >= 0 && m_id < LONGHAND_PROPERTY_COUNT);
        return static_cast<Id>(m_id);
    }

    inline Id shorthandId() const {
        DCHECK(isShorthand());
        return static_cast<Id>(m_id);
    }

    inline bool isShorthand() const {
        return m_id >= LONGHAND_PROPERTY_COUNT && m_id < PROPERTY_COUNT;
    }

private:
    int8_t m_id;
};

}  // namespace CSS

namespace std {
template <>
struct hash<CSS::PropertyId> {
    size_t operator()(const CSS::PropertyId& id) const {
        return std::hash<int>()(static_cast<int>(id));
    }
};
}  // namespace std

#endif  // !CSS_PROPERTY_ID_H
