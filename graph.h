#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <list>
#include <queue>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

class graph{
  public:
    graph(int v);
    void addEdge(int to,int from);
    void showEdges();
    void showDegree();
    void showVisited();
    void getEdgesFromFile(string archiveName);
    void showBP();
  private:
    int vertex;
    int *degree;
    int *visited;
    list<int> * bfs;
    list<int> * bpAux;
    queue<int> * bp;
    vector<pair<int,int> > adjMtx;
    void runBFS(int v);
    void calcEdgeDegree();
    int testConnected(int calc,int start);
    int testBridge(int to,int from);
    int testAllEven();
    void deleteEdge(int to,int from);
    void invertEdge(int v);
    void makeListBp();
    void runBestPath(int start);
    void bpAuxRec(int start,int finalStart);
};

#endif
