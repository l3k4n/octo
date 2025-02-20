#include "webcore/css/selectorlist.h"

using namespace CSS;

using Iterator = SelectorList::Iterator;
using SelectorGroup = SelectorList::SelectorGroup;
using SelectorGroupIterator = SelectorList::SelectorGroupIterator;

static Iterator find_complex_selector_end(Iterator beg, Iterator end) {
    auto it = std::find_if(beg, end, [](const CSS::Selector& selector) {
        return selector.combinator() == Selector::Combinator::None;
    });

    if (it != end) return ++it;
    return it;
}

SelectorGroup::SelectorGroup(Iterator first, Iterator last) : m_first(first), m_last(last) {}

Iterator SelectorGroup::begin() const { return m_first; }

Iterator SelectorGroup::end() const { return m_last; }

std::reverse_iterator<Iterator> SelectorGroup::rbegin() const {
    return std::reverse_iterator(m_last);
}
std::reverse_iterator<Iterator> SelectorGroup::rend() const {
    return std::reverse_iterator(m_first);
}

SelectorGroupIterator::SelectorGroupIterator(Iterator current, Iterator list_end)
    : m_end(list_end), m_group(current, find_complex_selector_end(current, list_end)) {}

SelectorGroupIterator::SelectorGroupIterator(Iterator end) : m_end(end), m_group(end, end) {}

const SelectorGroup& SelectorGroupIterator::operator*() { return m_group; }

SelectorGroupIterator& SelectorGroupIterator::operator++() {
    auto start = m_group.end();
    m_group = SelectorGroup(start, find_complex_selector_end(start, m_end));
    return *this;
}

bool SelectorGroupIterator::operator!=(const SelectorGroupIterator& other) {
    return m_group.begin() != other.m_group.begin();
}

SelectorGroupIterator SelectorList::group_begin() const {
    return SelectorGroupIterator(begin(), end());
}

SelectorGroupIterator SelectorList::group_end() const { return SelectorGroupIterator(end()); }
