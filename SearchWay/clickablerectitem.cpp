#include "clickablerectitem.h"
#include <random>
ClickableRectItem::ClickableRectItem(int id,qreal x, qreal y, qreal width, qreal height)
    : QGraphicsRectItem(x, y, width, height),
    id_(id)
{
    setPen(QPen(Qt::black));
    setAcceptHoverEvents(true);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(0.0, 1.0); // Генерация числа от 0 до 1

    double random_number = distrib(gen);
    if (random_number > 0.15) { // 85% вероятность белого
        type_kot = kot::white;
        setBrush(QBrush(Qt::white));
    } else { // 15% вероятность черного
        type_kot = kot::black;
        setBrush(QBrush(Qt::black));
    }
}


void ClickableRectItem::setSelected(bool selected) {
    if (selected) {
        setBrush(QBrush(Qt::red));
    } else {
        setBrush(QBrush(Qt::white));
    }
}


void ClickableRectItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    emit PressOnRect();
    QGraphicsRectItem::mousePressEvent(event);
}

void ClickableRectItem::Path()
{
    setBrush(QBrush(Qt::darkRed));
}
