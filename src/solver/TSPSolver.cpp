#include "TSPSolver.h"
#include "io/io.h"
#include "graph/Graph.h"
#include "graph/Node.h"

#include <vector>
#include <unordered_set>
#include <queue>
#include <fstream>

using namespace std;

OutputData TSPSolver::solveGreedily(InputData inputData) {
    clock_t startTime = clock();

    vector<Point*> points;
    for(int i = 0; i < inputData.count; i++) {
        Point* point = inputData.points[i];
        points.push_back(point);
    }

    OutputData outputData = OutputData();
    delete this->graph;
    this->graph = new Graph(points);
    this->minimumSpanningTreeEdges = this->findMinimumSpanningTreeEdges();
    outputData.weightSum = 0;

    clock_t endTime = clock();
    outputData.timeSecs = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    return outputData;
}

vector<Node::Edge> TSPSolver::findMinimumSpanningTreeEdges() {
    unordered_set<string> visitedNodes;

    auto comparator = [](const Node::Edge& a, const Node::Edge& b) {
        return std::get<2>(a) >= get<2>(b);
    };
    priority_queue<Node::Edge, vector<Node::Edge>, decltype(comparator)> heap(comparator);

    //auto startNodeIndex = rand() % this->graph->vertices.size();
    auto startNodeIndex = 0;
    Node* startNode = this->graph->vertices[startNodeIndex];
    heap.push(Node::Edge(make_tuple(nullptr, startNode, 0)));

    vector<Node::Edge> mstEdges;
    while(mstEdges.size() < this->graph->vertices.size()) {
        auto lowerEdge = heap.top();
        heap.pop();
        auto destNode = get<1>(lowerEdge);

        const auto contains = visitedNodes.find(destNode->toString()) != visitedNodes.end();
        if(contains) continue;

        visitedNodes.insert(destNode->toString());
        mstEdges.push_back(lowerEdge);

        for(auto& edge: destNode->edges) {
            auto nextNode = get<1>(edge);
            const auto contains = visitedNodes.find(nextNode->toString()) != visitedNodes.end();
            if(contains) continue;
            heap.push(edge);
        }
    }

    return mstEdges;
}

void TSPSolver::findDepthFirstSearchCycle() {

}

//double TSPSolver::calculateMinimumSpanningTreeCost() {
//    double cost = 0.0;
//    for(auto& node: this->minimumSpanningTree->vertices) {
//        if(!node->edges.empty()) {
//            for(auto& edge: node->edges) {
//                cost += get<2>(edge);
//            }
//        }
//    }
//    return cost;
//}

void TSPSolver::exportTree(const std::string& path) {
    remove( path.c_str());
    ofstream file(path, std::ios_base::app);
    for(auto edge: this->minimumSpanningTreeEdges) {
        auto origin = get<0>(edge);
        if(origin == nullptr) continue;
        auto dest = get<1>(edge);
        file << origin->toString() << "\n";
        file << dest->toString() << "\n";
    }
    file.flush();
    file.close();
}

void TSPSolver::exportCycle(const std::string& path) {

}

TSPSolver::~TSPSolver() {
    delete graph;
}