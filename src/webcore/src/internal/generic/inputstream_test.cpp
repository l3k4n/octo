#include "webcore/internal/generic/inputstream.h"

#include <unicode/umachine.h>
#include <unicode/unistr.h>

#include <string>

#include "catch2/catch_test_macros.hpp"

struct GenericInputStreamFixture {
    bool advance_and_compare(const char32_t* buf, size_t size) const {
        auto pos = 0;
        while (pos < size) {
            if (in.advance() != buf[pos++]) return false;
        }

        return true;
    }

    mutable GenericInputStream in =
        std::string("Lorem🐱 café ipsum Γειά σας мир 😊, tacos brûlée 🌍.");
};

TEST_CASE_PERSISTENT_FIXTURE(GenericInputStreamFixture,
                             "GenericInputStream handles utf8 ifput properly", "[generic]") {
    SECTION("advancing works with multibyte character's") {
        // advance to space right after the cat emoji
        in.advanceUntil(' ');
        REQUIRE(in.current() == ' ');
    }

    SECTION("createStringView captures proper range") {
        auto start = in.pos();
        in.advance(4);

        REQUIRE(in.createStringView(start, in.pos()) == std::u16string({u'c', u'a', u'f', u'é'}));
    }

    SECTION("moving to previous and future stream position works properly") {
        auto savepoint1 = in.pos();  // ... café<SAVE POINT 1> ipsum Γειά σας ...
        in.advanceUntil(',');
        auto savepoint2 = in.pos();  // ... мир 😊,<SAVE POINT 2> tacos brûlée 🌍.

        in.moveTo(savepoint1);
        REQUIRE(advance_and_compare(U" ipsum", 6));
        in.moveTo(savepoint2);
        REQUIRE(advance_and_compare(U" tacos", 6));
    }

    SECTION("advancing until invalid empties the stream") {
        in.advanceUntil('x');
        REQUIRE(in.eof());
    }
}
