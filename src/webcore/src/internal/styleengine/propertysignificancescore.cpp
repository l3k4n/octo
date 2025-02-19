#include "webcore/internal/styleengine/propertysignificancescore.h"
#include <cstdint>

using namespace StyleEngine;

PropertySignificanceScore::PropertySignificanceScore()
    : m_important(false), m_origin(PropertyOrigin::None) {}

PropertySignificanceScore::PropertySignificanceScore(PropertyOrigin origin, uint32_t specificity, bool important)
    : m_origin(origin), m_important(important), m_specificity(specificity) {}

bool PropertySignificanceScore::isImportant() const { return m_important; }
