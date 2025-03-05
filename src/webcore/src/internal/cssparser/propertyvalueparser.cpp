#include "webcore/internal/cssparser/propertyvalueparser.h"

#include <string_view>
#include <unordered_map>

#include "webcore/css/cssstyledeclaration.h"
#include "webcore/css/properties/propertydata.h"
#include "webcore/css/properties/propertyid.h"
#include "webcore/css/values/colorvalue.h"
#include "webcore/css/values/sizevalue.h"
#include "webcore/css/values/value.h"
#include "webcore/css/values/widekeywordvalue.h"
#include "webcore/internal/cssparser/token.h"
#include "webcore/internal/cssparser/tokenstream.h"

CssPropertyValueParser::CssPropertyValueParser(CssTokenStream& stream) : m_stream(stream) {}

bool CssPropertyValueParser::parseValue(CSS::PropertyId id, CSS::CSSStyleDeclaration& decls) {
    auto keyword = parseWideKeywordValue(m_stream);
    if (keyword != nullptr) {
        decls.setProperty(id, keyword);
        return true;
    }

    auto property = CSS::PropertyInstances[int(id)];
    if (property->isLonghand()) {
        auto value = dynamic_cast<CSS::LonghandProperty*>(property)->parseValue(m_stream);
        if (!value) return false;
        decls.setProperty(id, value);
        return true;
    }

    // TODO: parse shorthand properties
    return false;
}

inline CSS::ColorValue* parseHexColor(std::u16string_view str) {
    char hex_str[8] = {'0', '0', '0', '0', '0', '0', 'F', 'F'};  // RRGGBBAA

    if (str.length() == 3 || str.length() == 4) {
        for (int i = 0; i < str.length(); ++i) {
            hex_str[i * 2] = hex_str[(i * 2) + 1] = static_cast<char>(str[i]);
        }
    } else if (str.length() == 6 || str.length() == 8) {
        for (int i = 0; i < str.length(); ++i) {
            hex_str[i] = static_cast<char>(str[i]);
        }
    } else {
        return nullptr;
    }

    auto hex = (int)std::strtol(hex_str, nullptr, 16);
    unsigned char r = (hex >> 24) & 0xFF;
    unsigned char g = (hex >> 16) & 0xFF;
    unsigned char b = (hex >> 8) & 0xFF;
    unsigned char a = (hex >> 0) & 0xFF;

    return new CSS::ColorValue(r, g, b, a);
}

CSS::Value* CssPropertyValueParser::parseColorValue(CssTokenStream& stream) {
    static std::unordered_map<std::u16string_view, CSS::ColorValue::RGBA> known_colors = {
        {u"white", {255, 255, 255, 255}}, {u"black", {0, 0, 0, 255}},
        {u"red", {255, 0, 0, 255}},       {u"green", {0, 255, 0, 255}},
        {u"blue", {0, 0, 255, 255}},      {u"transparent", {0, 0, 0, 0}},
    };

    switch (stream.peek()) {
        case Hash:
            return parseHexColor(stream.next().value());

        case Ident: {
            auto it = known_colors.find(stream.next().value());
            if (it == known_colors.end()) return nullptr;
            return new CSS::ColorValue(it->second);
        }

        default:
            return nullptr;
    }
}

CSS::Value* CssPropertyValueParser::parseSizeValue(CssTokenStream& stream) {
    // TODO: implement size parser
    if (stream.peek() != Dimension) return nullptr;
    return new CSS::SizeValue(0);
}

CSS::Value* CssPropertyValueParser::parseWideKeywordValue(CssTokenStream& stream) {
    if (stream.peek() != Ident) return nullptr;
    auto value = stream.peek().value();

    static std::unordered_map<std::u16string_view, CSS::WideKeywordValue::Keyword> keyword_map = {
        {u"inherit", CSS::WideKeywordValue::Inherit},
        {u"initial", CSS::WideKeywordValue::Initial},
        {u"unset", CSS::WideKeywordValue::Unset},
    };

    auto it = keyword_map.find(value);
    if (it == keyword_map.end()) return nullptr;

    stream.next();
    return new CSS::WideKeywordValue(it->second);
}
