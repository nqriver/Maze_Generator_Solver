#ifndef MAZE_H
#define MAZE_H

#include "cell.h"
#include <array>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MazeGrid; }
QT_END_NAMESPACE

class Maze : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MazeGrid *ui;

public slots:
    virtual void generate() = 0;
    virtual void solve() = 0;
    virtual void drawPath() = 0;
    virtual void setDefaultMazeColor() = 0;

signals:
    void solveFinished();
    void readyToDrawPath();
protected:
    static constexpr int width  { 30 };
    static constexpr int height { 30 };
    std::array<std::array<std::unique_ptr<Cell>, width>, height> grid;
    Cell* entry;      //observer ptr
    Cell* exit;       //observer ptr
    QPointer<QGraphicsScene> scene;

public:

    Maze(QWidget *parent = nullptr);
    ~Maze();
    Cell* getAdjacentCell(Cell*);
    void hideWalls(Cell*, Cell*);
    bool rightNeighbourAvailable(Cell*)  const;
    bool leftNeighbourAvailable(Cell*)   const;
    bool upperNeigbourAvailable(Cell*)   const;
    bool bottomNeighbourAvailable(Cell*) const;



    int sceneHeight() const;
    int sceneWidth()  const;
};
#endif // MAZE_H
