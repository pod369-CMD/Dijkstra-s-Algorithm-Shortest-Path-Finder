#include <QCoreApplication>
#include <QDebug>
#include "graph.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Graph g;

    if (!g.loadFromFile("graph.txt")) {
        return -1;
    }

    g.printMatrix();

    int start = 1;
    int finish = 6;

    g.dijkstra(start);
    g.printDistances(start);

    qDebug() << "Кратчайший путь из" << start << "в" << finish << ":";
    qDebug().noquote() << g.getPath(start, finish);

    int cost = g.getDistance(finish);
    if (cost >= 1000000000)
        qDebug() << "Стоимость: INF";
    else
        qDebug() << "Стоимость:" << cost;

    return 0;
}
