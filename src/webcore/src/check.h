#ifndef HTMLPARSER_CHECK_H
#define HTMLPARSER_CHECK_H

#ifdef DCHECK_IS_ON
#define DCHECK(expr)                                      \
    if (!(expr)) {                                        \
        std::cerr << __FILE__ << ":" << __LINE__ << ": "; \
        std::cerr << "Assertion Failed: " #expr "\n";     \
        abort();                                          \
    }
#else
#define DCHECK(expr) (void(0));
#endif

#endif  // !HTMLPARSER_CHECK_H
