#include "webcore/css/properties/longhands.h"

#include "webcore/internal/cssparser/propertyvalueparser.h"
#include "webcore/internal/cssparser/tokenstream.h"

namespace CSS::PROPERTIES {

Value* BackgroundColor::parseValue(CssTokenStream& stream) {
    return CssPropertyValueParser::parseColorValue(stream);
}

Value* Color::parseValue(CssTokenStream& stream) {
    return CssPropertyValueParser::parseColorValue(stream);
}

Value* Width::parseValue(CssTokenStream& stream) {
    return CssPropertyValueParser::parseSizeValue(stream);
}

Value* Height::parseValue(CssTokenStream& stream) {
    return CssPropertyValueParser::parseSizeValue(stream);
}

}  // namespace CSS::PROPERTIES
