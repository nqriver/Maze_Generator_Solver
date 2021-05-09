#include "inc\mazeRB.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MazeRB w;
    w.show();
    return a.exec();
}
