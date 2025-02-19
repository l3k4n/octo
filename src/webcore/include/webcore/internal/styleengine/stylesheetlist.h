#ifndef WEBCORE_INTERNAL_STYLE_ENGINE_STYLESHEET_LIST_H
#define WEBCORE_INTERNAL_STYLE_ENGINE_STYLESHEET_LIST_H

#include <memory>
#include <vector>

#include "webcore/css/cssstylesheet.h"

namespace StyleEngine {

typedef std::vector<std::unique_ptr<CSS::CSSStyleSheet>> StyleSheetList;

}

#endif  // !WEBCORE_INTERNAL_STYLE_ENGINE_STYLESHEET_LIST_H
