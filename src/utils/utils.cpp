#include "utils.h"

#include <QBitmap>
#include <QIcon>
#include <QPixmap>

namespace utils = octo::utils;

QPixmap utils::createColoredPixmap(const QString &iconPath, const QString &sourceColor,
                                   const QString &targetColor) {
    auto pixmap = QPixmap(iconPath);
    auto mask = pixmap.createMaskFromColor(QColor(sourceColor), Qt::MaskOutColor);
    pixmap.fill(QColor(targetColor));
    pixmap.setMask(mask);

    return std::move(pixmap);
}
