#include "paintedItem.h"

SPView::SPView(QQuickItem *parent)
    :QQuickPaintedItem(parent)
{

}

SPView::~SPView()
{

}

void SPView::clear()
{
    purgePaintElements();
    update();
}

