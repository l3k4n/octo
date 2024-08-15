#ifndef GUI_NAV_BAR_BUTTON_H
#define GUI_NAV_BAR_BUTTON_H

#include <QPushButton>

namespace octo::gui {

class NavBarButton : public QPushButton {
public:
    NavBarButton(const QString& iconPath, QWidget* parent = nullptr);
};

}  // namespace octo::gui

#endif  // !GUI_NAV_BAR_BUTTON_H
