#include "navbarbutton.h"

#include "utils.h"

using namespace octo;
using namespace octo::gui;

NavBarButton::NavBarButton(const QString& iconPath, QWidget* parent) : QPushButton(parent) {
    QIcon icon;
    QPixmap enabled_pixmap = utils::createColoredPixmap(iconPath, "#fff", "#ccc");
    QPixmap disabled_pixmap = utils::createColoredPixmap(iconPath, "#fff", "#333");
    icon.addPixmap(enabled_pixmap, QIcon::Mode::Active);
    icon.addPixmap(disabled_pixmap, QIcon::Mode::Disabled);

    setIcon(icon);
    setObjectName("NavBarBtn");
}
