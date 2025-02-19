#include "webcore/internal/styleengine/styleengine.h"

#include "octocore/debug.h"
#include "webcore/dom/document.h"
#include "webcore/dom/element.h"
#include "webcore/dom/nodefilter.h"
#include "webcore/dom/treewalker.h"
#include "webcore/html/htmlbodyelement.h"
#include "webcore/html/htmlhtmlelement.h"
#include "webcore/internal/styleengine/stylebuilder.h"
#include "webcore/internal/styleengine/stylerulematcher.h"

namespace StyleEngine {

StyleEngine::StyleEngine(DOM::Document* owner) : m_owner(owner) {}

void StyleEngine::computeStyles() {
    StyleRuleMatcher matcher(m_stylesheet_list);
    DOM::TreeWalker walker(m_owner->body(), DOM::NodeFilter::SHOW::ELEMENT);
    DOM::Element* element = dynamic_cast<DOM::Element*>(walker.currentNode());
    OCTO_DCHECK(element && element == walker.currentNode());

    while (element) {
        StyleBuilder style_builder;
        for (auto it = matcher.findMatches(element), end = matcher.end(); it != end; ++it) {
            style_builder.addRuleProperties(*it);
        }
        style_builder.computeStyleFor(element);

        element = dynamic_cast<DOM::Element*>(walker.nextNode());
    }
}

void StyleEngine::addStyleSheet(std::unique_ptr<CSS::CSSStyleSheet> stylesheet) {
    m_stylesheet_list.push_back(std::move(stylesheet));
}

}  // namespace StyleEngine
