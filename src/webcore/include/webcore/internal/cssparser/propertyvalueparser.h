#ifndef CSSPARSER_VALUE_PARSER_H
#define CSSPARSER_VALUE_PARSER_H

#include "webcore/css/propertyid.h"

namespace CSS {
class Value;
class CSSStyleDeclaration;
}
class CssTokenStream;

class CssPropertyValueParser {
public:
    typedef CSS::Value* (*LonghandParser)(CssTokenStream&);
public:
    CssPropertyValueParser(CssTokenStream&);

    bool parseValue(CSS::PropertyId, CSS::CSSStyleDeclaration&);

    static CSS::Value* parseColorValue(CssTokenStream&);
    static CSS::Value* parseSizeValue(CssTokenStream&);
    static CSS::Value* parseWideKeywordValue(CssTokenStream&);

    static LonghandParser resolveLonghandParser(CSS::PropertyId);

private:
    static LonghandParser longhand_parsers[];

    CssTokenStream& m_stream;
};

#endif  //! CSSPARSER_VALUE_PARSER_H
