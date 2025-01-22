#ifndef OCTOCORE_ASSERT_H
#define OCTOCORE_ASSERT_H

#define OCTO_NOTREACHED()                                 \
    do {                                                  \
        std::cerr << __FILE__ << ":" << __LINE__ << ": "; \
        std::cerr << "Reached unreachable code\n";        \
        abort();                                          \
    } while (false)

#ifdef NDEBUG

#define OCTO_DCHECK(expr)

#else

#include <iostream>
#define OCTO_DCHECK(expr)                                     \
    do {                                                      \
        if (!(expr)) {                                        \
            std::cerr << __FILE__ << ":" << __LINE__ << ": "; \
            std::cerr << "Assertion Failed: " #expr "\n";     \
            abort();                                          \
        }                                                     \
    } while (false)

#endif

#endif  // !OCTOCORE_ASSERT_H
