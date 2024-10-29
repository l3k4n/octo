#ifndef CSSPARSER_LEXER_H
#define CSSPARSER_LEXER_H

#include <string>
#include <string_view>

#include "webcore/internal/generic_input_stream.h"
#include "token.h"

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

private:
    GenericInputStream m_in;
};

#endif  // !CSSPARSER_LEXER_H
