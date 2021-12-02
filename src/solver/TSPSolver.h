#ifndef __TSP_SOLVER_H__
#define __TSP_SOLVER_H__

#include <string>

class Graph;
struct OutputData;
struct InputData;

class TSPSolver {
private:
    Graph* graph = nullptr;
    Graph* minimumSpanningTree = nullptr;

    Graph* findMinimumSpanningTree();
    double calculateMinimumSpanningTreeCost();
public:
     OutputData solveGreedily(InputData inputData);
     void exportTree(const std::string& path);
     void exportCycle(const std::string& path);
};

#endif