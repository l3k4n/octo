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
    const Tab& newTab();

signals:
    void newTabCreated(const Tab& tab, size_t pos);

private:
    QVector<Tab*> m_tabs;
};

}  // namespace octo::core

#endif  // !CORE_INSTANCE_H
