#include "Graph.h"
#include <algorithm>
#include <ostream>
#include <utility>
#include <vector>


void Node::add_neighbor(int to, int cost) {
    neibrs.push_back(std::pair<int, int>(to, cost));
}

const std::vector<std::pair<int, int>>& Node::getNeighbors () {
    return neibrs;
}

void Graph::fillGraphFileMatrix(const std::string filename) {
    std::string bufline;
    std::ifstream file;
    file.open(filename);

    if (file.is_open()) {
        std::getline(file, bufline); // amount of nodes
        int n = stoi(bufline);
        nodes.resize(n);
        nodes.clear();

        while (std::getline (file,bufline)) {
            std::istringstream iss(bufline);
            Node newnode;
            for (int i = 0; i < n; i++) {
                int tmp;
                iss >> tmp;
                if (tmp > 0)
                    newnode.add_neighbor(i, tmp);
            }
            nodes.push_back(newnode);
        }
        file.close();
    }
    else {
        throw 1;
    }
}

void Graph::pathRestore(int st_node, int tg_node, std::vector<std::pair<int, int>>& parents) {

    std::cout << "RESTORING PATH " << st_node << " - " << tg_node << std::endl;

    int v = tg_node;
    std::vector<int> path;

    while (v != st_node) {
        int j = 0;
        while (parents[j].first != v) {
            j++;
        }
        path.push_back(parents[j].first);
        v = parents[j].second;
    }
    path.push_back(st_node);

    std::reverse(path.begin(), path.end());

    for (int i = 0; i < path.size() - 1; i++) {
        std::cout << path[i] << " -> ";
    }
    std::cout << path[path.size() - 1] << std::endl;
}

// Переписать восстановление через шаблон
// Вывод вынести отдельно или перегрузить (?)

void Graph::pathRestoreState(State st_state, State tg_state, std::vector<std::pair<State, State>>& parents) {
    std::cout << "RESTORING PATH " << std::endl;

    State v = tg_state;
    std::vector<State> path;

    while (v != st_state) {
        int j = 0;
        while (parents[j].first != v) {
            j++;
        }
        path.push_back(parents[j].first);
        v = parents[j].second;
    }
    path.push_back(st_state);

    std::reverse(path.begin(), path.end());

    for (int i = 0; i < path.size() - 1; i++) {
        std::cout << "STATE " << i << std::endl;
        path[i].printState(); 
    }
    std::cout << "TARGET STATE" << std::endl;
    path[path.size() - 1].printState();
}

bool Graph::breadthSearch(int st_node, int tg_node, bool pathrestore) {
    step_counter = 0;
    std::vector<int> visited;
    std::deque<int> open;
    std::vector<std::pair<int, int>> parents;   // <node, parent_node>

    open.emplace_back(st_node);
    int v;
    
    while (!open.empty()) {
        ++step_counter;
        v = open.front();
        if (v == tg_node) {
            if (pathrestore)                            // path restore flag set
                pathRestore(st_node, tg_node, parents); // path restore 
            return true;
        }
        else {
            visited.push_back(v);
            open.pop_front();
            for (auto nb : nodes[v].getNeighbors()) // node in (open or visited) check
            {
                if (std::find(visited.begin(), visited.end(), nb.first) == visited.end() && 
                    std::find(open.begin(), open.end(), nb.first) == open.end()) {                        
                        open.emplace_back(nb.first);
                        parents.push_back(std::pair<int, int>(nb.first, v));
                    }
            }
        }
    }
    return false;
}



