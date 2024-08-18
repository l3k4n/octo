#include "gui/navbarbutton.h"

QPixmap createColoredPixmap(const QString &iconPath, const QString &sourceColor,
                            const QString &targetColor) {
    auto pixmap = QPixmap(iconPath);
    auto mask = pixmap.createMaskFromColor(QColor(sourceColor), Qt::MaskOutColor);
    pixmap.fill(QColor(targetColor));
    pixmap.setMask(mask);

    return pixmap;
}


NavBarButton::NavBarButton(const QString& iconPath, QWidget* parent) : QPushButton(parent) {
    QIcon icon;
    QPixmap enabled_pixmap = createColoredPixmap(iconPath, "#fff", "#ccc");
    QPixmap disabled_pixmap = createColoredPixmap(iconPath, "#fff", "#333");
    icon.addPixmap(enabled_pixmap, QIcon::Mode::Active);
    icon.addPixmap(disabled_pixmap, QIcon::Mode::Disabled);

    setIcon(icon);
    setObjectName("NavBarBtn");
}
