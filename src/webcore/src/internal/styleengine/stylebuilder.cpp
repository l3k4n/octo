#include "webcore/internal/styleengine/stylebuilder.h"

#include <cstdint>
#include <cstdio>

#include "octocore/debug.h"
#include "webcore/css/cssstyledeclaration.h"
#include "webcore/css/cssstylerule.h"
#include "webcore/css/properties/property.h"
#include "webcore/css/properties/propertydata.h"
#include "webcore/css/selector.h"
#include "webcore/internal/styleengine/computedstyle.h"
#include "webcore/internal/styleengine/propertysignificancescore.h"

using namespace StyleEngine;

StyleBuilder::StyleBuilder() : m_property_scores(CSS::PROPERTY_COUNT) {}

void StyleBuilder::addRuleProperties(const CSS::CSSStyleRule& rule) {
    for (auto decl : rule.declarations()) {
        auto property = CSS::PropertyInstances[size_t(decl.id)];
        // TODO: get rule origin
        PropertySignificanceScore score(PropertyOrigin::None,
                                        computeSpecificity(rule.selectorList()), decl.important);

        if (property->isLonghand()) {
            addLonghandProperty(decl.id, decl.value, score);
        } else {
            auto shorthand = dynamic_cast<CSS::ShorthandProperty*>(property);
            shorthand->applyLonghands(*this, decl.value, score);
        }
    }
}

void StyleBuilder::addLonghandProperty(CSS::PropertyId id, CSS::Value* value,
                                       PropertySignificanceScore score) {
    auto property = dynamic_cast<CSS::LonghandProperty*>(CSS::PropertyInstances[size_t(id)]);
    OCTO_DCHECK(property);

    if (score > m_property_scores[size_t(id)]) {
        m_longhand_declarations.push_back({property, value});
    }
}

void StyleBuilder::computeStyleFor(DOM::Element* element) {
    ComputedStyle* computed_style = element->computedStyle();
    if (!computed_style) {
        computed_style = new ComputedStyle;
        element->setComputedStyle(computed_style);
    }

    for (auto decl : m_longhand_declarations) {
        decl.property->setComputedValue(computed_style, decl.value);
    }
}

uint32_t StyleBuilder::computeSpecificity(const CSS::SelectorList& selector_list) {
    uint32_t specificity = 0;

    for (auto it = selector_list.group_begin(), end = selector_list.group_end(); it != end; ++it) {
        uint8_t a = 0, c = 0;
        uint16_t b = 0;
        for (auto selector : *it) {
            switch (selector.type()) {
                    // clang-format off
                case CSS::Selector::Type::Id:   ++a; break;

                case CSS::Selector::Type::Class:
                case CSS::Selector::Type::Attr: ++b; break;

                case CSS::Selector::Type::Tag:  ++c; break;

                default: break;
                    // clang-format on
            }
        }

        uint32_t result = 0;
        result |= static_cast<uint32_t>(a) << 24;
        result |= static_cast<uint32_t>(b) << 16;
        result |= static_cast<uint32_t>(c) << 8;

        if (result > specificity) specificity = result;
    }

    return specificity;
}
