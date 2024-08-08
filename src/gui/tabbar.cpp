#include "tabbar.h"

#include <QPainter>
#include <QPainterPath>

#include "delegates/tabbutton.h"

using namespace octo::gui;

TabBarView::TabBarView(QWidget *parent) {
    new octo::gui::TabBarButtonDelegate(this);
    setParent(parent);
    setItemDelegate(new TabBarButtonDelegate(this));
    setSelectionMode(QListView::SelectionMode::SingleSelection);
    setEditTriggers(QListView::NoEditTriggers);
    setFlow(QListView::LeftToRight);
    setUniformItemSizes(true);
    setFixedHeight(40);
    setIconSize(QSize(20, 20));
    setSpacing(2);
    setMouseTracking(true);
    setObjectName("TabBarView");
}
