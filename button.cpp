#include "button.h"

Button::Button(QPointF pos, QSizeF size, QString path, GraphicsItem *parent):
    GraphicsItem(pos, size, path, parent)
{
    setFlag(ItemIsFocusable);
}

void Button::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit buttonPressed();
}
