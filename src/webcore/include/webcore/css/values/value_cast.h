#ifndef CSS_VALUES_CAST_H
#define CSS_VALUES_CAST_H

#include <typeinfo>

#include "webcore/css/values/traits.h"
#include "webcore/css/values/value.h"

template <typename T>
T css_value_cast(CSS::Value* value) {
    static_assert(std::is_pointer_v<T>, "T must be a pointer type");
    static_assert(std::is_base_of_v<CSS::Value, std::remove_pointer_t<T>>, "T must be a css value");

    if (value == nullptr) return nullptr;
    if (value->Type() != css_value_type<std::remove_pointer_t<T>>::value_type) {
        throw std::bad_cast();
    }

    return static_cast<T>(value);
}

#endif  // !CSS_VALUES_CAST_H
