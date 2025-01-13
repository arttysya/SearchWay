#pragma once

#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QObject>

enum class kot{ black, white};

class ClickableRectItem : public QObject, public QGraphicsRectItem {
     Q_OBJECT
public:
    ClickableRectItem(int id, qreal x, qreal y, qreal width, qreal height);
    void setSelected(bool selected);
    int GetId(){return id_;}
    void Path();
    kot GetType(){return type_kot;}
signals:
    void PressOnRect();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int id_;
   kot type_kot;
};
