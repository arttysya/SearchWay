#include "gridgrapghic.h"

#include <QObject>
#include <qdebug.h>
#include <queue>
#include <vector>

#include <unordered_set>
#include <QGraphicsSceneMouseEvent>
constexpr uint32_t BASE_SIZE = 20;
struct searchData
{
    ClickableRectItem* l_pItem{nullptr};
    bool visited{false};
};
void GridScene::createGrid(int rows, int cols) {
    int id{-1};
    DeleteScene();
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            ClickableRectItem* rect = new ClickableRectItem(++id, col * BASE_SIZE, row * BASE_SIZE, BASE_SIZE, BASE_SIZE);
            if(!rect)
                continue;
            connect(rect, &ClickableRectItem::PressOnRect, this, &GridScene::handleRectClick);
            rect->setPen(QPen(Qt::black));
            addItem(rect);


        }
    }
}

void GridScene::handleRectClick(){
    auto* rect = qobject_cast<ClickableRectItem*>(sender());
    if (!(rect && rect->GetType() != kot::black))
        return;
    if(FirstPosition == nullptr)
    {
        FirstPosition = rect;
        FirstPosition->setSelected(true);
        return;
    }

    if(FirstPosition == rect)
    {
        FirstPosition->setSelected(false);
        SecondPosition = nullptr;
        return;
    }

}

void GridScene::DeleteScene()
{
    auto Items = items();
    for(auto& item: Items)
        removeItem(item);

    FirstPosition = nullptr;
    SecondPosition = nullptr;

}

void GridScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    try {


    QPointF mousePos = event->scenePos();
    auto item = itemAt(mousePos, QTransform());
    ClickableRectItem *rect = dynamic_cast<ClickableRectItem*>(item);

    if (!(rect && FirstPosition && rect->GetType() != kot::black &&  rect != SecondPosition)) {
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }


    if (SecondPosition == FirstPosition) {
        SecondPosition= nullptr;
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }

    if (SecondPosition != nullptr) {
        SecondPosition->setSelected(false);
    }

    SecondPosition = rect;
    SecondPosition->setSelected(true);

    // Проверка на пустоту пути
        while (!m_path.empty()) {
            if (m_path.top() == FirstPosition) break;
            m_path.top()->setSelected(false);
            m_path.pop();
        }
    if (searchThread.joinable()) {
           searchThread.join();
       }
    searchThread = std::thread(&GridScene::SearchPath, this);
    searchThread.detach();
    QGraphicsScene::mouseMoveEvent(event);
    } catch (std::exception& e) {
        qDebug() << e.what();
    }
}

void GridScene::SearchPath()
{
    std::lock_guard<std::mutex> lock(mutex);



    // Проверка на нулевые указатели
    if (FirstPosition == nullptr || SecondPosition == nullptr) return;

    std::unordered_set<ClickableRectItem*> visited;
    std::vector<ClickableRectItem*> parent(static_cast<size_t>(items().size()), nullptr);
    std::queue<ClickableRectItem*> queue;

    visited.insert(FirstPosition);
    queue.push(FirstPosition);

    while (!queue.empty()) {
        ClickableRectItem* vertex = queue.front();
        queue.pop();

        if (vertex == SecondPosition) {
            break;
        }

        QPointF position = vertex->rect().topLeft();
        ClickableRectItem* neighbor{nullptr};

        // Проверка соседей
        for (const auto& direction : {TopItem(position), RightItem(position), LeftItem(position), DownItem(position)}) {
            neighbor = direction;
            if (neighbor && neighbor->GetType() != kot::black && visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor->GetId()] = vertex;
                queue.push(neighbor);
            }
        }
    }

    // Восстановление пути
    for (ClickableRectItem* v = SecondPosition; v != nullptr; v = parent[v->GetId()]) {
        m_path.push(v);
    }

    if (!m_path.empty() && m_path.top() == FirstPosition) {
        while (!m_path.empty()) {
            if (m_path.top() != FirstPosition && m_path.top() != SecondPosition)
                m_path.top()->Path();
            m_path.pop();
        }
    } else {
        qDebug() << "Путь не найден." << endl;
    }
}

ClickableRectItem* GridScene::TopItem(QPointF position)
{
    position.setY(position.y() - BASE_SIZE);
    return FountItem(position);
}
ClickableRectItem* GridScene::RightItem(QPointF position)
{
    position.setX(position.x() + BASE_SIZE);
    return FountItem(position);
}
ClickableRectItem* GridScene::LeftItem(QPointF position)
{
    position.setX(position.x() - BASE_SIZE);
    return FountItem(position);
}
ClickableRectItem* GridScene::DownItem(QPointF position)
{
    position.setY(position.y() + BASE_SIZE);
    return FountItem(position);
}
ClickableRectItem* GridScene::FountItem(const QPointF& Position)
{
    auto rect = itemAt(Position, QTransform());
    return dynamic_cast<ClickableRectItem*>(rect);
}

