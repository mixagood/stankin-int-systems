#include "State.h"
#include <map>
#include <vector>

bool State::checkState(std::map<std::string, bool>& st) { // Создается копия, применяет изменение

    if (st["собака"] == st["козел"] && (st["крестьянин"] != st["собака"]))
        return false;
    if ((st["собака"] == st["волк1"] || st["собака"] == st["волк2"]) && st["крестьянин"] != st["собака"])
        return false;
    if (st["козел"] == st["капуста"] && st["крестьянин"] != st["козел"])
        return false;
    if ((st["козел"] == st["волк1"] || st["козел"] == st["волк2"]) && st["крестьянин"] != st["козел"])
        return false;
    return true;
}

std::vector<State> State::genPosStates() {

    std::vector<State> pos_states; // возможные состояния

    std::vector<std::string> pos_keys;
    bool mainkey = state["крестьянин"];  // захардкодил мужика

    // Отбор значений, которые возможно заменить
    for (auto i : state) {
        if (i.second == mainkey && i.first != "крестьянин") {
            pos_keys.push_back(i.first);
        }
    }

    for(int i = 0; i < pos_keys.size(); i++) {

        // отдельная обработка для одной замены 
        std::map<std::string, bool> state_checkcopy(state); // копия
        state_checkcopy[pos_keys[i]] = !state[pos_keys[i]];
        state_checkcopy["крестьянин"] = !state_checkcopy["крестьянин"];
        if (checkState(state_checkcopy)) {
            State newstate(state_checkcopy);
            pos_states.push_back(newstate);
        }

        // перебираются пары, так как по условию 2 места в лодке
        for (int j = i + 1; j < pos_keys.size(); j++) {
            std::map<std::string, bool> state_checkcopy(state); // копия
            state_checkcopy[pos_keys[i]] = !state[pos_keys[i]];
            state_checkcopy[pos_keys[j]] = !state[pos_keys[j]];
            state_checkcopy["крестьянин"] = !state_checkcopy["крестьянин"];

            if (checkState(state_checkcopy)) {
                State newstate(state_checkcopy);
                pos_states.push_back(newstate);
            }
        }
    }

    return pos_states;
}
