#include "text.h"

text::text(QPointF pos, QSizeF size, GraphicsItem *parent):GraphicsItem(pos, size, parent)
{
    m_text="";
    m_fontSize=10;
    m_fontColor=Qt::black;
    m_backgroundColor=Qt::transparent;
    m_isCenter=false;
}

text::text(QPointF pos, QSizeF size, std::string text, int fontSize, QColor fontColor,
           QColor backgroundColor, GraphicsItem *parent):
    GraphicsItem(pos, size, parent)
{
    m_text=QString::fromStdString(text);
    m_fontSize=fontSize;
    m_fontColor=fontColor;
    m_backgroundColor=backgroundColor;
    m_isCenter=false;
}

text::text(QPointF pos, QSizeF size, int fontSize, QColor fontColor,
           QColor backgroundColor, GraphicsItem *parent):
    GraphicsItem(pos, size, parent)
{
    m_text="";
    m_fontSize=fontSize;
    m_fontColor=fontColor;
    m_backgroundColor=backgroundColor;
    m_isCenter=false;
}

void text::setText(std::string text)
{
    m_text=QString::fromStdString(text);
}

void text::setFontSize(int fontSize)
{
    m_fontSize=fontSize;
}

void text::setFontColor(QColor fontColor)
{
    m_fontColor=fontColor;
}

void text::setBackgroundColor(QColor backgroundColor)
{
    m_backgroundColor=backgroundColor;
}

void text::setCenter()
{
    m_isCenter=true;
}

void text::setLeft()
{
    m_isCenter=false;
}

void text::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(m_text.isEmpty())
        return;

    painter->save();

    QBrush brush=QBrush();
    brush.setColor(m_backgroundColor);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    //painter->drawRect(boundingRect());
    painter->fillRect(boundingRect(),brush);

    QFont font=QFont();
    font.setPointSize(m_fontSize);
    painter->setFont(font);
    painter->setPen(m_fontColor);
    if(m_isCenter)
    {
        painter->drawText(boundingRect(), Qt::AlignCenter, m_text);
    }
    else
    {
        painter->drawText(boundingRect(), m_text);
    }

    painter->restore();
}
