#include "inc\mazeRB.h"
#include <iostream>

MazeRB::MazeRB(QWidget *parent)
    : Maze(parent)
{
    currentCell = grid[0][0].get();
    currentCell->setCellStatusPassed();
    currentCell->setColorMagenta();
    history.push(currentCell);

    timer = new QTimer(this);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);
    timer->setInterval(10);
    timer2->setInterval(12);
    timer3->setInterval(12);

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(generate()));


    entry->visitedFrom = nullptr;
    solveHistory.push_back(entry);
    entry->setVisited();

    path = exit;

    QObject::connect(timer2, SIGNAL(timeout()), this, SLOT(solve()));
    QObject::connect(timer, SIGNAL(timeout()), timer2, SLOT(start()));

    QObject::connect(this, SIGNAL(solveFinished()), this, SLOT(setDefaultMazeColor()));

    QObject::connect(timer3, SIGNAL(timeout()), this, SLOT(drawPath()));
    QObject::connect(this, SIGNAL(readyToDrawPath()), timer3, SLOT(start()));
    timer->start();

}


void MazeRB::drawPath(){
    path->setColorBlue();
    path = path->visitedFrom;

    if (path == entry){
        timer3->stop();
        path->setColorBlue();
    }
}

void MazeRB::setDefaultMazeColor(){
    for(int x = 0; x < Maze::width; ++x)
    {
        for(int y = 0; y < Maze::height; ++y)
        {
            grid[x][y]->setColorDefault();
//            std::cout << grid[x][y].use_count() << '\n';
        }
    }
    emit readyToDrawPath();
}



void MazeRB::solve()
{
    trackedCell = solveHistory.front();
    trackedCell->setColorRed();

    std::vector<Cell*> neighbours{};
    setNeighboursBFS(trackedCell, neighbours);
    solveHistory.pop_front();

    if (trackedCell == exit){
        timer2->stop();
        emit solveFinished();
        std::cout << "\n\nDONE !!!";
    }


    for (auto &neighbour : neighbours){
        if (!neighbour->isVisited()){
            solveHistory.push_back(neighbour);
            neighbour->setVisited();
            neighbour->visitedFrom = trackedCell;
//            std::cout << neighbour->get_x() << "::" << neighbour->get_y() <<'\t'
//                      << neighbour->visitedFrom->get_x() << "::" << neighbour->visitedFrom->get_y() <<'\n';
        }
    }

    if (solveHistory.empty()){
        timer2->stop();
        std::cout <<"\nEMPTY. !!!";
    }
}


void MazeRB::generate(){
    nextCell = getAdjacentCell(currentCell);
    if (nextCell != nullptr)
    {
        hideWalls(currentCell, nextCell);
        currentCell->setColorDefault();
        nextCell->setColorMagenta();
        history.push(nextCell);
        nextCell->setCellStatusPassed();
        currentCell = nextCell;
    }
    else if (!history.empty())
    {
        currentCell->setColorDefault();
        currentCell = history.top();
        history.pop();
        currentCell->setColorMagenta();
    }
    else if (history.empty())
    {
        currentCell->setColorDefault();
        timer->stop();
    }
}


void MazeRB::setNeighboursBFS(Cell* A, std::vector<Cell*>& neighbours)
{
    neighbours.clear();
    int A_x { A->get_x() };
    int A_y { A->get_y() };

    if (A->wayDownOpen() && A_y < Maze::height - 1){
        neighbours.push_back(grid[A_x][A_y+1].get());
    }

    if (A->wayUpOpen() && A_y > 0){
        neighbours.push_back(grid[A_x][A_y-1].get());
    }

    if (A->wayLeftOpen() && A_x > 0){
        neighbours.push_back(grid[A_x-1][A_y].get());
    }

    if (A->wayRightOpen() && A_x < Maze::width - 1){
        neighbours.push_back(grid[A_x+1][A_y].get());
    }

}
