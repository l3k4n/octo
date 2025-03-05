#ifndef CSS_VALUES_COLOR_VALUE_H
#define CSS_VALUES_COLOR_VALUE_H

#include <cstdint>

#include "webcore/css/values/value.h"

namespace CSS {

class ColorValue : public Value {
public:
    struct RGBA {
        uint8_t r, g, b, a;
    };

    ColorValue(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : Value(Color), m_color({r, g, b, a}) {}

    ColorValue(RGBA color) : Value(Color), m_color(color) {}

    RGBA rgba() { return m_color; }

private:
    const RGBA m_color;
};

}  // namespace CSS

#endif  // !CSS_VALUES_COLOR_VALUE_H
