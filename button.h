#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <graphicsitem.h>

class Button : public QObject, public GraphicsItem
{
    Q_OBJECT
public:
    explicit Button(QPointF pos, QSizeF size, QString path, GraphicsItem *parent = Q_NULLPTR);


signals:
    void buttonPressed();
public slots:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BUTTON_H
