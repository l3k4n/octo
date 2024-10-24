#ifndef HTMLPARSER_UNICODE_H
#define HTMLPARSER_UNICODE_H

typedef char32_t codepoint_t;

#define REPLACEMENT_CHAR codepoint_t(0xFFFD)
#define EOF_CHAR codepoint_t('\0')

#endif  // !HTMLPARSER_UNICODE_H
