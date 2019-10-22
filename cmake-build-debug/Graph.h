#pragma once
#ifndef COURSEWORK_GRAPH_H
#define COURSEWORK_GRAPH_H
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

class Graph {
public:

	explicit Graph(unsigned short);

	void printMatrix(); 

	void Task(); 

	void print(vector<int>, int);

	void printComponent(); 

	void dfs1(int); 

	void dfs2(int); 

	~Graph() {};
	
private:

	vector<int> order, component;
	
	vector<vector<int>> g, gr; 
	
	vector<int> used1, used2;
	
	int vertices;
};

void Graph::print(vector<int> component, int size) {
	cout << "Vertices of the strongly connected component are: ";
	for (int i = 0; i < size; i++)
		cout << component[i];
	cout << endl;
	cout << "The graph of strongly connected component is:" << endl;
	printComponent();
}

void Graph::printComponent() {
	int k = 0;
	for (int i = 0; i < component.size(); ++i) {
		cout << component[i] << " connected with: ";
		for (int j = 0; j < g[component[i]].size(); ++j) {
			for (int k = 0; k < component.size(); ++k) {
				if (g[component[i]][j] == component[k])
					cout << component[k] << " ";
			}
		}
		cout << endl;
	}
	cout << endl << endl;
}

void Graph::printMatrix() {
	int a = 0;
	for (auto &k : g) {
		cout << a++ << ": ";
		if (!k.empty()) {
			for (auto c : k)
				cout << c << " ";
		}
		cout << endl;
	}
}

void Graph::Task() {
	for (int i = 0; i < vertices; ++i)
		if (!used1[i])
			dfs1(i);

	used1.assign(vertices, false);

	cout << endl;
	for (int i = 0; i < vertices; ++i) {
		int v = order[vertices - 1 - i];
		if (!used1[v]) {
			dfs2(v);
			print(component, component.size());
			component.clear();
		}
	}
}

Graph::Graph(unsigned short size) : vertices(size), used1(size, false), order(0), component(0) {
	
	g.resize(size);
	gr.resize(size);
	
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			//if(i != j) //Are loops allowed or not?
				if (rand() % 5 == 1) {
					g.at(i).push_back(j); // Filing the graph
					gr.at(j).push_back(i); // Filling the reversed graph
				}
		}
	}	
}

void Graph::dfs1(int v) {
	used1[v] = true;
	for (int i = 0; i < g[v].size(); ++i) {
		if (!used1[g[v][i]])
			dfs1(g[v][i]);
	}
	order.push_back(v);
}

void Graph::dfs2(int v) {
	used1[v] = true;
	component.push_back(v);
	for (size_t i = 0; i < gr[v].size(); ++i) {
		if (!used1[gr[v][i]]) {
			dfs2(gr[v][i]);
		}
	}

}

#endif //COURSEWORK_GRAPH_H