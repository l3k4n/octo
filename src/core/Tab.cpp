#include "Tab.h"

#include <QObject>
#include <memory>

#include "Window.h"

using namespace octo::core;

Tab::Tab(Window* parent) : QObject(parent), pageData(newPage()) {}

Tab::Tab(const QString& url, Window* parent) : QObject(parent), pageData() {
    pageData = std::make_unique<PageData>(PageData{"Loading ...", url, QIcon()});
}

const QString& Tab::title() const { return pageData->title; }

const QString& Tab::url() const { return pageData->url; }

const QIcon Tab::favicon() const { return pageData->favicon; }

std::unique_ptr<Tab::PageData> Tab::newPage() {
    return std::make_unique<PageData>(PageData{"New Tab", "", QIcon()});
}
