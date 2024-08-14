#ifndef CORE_INSTANCE_H
#define CORE_INSTANCE_H

#include <QObject>
#include <QString>
#include <QVector>

#include "Tab.h"

namespace octo::core {

class Window : public QObject {
    Q_OBJECT;

public:
    Window(QObject* parent = nullptr);

private:
    QVector<Tab> m_tabs;
};

}  // namespace octo::core

#endif  // !CORE_INSTANCE_H
