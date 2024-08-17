#include "Window.h"

#include <QWidget>
#include <QtGlobal>
#include <QtNumeric>

#include "Tab.h"

using namespace octo::core;

Window::Window(QObject* parent) : QObject(parent) {}

Tab& Window::newTab() {
    Tab* tab = new Tab(this, m_tabs.count());
    m_tabs.push_back(tab);
    emit newTabCreated(*tab);
    return *tab;
}

void Window::moveTab(int from, int to) {
    Q_ASSERT_X(qAbs(from - to) <= 1, "Window::moveTab",
               "Tab moved more than a single position at once");

    m_tabs.at(from)->setPosition(to);
    m_tabs.at(to)->setPosition(from);
    m_tabs.swapItemsAt(from, to);
}

void Window::closeTab(int idx) { m_tabs.takeAt(idx)->deleteLater(); }
