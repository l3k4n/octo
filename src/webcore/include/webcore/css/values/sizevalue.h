#ifndef CSS_VALUES_SIZE_H
#define CSS_VALUES_SIZE_H

#include <cmath>

#include "value.h"

namespace CSS {

class SizeValue : public Value {
public:
    SizeValue(double value) : Value(Size), m_value(value) {}

private:
    const double m_value;
};

}  // namespace CSS

#endif  // !CSS_VALUES_SIZE_H
