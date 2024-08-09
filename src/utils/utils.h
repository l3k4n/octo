#ifndef UTILS_H
#define UTILS_H

#include <QIcon>
#include <QString>

namespace octo::utils {

QPixmap createColoredPixmap(const QString &iconPath, const QString &sourceColor,
                         const QString &targetColor);

}  // namespace octo::utils

#endif  // !UTILS_H
