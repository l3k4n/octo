#ifndef CSS_SELECTOR_LIST_H
#define CSS_SELECTOR_LIST_H

#include <vector>

#include "selector.h"

namespace CSS {

class SelectorList : std::vector<Selector> {
public:
    using Iterator = std::vector<Selector>::const_iterator;

    class SelectorGroup {
    public:
        SelectorGroup(Iterator first, Iterator list_end);

        Iterator begin() const;
        Iterator end() const;
        std::reverse_iterator<Iterator> rbegin() const;
        std::reverse_iterator<Iterator> rend() const;

    private:
        Iterator m_first, m_last;
    };

    class SelectorGroupIterator {
    public:
        SelectorGroupIterator(Iterator current, Iterator end);
        SelectorGroupIterator(Iterator end);

        const SelectorGroup& operator*();
        SelectorGroupIterator& operator++();
        bool operator!=(const SelectorGroupIterator& other);

    private:
        Iterator m_end;
        SelectorGroup m_group;
    };

    using vector::back;
    using vector::emplace_back;
    using vector::size;
    using vector::operator[];
    using vector::shrink_to_fit;

    SelectorGroupIterator group_begin() const;
    SelectorGroupIterator group_end() const;
};

}  // namespace CSS

#endif  // !CSS_SELECTOR_LIST_H
