#pragma once

#include <QGraphicsView>
#include <memory>

#include "gridgrapghic.h"

class FieldsView : public QGraphicsView
{
public:
    FieldsView(QWidget *parent = nullptr);

    GridScene* GetScene()
    {return m_Scene.get();}

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    std::unique_ptr<GridScene> m_Scene;

};
