#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H
#include <QGraphicsItem>
#include <QPainter>
class GraphicsItem : public QGraphicsItem//图形构件类，是卡片构件、战排构件、背景构件的基类
{
public:
    GraphicsItem(qreal left, qreal top, qreal width, qreal height, QString path,GraphicsItem *parent = Q_NULLPTR);//构件的初始化
    GraphicsItem(qreal left, qreal top, qreal width, qreal height,GraphicsItem *parent = Q_NULLPTR);//构件的初始化
    GraphicsItem(QPointF pos, QSizeF size, QString path, GraphicsItem *parent = Q_NULLPTR);
    GraphicsItem(QPointF pos, QSizeF size, GraphicsItem *parent=Q_NULLPTR);
    ~GraphicsItem();
public:
    QRectF boundingRect() const;//返回构件的位置和尺寸
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);//绘制构件
    void resize(qreal width, qreal height);//改变构件的尺寸
    void resize(QSizeF size){m_width=size.width(); m_height=size.height();}
    void changeImagePath(QString path){m_path=path; m_image.load(path);}//改变图片
    void setLeftTop(qreal x, qreal y){m_left=x; m_top=y;}
    void setLeftTop(QPointF point){m_left=point.x(); m_top=point.y();}
    //void changeText(QString text){m_text=text;}
protected:
    //单位说明：
    //对于背景构件，以下物理量是其在场景中的实际物理量（以像素为单位）；
    //对于非背景构件，是其相对于与背景构件的相对物理量，大小介于0~1
    qreal m_left, m_top;//左上角的横纵坐标
    qreal m_width,m_height;//构件的宽和高
    QString m_path;//构件图片来源
    QImage m_image;//构件的图片
    GraphicsItem* m_parent;//构件的父亲。所有非背景构件的父亲都是背景构件。
    //QString m_text;//构件的文字
};

#endif // GRAPHICSITEM_H
