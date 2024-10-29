#ifndef WEBCORE_CHECK_H
#define WEBCORE_CHECK_H

#ifdef DCHECK_IS_ON
#include <iostream>
#define DCHECK(expr)                                      \
    if (!(expr)) {                                        \
        std::cerr << __FILE__ << ":" << __LINE__ << ": "; \
        std::cerr << "Assertion Failed: " #expr "\n";     \
        abort();                                          \
    }
#else
#define DCHECK(expr) (void(0));
#endif

#endif  // !WEBCORE_CHECK_H
