/*
Mishchenko Mikhail IDB-20-07, 2022

FOR LAB02

Variant 11 (26 % 15)
*/

#include <utility>
#include <vector>
#include <map>
#include <string>
#include <iostream>

class State {
private:
    std::map<std::string, bool> state;                  // хранит состояния системы

    bool checkState(std::map<std::string, bool>& st);    // проверить состояние

public:
    std::vector<State> genPosStates(); // сгенерировать возможные состояния системы
    void readStateFile(); // считать состояние из файла

    State() {
        state["козел"] = 0;
        state["собака"] = 0;
        state["капуста"] = 0;
        state["волк1"] = 0;
        state["волк2"] = 0;
        state["крестьянин"] = 0;
    }

    State(std::vector<std::pair<std::string, bool>>& init) {
        for (auto i : init) {
            state[i.first] = i.second;
        }
    }

    State(std::map<std::string, bool>& init) {
        state = init;
    }

    void printState() {
        std::cout << "----------" << std::endl;
        for (auto i : state) {
            std::cout << i.first << " : " << i.second << std::endl;
        }
        std::cout << "----------" << std::endl;
    }
};
