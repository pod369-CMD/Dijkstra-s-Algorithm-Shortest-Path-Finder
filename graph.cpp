#include "graph.h"
#include <QFile>
#include <QTextStream>
#include <QStack>
#include <QDebug>

Graph::Graph()
{
    n = 0;
    m = 0;
    matrix = nullptr;
    dist = nullptr;
    parent = nullptr;
    used = nullptr;
}

Graph::~Graph()
{
    clearMemory();
}

void Graph::clearMemory()
{
    if (matrix != nullptr) {
        for (int i = 0; i <= n; ++i) {
            delete[] matrix[i]; //удалить строки
        }
        delete[] matrix; //удалить массив указателей
        matrix = nullptr;
    }

    delete[] dist;
    dist = nullptr;

    delete[] parent;
    parent = nullptr;

    delete[] used;
    used = nullptr;

    n = 0;
    m = 0;
}

bool Graph::loadFromFile(const QString &fileName)
{
    clearMemory();

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл:" << fileName;
        return false;
    }

    QTextStream in(&file);//Создаём поток чтения из файла

    in >> n >> m;

    matrix = new int*[n + 1];
    for (int i = 0; i <= n; ++i) {
        matrix[i] = new int[n + 1];
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == j)
                matrix[i][j] = 0;
            else
                matrix[i][j] = INF;
        }
    }

    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        in >> from >> to >> weight;
        matrix[from][to] = weight;
    }

    dist = new int[n + 1];
    parent = new int[n + 1];
    used = new bool[n + 1];

    file.close();
    return true;
}

void Graph::printMatrix() const
{
    qDebug() << "Матрица смежности:";

    QString header = "     ";
    for (int j = 1; j <= n; ++j) {
        header += QString("%1 ").arg(j, 6);
    }
    qDebug().noquote() << header;

    for (int i = 1; i <= n; ++i) {
        QString row = QString("%1 ").arg(i, 3); //вставить j шириной 6 на место %1
        for (int j = 1; j <= n; ++j) {
            if (matrix[i][j] == INF)
                row += QString("%1 ").arg("INF", 6);
            else
                row += QString("%1 ").arg(matrix[i][j], 6);
        }
        qDebug().noquote() << row;
    }
}

int Graph::findMinVertex() const
{
    int minVertex = -1;
    int minValue = INF;

    for (int i = 1; i <= n; ++i) {
        if (!used[i] && dist[i] < minValue) {
            minValue = dist[i];
            minVertex = i;
        }
    }

    return minVertex;
}

void Graph::dijkstra(int start)
{
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
        parent[i] = -1;
        used[i] = false;
    }

    dist[start] = 0;

    for (int step = 1; step <= n; ++step) {
        int v = findMinVertex();

        if (v == -1) {
            break;
        }

        used[v] = true;

        for (int to = 1; to <= n; ++to) {
            if (matrix[v][to] != INF && !used[to]) {
                if (dist[v] + matrix[v][to] < dist[to]) {
                    dist[to] = dist[v] + matrix[v][to];
                    parent[to] = v;
                }
            }
        }
    }
}

void Graph::printDistances(int start) const
{
    qDebug() << "Оценки кратчайших путей из вершины" << start << ":";

    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF)
            qDebug() << "До вершины" << i << ": INF";
        else
            qDebug() << "До вершины" << i << ":" << dist[i];
    }
}

QString Graph::getPath(int start, int finish) const
{
    if (finish < 1 || finish > n) {
        return "Некорректная конечная вершина";
    }

    if (dist[finish] == INF) {
        return "Пути нет";
    }

    QStack<int> stack;
    int current = finish;

    while (current != -1) {
        stack.push(current);
        current = parent[current];
    }

    QString result;
    while (!stack.isEmpty()) {
        result += QString::number(stack.pop());
        if (!stack.isEmpty()) {
            result += " -> ";
        }
    }

    return result;
}

int Graph::getDistance(int finish) const
{
    if (finish < 1 || finish > n) {
        return INF;
    }
    return dist[finish];
}
