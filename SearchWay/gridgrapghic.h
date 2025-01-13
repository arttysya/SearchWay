#pragma once

#include <QGraphicsScene>
#include <stack>

#include "clickablerectitem.h"
#include <thread>
#include <mutex>
class GridScene : public QGraphicsScene {
    Q_OBJECT
public:
    void createGrid(int rows, int cols);

public slots:
    void SearchPath();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private slots:
    void handleRectClick();

private:
    void DeleteScene();
    ClickableRectItem* FountItem(const QPointF& position);
    ClickableRectItem* TopItem(QPointF position);
    ClickableRectItem* RightItem(QPointF position);
    ClickableRectItem* LeftItem(QPointF position);
    ClickableRectItem* DownItem(QPointF position);

private:
    ClickableRectItem* FirstPosition{nullptr};
    ClickableRectItem* SecondPosition{nullptr};

    std::stack<ClickableRectItem*> m_path;
    std::thread searchThread;
    bool stopSearch = false;
    std::mutex mutex;
};
