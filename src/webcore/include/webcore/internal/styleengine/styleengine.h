#ifndef WEBCORE_INTERNAL_STYLE_ENGINE_ENGINE_H
#define WEBCORE_INTERNAL_STYLE_ENGINE_ENGINE_H

#include <memory>

#include "webcore/css/cssstylesheet.h"
#include "webcore/internal/styleengine/stylesheetlist.h"

namespace DOM {
class Document;
}

namespace StyleEngine {

class StyleEngine {
public:
    StyleEngine(DOM::Document* owner);
    StyleEngine(const StyleEngine&) = delete;

    void computeStyles();
    void addStyleSheet(std::unique_ptr<CSS::CSSStyleSheet>);

private:
    DOM::Document* const m_owner;
    StyleSheetList m_stylesheet_list;
};

}  // namespace StyleEngine

#endif  // !WEBCORE_INTERNAL_STYLE_ENGINE_ENGINE_H
