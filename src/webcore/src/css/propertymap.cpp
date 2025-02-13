#include "webcore/css/propertymap.h"

#include "webcore/css/propertyid.h"
#include "webcore/css/values/value.h"

using CSS::PropertyMap;

void PropertyMap::set(CSS::PropertyId p, CSS::Value* v) { m_map.insert(std::pair(p, v)); }

CSS::Value* PropertyMap::get(CSS::PropertyId p) const {
    auto it = m_map.find(p);

    if (it == m_map.end()) return nullptr;
    return it->second;
}

// Value get(PropertyName);
