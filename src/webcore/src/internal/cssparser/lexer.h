#ifndef CSSPARSER_LEXER_H
#define CSSPARSER_LEXER_H

#include <string>
#include <string_view>

#include "token.h"
#include "webcore/internal/generic/inputstream.h"

class CssLexer {
public:
    CssLexer(const std::string& in);
    CssToken next();

private:
    void reconsumeCurrent();
    bool advanceIfNextMatch(UChar32, UChar32);

    bool streamStartsWithNumber();
    bool streamStartsWithIdentSequence();
    // function name says 3 because of spec, but I decided not to handle escapes so it's just 2.
    bool next3CodepointsStartsIdentSequence();

    void consumeComments();
    std::u16string_view consumeIdentSequence();
    CssToken consumeWhiteSpaceToken();
    CssToken consumeStringToken();
    CssToken consumeNumericToken();
    CssToken consumeIdentLikeToken();
    CssToken consumeCurrentCharAsDelim();

private:
    GenericInputStream m_in;
};

#endif  // !CSSPARSER_LEXER_H
