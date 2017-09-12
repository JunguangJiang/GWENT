#ifndef TEXT_H
#define TEXT_H

#include "graphicsitem.h"
//文本框类

class text : public GraphicsItem
{
public:
    text(QPointF pos, QSizeF size, GraphicsItem* parent=Q_NULLPTR);
    text(QPointF pos, QSizeF size, std::string text, int fontSize,
         QColor fontColor, QColor backgroundColor, GraphicsItem *parent=Q_NULLPTR);
    text(QPointF pos, QSizeF size, int fontSize,
         QColor fontColor, QColor backgroundColor, GraphicsItem *parent=Q_NULLPTR);
    void setText(std::string);//设置文本内容
    void setFontSize(int fontSize);//设置文本字体大小
    void setFontColor(QColor color);//设置字体颜色
    void setBackgroundColor(QColor color);//设置文本框背景颜色
    void setCenter();//设置字体居中
    void setLeft();//设置靠右对齐
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QString m_text;
    int m_fontSize;
    QColor m_fontColor;
    QColor m_backgroundColor;
    bool m_isCenter;//是否居中
};

#endif // TEXT_H
