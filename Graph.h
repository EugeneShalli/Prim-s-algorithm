#pragma once
#ifndef COURSEWORK_GRAPH_H
#define COURSEWORK_GRAPH_H
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include<ctime>

using namespace std;

class Graph {
public:

	explicit Graph(unsigned short);

	void printMatrix(); 

	void Task();

	~Graph() {};
	
private:
	const int INF = INT32_MAX - 1;

	vector<vector<int>> g;

	int vertices, rebra;

};

void Graph::printMatrix() {
//Это просто печать матрицы смежности
    cout << "This is adjacency matrix of graph:" << endl;
    for (const auto &c : g) {
        for (int d : c)
            if(d == INF) cout << setw(4) << " / "; else // для красоты
                cout << setw(4) <<  d;
        cout << endl;
    }
    cout << "------------" << endl;
}

void Graph::Task() {
//Это тот алгоритм, который я описывал, только с небольшим изменением:
//Здесь мы для каждой ещё не выбранной вершины храним минимальное ребро, ведущее в уже выбранную вершину
//На текущем шаге, чтобы выбрать минимальное ребро, нам надо просто посмотреть минимальные ребра всех еще не выбранных вершин
    vector<unsigned > closest(vertices,0);
    vector<int> lowcost(g.at(0));
    cout << "MST contains following edges:" << endl;
    int t1 = clock();
    for (int i = 1; i < vertices; ++i) {
        int min = lowcost.at(1);
        unsigned k = 1;
        for (unsigned j = 2; j < vertices; ++j) {
            if(lowcost.at(j) < min){
                min = lowcost.at(j);
                k = j;
            }
        }
        if (lowcost[k] == INF) {
            cout << "No MST!";
            exit(0);
        }
        cout << "(" << k << " " << closest.at(k)<< ")" << endl;
        lowcost.at(k) = INF + 1;
        for (unsigned l = 1; l < vertices; ++l) {
            if((g.at(k).at(l) < lowcost.at(l)) && lowcost.at(l) < INF + 1){
                lowcost.at(l) = g.at(k).at(l);
                closest.at(l) = k;
            }
        }
    }
    int t2 = clock();
    cout << endl << vertices << endl << rebra;
    cout << endl << (float)(t2 - t1) / CLOCKS_PER_SEC << endl;
}

Graph::Graph(unsigned short size) : vertices(size)/*, used1(size, false), min_e(vertices, INF), sel_e(vertices, (0 - 1)), order(0), component(0) */{
//Это инициализация Графа и генерация случайного графа

    srand(time(0));
    g.resize(vertices);
    rebra = 0;
    for (int i = 0; i < vertices; i++) {
        g[i].resize(vertices);
    }


//Случайная генерация
    for (int i = 0; i < vertices; i++) {
        for (int j = i; j < vertices; j++) {
            if (i == j) {
                g[i][j] = INF;
            } else {
                if (rand() % 4 != 1) {
                    rebra++;
                    g[i][j] = g[j][i] = rand() % 101;
                } else g[i][j] = g[j][i] = INF;
            }
        }
    }


/*
    //        0
    //      /   \
    //    3/     \5
    //    /       \
    //    1-------2
    //        4
    g[0][0] = INF;
    g[0][1] = 3;
    g[0][2] = 5;
    g[1][0] = 3;
    g[1][1] = INF;
    g[1][2] = 4;
    g[2][0] = 5;
    g[2][1] = 4;
    g[2][2] = INF;
*/

/*
    g[0][0] = INF;
    g[0][1] = INF;
    g[0][2] = INF;
    g[1][0] = INF;
    g[1][1] = INF;
    g[1][2] = INF;
    g[2][0] = INF;
    g[2][1] = 4;
    g[2][2] = INF;
*/

/*
//          0
//         / \
//       1/   \4
//       /     \
//      1       2
//       \     /
//       2\   /3
//         \ /
//          3
    g[0][0] = INF;
    g[0][1] = 1;
    g[0][2] = 4;
    g[0][3] = INF;
    g[1][0] = 1;
    g[1][1] = INF;
    g[1][2] = INF;
    g[1][3] = 2;
    g[2][0] = 4;
    g[2][1] = INF;
    g[2][2] = INF;
    g[2][3] = 3;
    g[3][0] = INF;
    g[3][1] = 2;
    g[3][2] = 3;
    g[3][3] = INF;
*/

}
#endif //COURSEWORK_GRAPH_H
