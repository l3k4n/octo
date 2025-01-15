#ifndef CSS_PROPERTY_MAP_H
#define CSS_PROPERTY_MAP_H

#include <unordered_map>

#include "propertyid.h"
#include "values/value.h"

namespace CSS {

class PropertyMap {
public:
    void set(PropertyId, Value*);
    Value* get(PropertyId);

private:
    std::unordered_map<PropertyId, Value*> m_map;
};

}  // namespace CSS

#endif  // !CSS_PROPERTY_MAP_H
