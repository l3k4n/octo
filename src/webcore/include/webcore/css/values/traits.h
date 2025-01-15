#ifndef CSS_VALUES_TRAITS_H
#define CSS_VALUES_TRAITS_H

#include "webcore/css/values/colorvalue.h"
#include "webcore/css/values/sizevalue.h"
#include "webcore/css/values/value.h"
#include "webcore/css/values/widekeywordvalue.h"

template <typename T>
struct css_value_type {};

#define CSS_VALUE_TRAIT(v)                                                               \
    template <>                                                                       \
    struct css_value_type<CSS::v##Value> {                                            \
        static constexpr CSS::Value::ValueType value_type = CSS::Value::ValueType::v; \
    };

CSS_VALUE_TRAIT(Color)
CSS_VALUE_TRAIT(WideKeyword)
CSS_VALUE_TRAIT(Size)

#undef DEFINE_TRAIT

#endif  // !CSS_VALUES_TRAITS_H
