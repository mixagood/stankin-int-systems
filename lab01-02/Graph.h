/*
Mishchenko Mikhail IDB-20-07, 2022

Node is determined by it's number in Graph's "nodes" vector, 
needs template

*/

#include <vector>
#include <string>
#include <fstream>
#include <deque>
#include <utility>
#include <algorithm>
#include <iostream>
#include <sstream>

#include "State.h"

class Node {
private:
    std::vector<std::pair<int, int>> neibrs; // <destination, cost> node neighbors

public:
    void add_neighbor(int, int);
    const std::vector<std::pair<int, int>>& getNeighbors();
};

class Graph {
private:
    std::vector<Node> nodes; // Nodes of graph

    unsigned int step_counter;

    bool depthSearchRecCall(int cur_node, int tg_node, std::vector<int>& closed);

    bool depthSearchRecRouteCall(int cur_node, int tg_node, std::vector<int>& closed, std::vector<int> path); // по значению
    
    void pathRestore(int st_node, int tg_node, std::vector<std::pair<int, int>>& parents);

    void pathRestoreState(State st_state, State tg_state, std::vector<std::pair<State, State>>& parents);

public:
    void fillGraphFileMatrix(const std::string filename);

    bool depthSearchIter(const int st_node, const int tg_node, bool pathrestore=false);

    bool depthSearchRec(const int st_node, const int tg_node, bool pathrestore=false);

    bool breadthSearch(const int st_node, const int tg_node, bool pathrestore=false);

    bool breadthSearchState(State st_state, State tg_state, bool pathrestore);

    // Graph(const Graph&) = delete;
    // void operator=(const Graph&) = delete;
    // Graph(const Graph&&) = delete;
};