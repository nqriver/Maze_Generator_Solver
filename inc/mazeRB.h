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


    std::shared_ptr<Cell> currentCell;
    std::shared_ptr<Cell> nextCell;
    std::stack<std::shared_ptr<Cell>> history;


    std::shared_ptr<Cell> trackedCell { nullptr };
    std::deque<std::shared_ptr<Cell>> solveHistory;
    void setNeighboursBFS(Cell* A, std::vector<std::shared_ptr<Cell>>& neighbours);


    std::shared_ptr<Cell> path { nullptr };
};

#endif // MAZERB_H
