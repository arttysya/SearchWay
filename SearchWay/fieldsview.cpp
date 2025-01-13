#include "fieldsview.h"

#include <QWheelEvent>

FieldsView::FieldsView(QWidget *parent ):
    QGraphicsView(parent),
    m_Scene(std::make_unique<GridScene>())
{
    setScene(m_Scene.get());
}

void FieldsView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0) {
        scale(1.1, 1.1);
    } else {
        scale(1.0 / 1.1, 1.0 / 1.1);
    }
    event->accept();
}

