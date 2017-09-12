#include "graphicsitem.h"
#include <QDebug>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
GraphicsItem::GraphicsItem(qreal left, qreal top, qreal width, qreal height, QString path,GraphicsItem *parent):
   m_left(left),m_top(top), m_width(width), m_height(height), m_path(path),QGraphicsItem(parent)
 // @note: 构件的父亲必须也是QGraphicsItem类
{
    m_image.load(path);
    m_parent=parent;
}

GraphicsItem::GraphicsItem(qreal left, qreal top, qreal width, qreal height,GraphicsItem *parent):
   m_left(left),m_top(top), m_width(width), m_height(height), m_path(""),QGraphicsItem(parent)
 // @note: 构件的父亲必须也是QGraphicsItem类
{
    m_parent=parent;
}

GraphicsItem::GraphicsItem(QPointF pos, QSizeF size, QString path, GraphicsItem *parent):
    m_left(pos.x()),m_top(pos.y()), m_width(size.width()), m_height(size.height()),m_path(path), QGraphicsItem(parent)
{
    m_image.load(path);
    m_parent=parent;
}

GraphicsItem::GraphicsItem(QPointF pos, QSizeF size, GraphicsItem *parent):
    m_left(pos.x()),m_top(pos.y()), m_width(size.width()), m_height(size.height()),m_path(""), QGraphicsItem(parent)
{
    m_parent=parent;
}


GraphicsItem::~GraphicsItem()
{
    //QGraphicsItem::~QGraphicsItem();
}

QRectF GraphicsItem::boundingRect()const
{
    qreal absoluteWidth=this->scene()->views().at(0)->width();
    qreal absoluteHeight=this->scene()->views().at(0)->height();

    return QRectF(m_left*absoluteWidth, m_top*absoluteHeight,
              m_width*absoluteWidth, m_height*absoluteHeight);
    /*
    if(this->parentItem())//如果是非背景构件，要按照背景构件的当前尺寸调整该构件的实际尺寸
    {
        qreal absoluteWidth=this->scene()->views().at(0)->width();
        qreal absoluteHeight=this->scene()->views().at(0)->height();
        //return QRectF(m_left*m_parent->m_width, m_top*m_parent->m_height,
          //        m_width*m_parent->m_width, m_height*m_parent->m_height);
        return QRectF(m_left*absoluteWidth, m_top*absoluteHeight,
                  m_width*absoluteWidth, m_height*absoluteHeight);
    }
    else//如果是背景构件，则直接返回背景构件的尺寸
    {
        //qDebug()<<this->scene()->views().at(0)->width();
        //qDebug()<<this->scene()->items();
        return QRectF(m_left, m_top,
                  m_width, m_height);
        //return QRectF(this->scene()->width(), this->scene()->height(),
          //        this->scene()->width(), this->scene()->height());
    }*/
}

void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!m_image.isNull()){
        painter->drawImage(boundingRect(),m_image);
    }
    /*
    if(m_text!="")
    {
        painter->save();
        QBrush brush=QBrush(Qt::lightGray);
        painter->setBrush(brush);
        painter->drawRect(boundingRect());
        QFont font=QFont();
        font.setPointSize(16);
        painter->setFont(font);
        painter->drawText(boundingRect(),m_text);
        painter->restore();
    }*/
}


void GraphicsItem::resize(qreal width, qreal height)
{
    m_width=width;
    m_height=height;
}


