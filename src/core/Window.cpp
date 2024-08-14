#include "Window.h"

#include "Tab.h"

using namespace octo::core;

Window::Window(QObject* parent) : QObject(parent) {}

const Tab& Window::newTab() {
    Tab* tab = new Tab(this);
    m_tabs.push_back(tab);
    emit newTabCreated(*tab, m_tabs.count() - 1);
    return *tab;
}
