#include "core/Tab.h"

#include <QObject>
#include <memory>

#include "core/Window.h"

using namespace octo::core;

Tab::Tab(Window* parent, int position) : QObject(parent), pageData(newPage()), pos(position) {}

Tab::Tab(const QString& url, int position, Window* parent)
    : QObject(parent), pageData(), pos(position) {
    pageData = std::make_unique<PageData>(PageData{"Loading ...", url, QIcon()});
}

const QString& Tab::title() const { return pageData->title; }

const QString& Tab::url() const { return pageData->url; }

const QIcon Tab::favicon() const { return pageData->favicon; }

std::unique_ptr<Tab::PageData> Tab::newPage() {
    return std::make_unique<PageData>(PageData{"New Tab", "", QIcon()});
}

void Tab::setPosition(int position) { pos = position; }

int Tab::position() const { return pos; }

void Tab::navigate(const QString& url) {
    pageData->url = url;
    pageData->title = url;
    emit urlChanged(url);
    emit titleChanged(url);
}
