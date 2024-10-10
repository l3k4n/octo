#ifndef HTMLPARSER_UNICODE_H
#define HTMLPARSER_UNICODE_H

#include <stdint.h>

#include <string_view>
#include <vector>

typedef uint32_t codepoint_t;

class codepoint_buf_t : public std::vector<codepoint_t> {
public:
    using std::vector<codepoint_t>::vector;

    bool operator==(char) const;
    bool operator==(codepoint_t) const;
    bool operator==(std::string_view) const;
};

#define REPLACEMENT_CHAR codepoint_t(0xFFFD)
#define EOF_CHAR codepoint_t('\0')

#endif  // !HTMLPARSER_UNICODE_H
