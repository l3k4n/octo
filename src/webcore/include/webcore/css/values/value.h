#ifndef CSS_VALUES_VALUE_H
#define CSS_VALUES_VALUE_H

namespace CSS {

class Value {
public:
    // NOTE: Value types must prefix class names (e.g WideKeyword -> WideKeywordValue)
    enum ValueType { WideKeyword, Size, Color };

protected:
    constexpr Value(ValueType type) : m_type(type) {}
    ~Value();

public:
    inline ValueType Type() { return m_type; };

private:
    const ValueType m_type;
};

}  // namespace CSS

#endif  // !CSS_VALUES_VALUE_H
