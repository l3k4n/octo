#include "webcore/css/properties/longhands.h"

#include "webcore/css/values/value.h"
#include "webcore/css/values/value_cast.h"
#include "webcore/internal/cssparser/propertyvalueparser.h"
#include "webcore/internal/cssparser/tokenstream.h"
#include "webcore/internal/styleengine/computedstyle.h"

namespace CSS::PROPERTIES {

Value* BackgroundColor::parseValue(CssTokenStream& stream) {
    return CssPropertyValueParser::parseColorValue(stream);
}
void BackgroundColor::setComputedValue(StyleEngine::ComputedStyle* computed_style, CSS::Value* value) {
    computed_style->setBackgroundColor(css_value_cast<CSS::ColorValue*>(value)->rgba());
}

Value* Color::parseValue(CssTokenStream& stream) {
    return CssPropertyValueParser::parseColorValue(stream);
}
void Color::setComputedValue(StyleEngine::ComputedStyle* computed_style, CSS::Value* value) {
    computed_style->setColor(css_value_cast<CSS::ColorValue*>(value)->rgba());
}

Value* Width::parseValue(CssTokenStream& stream) {
    return CssPropertyValueParser::parseSizeValue(stream);
}
void Width::setComputedValue(StyleEngine::ComputedStyle* computed_style, CSS::Value* value) {
    computed_style->setWidth(css_value_cast<CSS::SizeValue*>(value));
}

Value* Height::parseValue(CssTokenStream& stream) {
    return CssPropertyValueParser::parseSizeValue(stream);
}
void Height::setComputedValue(StyleEngine::ComputedStyle* computed_style, CSS::Value* value) {
    computed_style->setHeight(css_value_cast<CSS::SizeValue*>(value));
}

}  // namespace CSS::PROPERTIES
