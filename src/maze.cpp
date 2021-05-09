#include "inc\maze.h"
#include "ui_mazeGrid.h"

Maze::Maze(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MazeGrid)
    , scene{ new QGraphicsScene() }
{
    ui->setupUi(this);
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::green, Qt::SolidPattern));
    ui->graphicsView->setSceneRect(0, 0, sceneWidth(), sceneHeight());
    ui->graphicsView->setFixedSize(sceneWidth(), sceneHeight());
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            grid[x][y] = std::make_shared<Cell>(x, y, scene);
        }
    }

    entry = grid[0][0];
    exit = grid[width-1][height-1];
}

Maze::~Maze()
{
    delete ui;
}

std::shared_ptr<Cell> Maze::getAdjacentCell(Cell* current)
{
    int currentX { current->get_x() };
    int currentY { current->get_y() };
    std::vector<std::shared_ptr<Cell>> availableCells;

    if (upperNeigbourAvailable(current))
    {
        availableCells.push_back(grid[currentX][currentY-1]);
    }

    if (bottomNeighbourAvailable(current))
    {
        availableCells.push_back(grid[currentX][currentY+1]);
    }

    if (leftNeighbourAvailable(current))
    {
        availableCells.push_back(grid[currentX-1][currentY]);
    }

    if (rightNeighbourAvailable(current))
    {
        availableCells.push_back(grid[currentX+1][currentY]);
    }


    if (!availableCells.empty())
    {
        auto randomIndex = rand() % availableCells.size();
        return availableCells[randomIndex];
    }

    return nullptr;

}

void Maze::hideWalls(Cell* A, Cell* B)
{
    auto A_x { A->get_x() };
    auto A_y { A->get_y() };
    auto B_x { B->get_x() };
    auto B_y { B->get_y() };

    if (A_x - B_x == -1){
        A->hideRightSide();
        B->hideLeftSide();
    }
    else if (A_x - B_x == 1){
        A->hideLeftSide();
        B->hideRightSide();
    }

    if (A_y - B_y == -1){
        A->hideBottomSide();
        B->hideUpperSide();
    }
    else if (A_y - B_y == 1){
        A->hideUpperSide();
        B->hideBottomSide();
    }

}

bool Maze::rightNeighbourAvailable(Cell* cell) const
{
    if (auto x = cell->get_x(), y = cell->get_y(); x < width - 1 && !grid[x+1][y]->isPassed())
    {
        return true;
    }
    return false;
}

bool Maze::leftNeighbourAvailable(Cell* cell) const
{
    if (auto x = cell->get_x(), y = cell->get_y(); x > 0 && !grid[x-1][y]->isPassed())
    {
        return true;
    }
    return false;
}

bool Maze::upperNeigbourAvailable(Cell* cell) const
{
    if (auto x = cell->get_x(), y = cell->get_y(); y > 0 && !grid[x][y-1]->isPassed())
    {
        return true;
    }
    return false;


}

bool Maze::bottomNeighbourAvailable(Cell* cell) const
{
    if (auto x = cell->get_x(), y = cell->get_y(); y < height - 1  && !grid[x][y+1]->isPassed())
    {
        return true;
    }
    return false;

}

//void MazeGrid::setDefaultMazeColor()
//{
//    for(int x = 0; x < width; ++x)
//    {
//        for(int y = 0; y < height; ++y)
//        {
//            grid[x][y]->setColorDefault();
//        }
//    }
//    emit readyToDraw();

//}

int Maze::sceneHeight() const
{
    return height * Cell::sideLength;
}

int Maze::sceneWidth() const
{
    return width * Cell::sideLength;
}