bool Graph::depthSearchIter(const int st_node, const int tg_node, bool pathrestore) {
    step_counter = 0;
    std::vector<int> visited;
    std::deque<int> open;
    std::vector<std::pair<int, int>> parents; // <node, parent_node>
    open.emplace_back(st_node);
    int v;

    while (!open.empty()) {
        ++step_counter;
        
        v = open.front();
        open.pop_front();
        visited.push_back(v);
        
        if (v == tg_node) {
            if (pathrestore)
                pathRestore(st_node, tg_node, parents);
            return true;
        }
        else {
            for (auto nb : nodes[v].getNeighbors()) {
                if (std::find(visited.begin(), visited.end(), nb.first) == visited.end() && 
                        std::find(open.begin(), open.end(), nb.first) == open.end()) {

                    open.emplace_front(nb.first);
                    parents.push_back(std::pair<int, int>(nb.first, v));
                }
            }
        }
    }
    return false;
}

bool Graph::depthSearchRec(const int st_node, const int tg_node, bool pathrestore) {
    std::vector<int> closed;
    step_counter = 0;
    
    if (pathrestore) {
        std::vector<int> path;
        return depthSearchRecRouteCall(st_node, tg_node, closed, path);
    }
    else {
        return depthSearchRecCall(st_node, tg_node, closed);
    }
}

bool Graph::depthSearchRecCall(int cur_node, int tg_node, std::vector<int>& closed) {
    ++step_counter;
    if (cur_node == tg_node) {
        return true;
    }
    else {
        closed.push_back(cur_node);
        for (auto nb : nodes[cur_node].getNeighbors()) {
            if (std::find(closed.begin(), closed.end(), nb.first) == closed.end()) {
                return depthSearchRecCall(nb.first, tg_node, closed);
            }
        }
    }
    return false;
}

bool Graph::depthSearchRecRouteCall(int cur_node, int tg_node, std::vector<int>& closed, std::vector<int> path) {
    ++step_counter;
    if (cur_node == tg_node) {
        std::cout << "SAVED PATH " << path[0] << " - " << tg_node << std::endl;
        for (int i : path) {
            std::cout << i << " -> ";
        }
        std::cout << tg_node << std::endl;
        return true;
    }
    else {
        closed.push_back(cur_node);
        path.push_back(cur_node);
        for (auto nb : nodes[cur_node].getNeighbors()) {
            if (std::find(closed.begin(), closed.end(), nb.first) == closed.end()) {
                return depthSearchRecRouteCall(nb.first, tg_node, closed, path);
            }
        }
    }
    return false;
}





bool Graph::breadthSearchState(State st_state, State tg_state, bool pathrestore) {
    step_counter = 0;

    std::vector<State> visited;   // состояния ранее сгенерированные
    std::deque<State> open;       // состояния ожидающие обработки

    std::vector<std::pair<State, State>> parents;   // <node, parent_node>

    open.emplace_back(st_state);
    State v;

    while (!open.empty()) {
        ++step_counter;

        v = open.front();
        
        if (v == tg_state) {
            if (pathrestore)                            // path restore flag set
                pathRestoreState(st_state, tg_state, parents); // path restore
            return true;
        }
        else {
            visited.push_back(v);
            open.pop_front();

            std::vector<State> newstates = v.genPosStates();
            for (auto i : newstates) {
                if (std::find(visited.begin(), visited.end(), i) == visited.end() && 
                    std::find(open.begin(), open.end(), i) == open.end())
                {
                    open.emplace_back(i);
                    parents.push_back(std::pair<State, State> (i, v));
                }
            }
        }
    }
    return false;
}



// bool Graph::depthSearchRecRouteCallState(State cur_state, State tg_state, std::vector<State>& closed, std::vector<State> path) {
    
//     ++step_counter;

//     if (cur_state == tg_state) {
//         std::cout << "SAVED PATH " << std::endl;
//         for (State i : path) {
//             i.printState();
//         }
//         tg_state.printState();
//         return true;
//     }
//     else {
//         closed.push_back(cur_state);
//         path.push_back(cur_state);

        

//         for (auto nb : nodes[cur_node].getNeighbors()) {
//             if (std::find(closed.begin(), closed.end(), nb.first) == closed.end()) {
//                 return depthSearchRecRouteCall(nb.first, tg_node, closed, path);
//             }
//         }
//     }
//     return false;
// }
