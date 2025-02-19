#ifndef WEBCORE_INTERNAL_STYLE_ENGINE_BUILDER_H
#define WEBCORE_INTERNAL_STYLE_ENGINE_BUILDER_H

#include <cstdint>
#include <vector>

#include "webcore/css/properties/property.h"
#include "webcore/css/properties/propertyid.h"
#include "webcore/css/selectorlist.h"
#include "webcore/dom/element.h"
#include "webcore/internal/styleengine/computedstyle.h"
#include "webcore/internal/styleengine/propertysignificancescore.h"

namespace CSS {
class CSSStyleRule;
};  // namespace CSS

namespace StyleEngine {

class StyleBuilder {
    struct LonghandDeclaration {
        CSS::LonghandProperty* property;
        CSS::Value* value;
    };

public:
    StyleBuilder();
    void addRuleProperties(const CSS::CSSStyleRule&);
    void addLonghandProperty(CSS::PropertyId, CSS::Value*, PropertySignificanceScore);
    static uint32_t computeSpecificity(const CSS::SelectorList& selector_list);

    void computeStyleFor(DOM::Element*);

private:
    // TODO: using CSSStyleDeclaration duplicates importance with m_property_scores
    std::vector<LonghandDeclaration> m_longhand_declarations;
    std::vector<PropertySignificanceScore> m_property_scores;
};

}  // namespace StyleEngine

#endif  // !WEBCORE_INTERNAL_STYLE_ENGINE_BUILDER_H
