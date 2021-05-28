#ifndef MAZERB_H
#define MAZERB_H

#include "cell.h"
#include "maze.h"

#include <memory>
#include <deque>
#include <stack>

#include <QPointer>
#include <QTimer>
#include <QTime>


class MazeRB : public Maze
{

public slots:
    void generate() override;
    void solve() override;
    void drawPath() override;
    void setDefaultMazeColor() override;

public:
    MazeRB(QWidget *parent = nullptr);

private:


    QPointer<QTimer> timer  { nullptr };
    QPointer<QTimer> timer2 { nullptr };
    QPointer<QTimer> timer3 { nullptr };


    Cell* currentCell;  //used in generating algorithm
    Cell* nextCell;     //used in generating algorithm
    std::stack<Cell*> history; //used in generating algorithm


    Cell* trackedCell { nullptr }; //used in solving algorithm
    std::deque<Cell*> solveHistory; //used in solving algorithm
    void setNeighboursBFS(Cell* A, std::vector<Cell*>& neighbours); //used in solving algorithm


    Cell* path { nullptr }; //used in final path drawing
};

#endif // MAZERB_H
