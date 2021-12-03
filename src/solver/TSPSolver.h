#ifndef __TSP_SOLVER_H__
#define __TSP_SOLVER_H__

#include <string>
#include "graph/Node.h"

class Graph;
struct OutputData;
struct InputData;

class TSPSolver {
private:
    Graph* graph = nullptr;
    std::vector<Node::Edge> minimumSpanningTreeEdges;
    std::vector<Node::Edge> cycleEdges;

    std::vector<Node::Edge> findMinimumSpanningTreeEdges();
    double findDepthFirstSearchCycle();
public:
    ~TSPSolver();

    OutputData solveGreedily(InputData inputData);
    void exportTree(const std::string& path);
    void exportCycle(const std::string& path);
};

#endif