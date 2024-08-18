#ifndef GUI_NAV_BAR_BUTTON_H
#define GUI_NAV_BAR_BUTTON_H

#include <QPushButton>

class NavBarButton : public QPushButton {
public:
    NavBarButton(const QString& iconPath, QWidget* parent = nullptr);
};

#endif  // !GUI_NAV_BAR_BUTTON_H
