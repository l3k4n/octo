#ifndef CSSPARSER_VALUE_PARSER_H
#define CSSPARSER_VALUE_PARSER_H

#include "webcore/css/properties/propertyid.h"

namespace CSS {
class Value;
class CSSStyleDeclaration;
}  // namespace CSS
class CssTokenStream;

class CssPropertyValueParser {
public:
    CssPropertyValueParser(CssTokenStream&);

    bool parseValue(CSS::PropertyId, CSS::CSSStyleDeclaration&);

    static CSS::Value* parseColorValue(CssTokenStream&);
    static CSS::Value* parseSizeValue(CssTokenStream&);
    static CSS::Value* parseWideKeywordValue(CssTokenStream&);

private:
    CssTokenStream& m_stream;
};

#endif  //! CSSPARSER_VALUE_PARSER_H
