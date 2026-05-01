#ifndef GRAPH_H
#define GRAPH_H

#include <QString>

class Graph
{
private:
    int n;          // число вершин
    int m;          // число дуг
    int **matrix;   // матрица смежности
    //Матрица смежности - динамический двумерный массив
    //int** используется, потому что это указатель на массив указателей,где каждый указатель указывает на строку матрицы
    int *dist;      // оценки кратчайших расстояний
    int *parent;    // предки для восстановления пути
    bool *used;     // окончательно помеченные вершины

    const int INF = 1000000000;

    void clearMemory();
    int findMinVertex() const; //поиск вершины с минимальной оценкой среди всех непомеченных вершин та, у которой:
    //used[i] == false,dist[i] минимально,метод не изменяет объект(const)

public:
    Graph();
    ~Graph();
ё
    bool loadFromFile(const QString &fileName);//метод для ввода графа.принимает имя файла, открывает его,
   // считывает данные о вершинах и дугах и заполняет матрицу смежности. Метод возвращает логическое значение: true, если чтение прошло успешно, и false

    void printMatrix() const;
    void dijkstra(int start);
    void printDistances(int start) const;//вывод итоговых оценок
    QString getPath(int start, int finish) const;//путь
    int getDistance(int finish) const;// длина
};

#endif // GRAPH_H
