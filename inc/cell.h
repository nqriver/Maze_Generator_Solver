#ifndef CELL_H
#define CELL_H

#include <memory>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QPointer>

struct Coordinates{
    int x, y;
};


class Cell {
private:
    Coordinates position;
    QPen* pen;
    bool passed{};
    bool visited{};

    bool wayLeft{};
    bool wayRight{};
    bool wayUp{};
    bool wayDown{};


//    std::unique_ptr<QGraphicsEllipseItem> circle{};
    std::unique_ptr<QGraphicsRectItem> square{};
    std::unique_ptr<QGraphicsLineItem> upper{};
    std::unique_ptr<QGraphicsLineItem> bottom{};
    std::unique_ptr<QGraphicsLineItem> left{};
    std::unique_ptr<QGraphicsLineItem> right{};

public:
    std::shared_ptr<Cell> visitedFrom;
    static constexpr int sideLength { 20 };

    Cell(int x, int y, QGraphicsScene *scene);
    bool isPassed() const;
    bool isVisited() const;
    void setCellStatusPassed();
    void setVisited();
    int get_x() const;
    int get_y() const;
    void showCurrentCell();
    void hideCurrentCell();

    void hideRightSide();
    void hideLeftSide();
    void hideUpperSide();
    void hideBottomSide();

    bool wayLeftOpen()  const;
    bool wayRightOpen() const;
    bool wayUpOpen()    const;
    bool wayDownOpen()  const;

    void setColorRed();
    void setColorBlue();
    void setColorMagenta();
    void setColorDefault();

//    void setCircle(QPointer<QGraphicsScene>);
};

#endif // CELL_H
