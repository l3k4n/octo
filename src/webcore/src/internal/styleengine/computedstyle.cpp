
#include "webcore/internal/styleengine/computedstyle.h"

using namespace StyleEngine;

CSS::SizeValue* ComputedStyle::width() { return m_width; }
CSS::SizeValue* ComputedStyle::height() { return m_height; }
CSS::ColorValue::RGBA ComputedStyle::color() { return m_color; }
CSS::ColorValue::RGBA ComputedStyle::backgroundColor() { return m_background_color; }

void ComputedStyle::setWidth(CSS::SizeValue* width) { m_width = width; }
void ComputedStyle::setHeight(CSS::SizeValue* height) { m_height = height; }
void ComputedStyle::setColor(CSS::ColorValue::RGBA color) { m_color = color; }
void ComputedStyle::setBackgroundColor(CSS::ColorValue::RGBA color) { m_background_color = color; };
