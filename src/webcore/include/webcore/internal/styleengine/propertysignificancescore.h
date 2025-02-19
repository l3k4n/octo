#ifndef WEBCORE_INTERNAL_STYLE_ENGINE_PROPERTY_SIGNIFICANCE_SCORE_H
#define WEBCORE_INTERNAL_STYLE_ENGINE_PROPERTY_SIGNIFICANCE_SCORE_H

#include <cstdint>
namespace StyleEngine {

enum class PropertyOrigin : uint8_t { None = 0, UserAgent, Author, Inline };

class PropertySignificanceScore {
public:
    PropertySignificanceScore();
    PropertySignificanceScore(PropertyOrigin, uint32_t specificity, bool important);

    bool operator>(PropertySignificanceScore other) const {
        return m_specificity > other.m_specificity;
    }

    bool isImportant() const;

private:
    bool m_important;
    PropertyOrigin m_origin;
    uint32_t m_specificity;
};

}  // namespace StyleEngine

#endif  // !WEBCORE_INTERNAL_STYLE_ENGINE_PROPERTY_SIGNIFICANCE_SCORE_H
