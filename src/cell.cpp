#include "inc\cell.h"

Cell::Cell(int x, int y, QGraphicsScene *scene) :
    position{x, y},
    pen{ new QPen() },
    passed{ false },
    visited{ false },
    wayLeft{ false },
    wayRight{ false },
    wayUp{ false },
    wayDown{ false }
{
    auto temp_x { x * sideLength };
    auto temp_y { y * sideLength };

    square = std::make_unique<QGraphicsRectItem>(temp_x, temp_y, sideLength, sideLength);
    square->setBrush(QBrush(QColor(Qt::green), Qt::SolidPattern));
    pen->setWidth(4);
    square->setPen(Qt::NoPen);
//    square->show();
//    pen->setColor(QColor(Qt::black));
    upper = std::make_unique<QGraphicsLineItem>(temp_x, temp_y, temp_x + sideLength, temp_y);
    bottom = std::make_unique<QGraphicsLineItem>(temp_x, temp_y + sideLength, temp_x + sideLength, temp_y + sideLength);
    left = std::make_unique<QGraphicsLineItem>(temp_x, temp_y, temp_x, temp_y + sideLength);
    right = std::make_unique<QGraphicsLineItem>(temp_x + sideLength, temp_y, temp_x + sideLength, temp_y + sideLength);
    upper->setPen(*pen);
    bottom->setPen(*pen);
    right->setPen(*pen);
    left->setPen(*pen);

    scene->addItem(square.get());
    scene->addItem(upper.get());
    scene->addItem(bottom.get());
    scene->addItem(left.get());
    scene->addItem(right.get());
}

bool Cell::isPassed() const
{
    return passed;
}

bool Cell::isVisited() const
{
    return visited;
}

void Cell::setCellStatusPassed()
{
    passed = true;
}

void Cell::setVisited()
{
    visited = true;
}

int Cell::get_x() const
{
    return position.x;
}

int Cell::get_y() const
{
    return position.y;
}

void Cell::showCurrentCell()
{
    square->show();
}

void Cell::hideCurrentCell()
{
    square->hide();
}

void Cell::hideRightSide()
{
    right->hide();
    wayRight = true;
}

void Cell::hideLeftSide()
{
    left->hide();
    wayLeft = true;
}

void Cell::hideUpperSide()
{
    upper->hide();
    wayUp = true;
}

void Cell::hideBottomSide()
{
    bottom->hide();
    wayDown = true;
}

bool Cell::wayLeftOpen() const
{
    return wayLeft;
}

bool Cell::wayRightOpen() const
{
    return wayRight;
}

bool Cell::wayUpOpen() const
{
    return wayUp;
}

bool Cell::wayDownOpen() const
{
    return wayDown;
}

void Cell::setColorRed()
{
    square->setBrush(QBrush(QColor(Qt::red), Qt::SolidPattern));
}

void Cell::setColorMagenta()
{
    square->setBrush(QBrush(QColor(Qt::darkMagenta), Qt::SolidPattern));
}

void Cell::setColorBlue()
{
    square->setBrush(QBrush(QColor(Qt::blue), Qt::Dense2Pattern));
}

void Cell::setColorDefault()
{
    square->setBrush(QBrush(QColor(Qt::darkGreen), Qt::SolidPattern));
}

//void Cell::setCircle(QPointer<QGraphicsScene> scene)
//{
//    circle = std::make_unique< QGraphicsEllipseItem >(position.x*sideLength, position.y * sideLength sideLength, sideLength);
//    circle->setBrush(QBrush(QColor(Qt::blue), Qt::SolidPattern));
//    circle->setPen(Qt::NoPen);
//    scene->addItem(circle.get());
//}
