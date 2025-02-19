#ifndef WEBCORE_INTERNAL_STYLE_ENGINE_COMPUTED_STYLE_H
#define WEBCORE_INTERNAL_STYLE_ENGINE_COMPUTED_STYLE_H

#include "webcore/css/values/colorvalue.h"

namespace CSS {
class Value;
class SizeValue;
}  // namespace CSS

namespace StyleEngine {

class ComputedStyle {
public:
    ComputedStyle() = default;
    ComputedStyle(const ComputedStyle&) = delete;

    CSS::SizeValue* width();
    CSS::SizeValue* height();
    CSS::ColorValue::RGBA color();
    CSS::ColorValue::RGBA backgroundColor();

    void setWidth(CSS::SizeValue*);
    void setHeight(CSS::SizeValue*);
    void setColor(CSS::ColorValue::RGBA color);
    void setBackgroundColor(CSS::ColorValue::RGBA color);

private:
    CSS::ColorValue::RGBA m_color;
    CSS::ColorValue::RGBA m_background_color;
    CSS::SizeValue* m_width = nullptr;
    CSS::SizeValue* m_height = nullptr;
};

}  // namespace StyleEngine

#endif  // !WEBCORE_INTERNAL_STYLE_ENGINE_COMPUTED_STYLE_H
