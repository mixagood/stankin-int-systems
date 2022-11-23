#include "Graph.h"
// #include "State.h"
#include <bits/types/struct_timespec.h>
#include <iostream>
#include <map>
#include <time.h>
#include <vector>

#define FILENAME "../src/testgraph1.txt"


void dumbtest (Graph& a) {
    std::cout << a.breadthSearch(0, 1, true) << std::endl;
    // std::cout << a.breadthSearch(0, 2) << std::endl;
    // std::cout << a.breadthSearch(1, 2) << std::endl;
    // std::cout << a.breadthSearch(3, 5) << std::endl;


    std::cout << a.depthSearchIter(0, 1, true) << std::endl;


    std::cout << a.depthSearchRec(0, 1, true) << std::endl;
    // std::cout << a.depthSearchRec(0, 2) << std::endl;
    // std::cout << a.depthSearchRec(1, 2) << std::endl;
    // std::cout << a.depthSearchRec(0, 1, false) << std::endl;
    

    // struct timespec ts;
    // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    // double time = (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
    // std::cout << time << std::endl;
}



int main () {
    // Graph a;
    // a.fillGraphFileMatrix(FILENAME);
    // dumbtest(a);

    std::map<std::string, bool> target_map;
    target_map["собака"] = true;
    target_map["волк1"] = true;
    target_map["волк2"] = true;
    target_map["капуста"] = true;
    target_map["крестьянин"] = true;
    target_map["козел"] = true;

    State start;
    State target(target_map);

    Graph a;
    std::cout << a.breadthSearchState(start, target, true) << std::endl;
    
    return 0;
}
