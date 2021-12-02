#include "TSPSolver.h"
#include "io/io.h"
#include "graph/Graph.h"

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
    this->graph = new Graph(points);
    this->minimumSpanningTree = this->findMinimumSpanningTree();
    outputData.weightSum = this->calculateMinimumSpanningTreeCost();

    delete this->graph;

    clock_t endTime = clock();
    outputData.timeSecs = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    return outputData;
}

Graph* TSPSolver::findMinimumSpanningTree() {
    auto* mst = new Graph(vector<Point*>());
    unordered_set<string> visitedNodes;

    auto comparator = [](const Node::EDGE& a, const Node::EDGE& b) {
        return std::get<1>(a) > get<1>(b);
    };
    priority_queue<Node::EDGE, vector<Node::EDGE>, decltype(comparator)> heap(comparator);

    //auto startNodeIndex = rand() % this->graph->vertices.size();
    auto startNodeIndex = 0;
    Node& startNode = this->graph->vertices[startNodeIndex];
    heap.push(Node::EDGE(make_tuple(startNode, 0)));

    for(auto& node : this->graph->vertices) {
        for(auto& edge: node.edges) {
            heap.push(edge);
        }
    }

    Node* previousNode = nullptr;
    while(mst->vertices.size() < this->graph->vertices.size()) {
        auto lowerEdge = heap.top();
        heap.pop();
        auto node = get<0>(lowerEdge);
        auto cost = get<1>(lowerEdge);

        if(previousNode != nullptr && node.toString() == previousNode->toString()) {
            continue;
        }
        const auto contains = visitedNodes.find(node.toString()) != visitedNodes.end();
        if(contains) {
            continue;
        }

        visitedNodes.insert(node.toString());

        auto* currentNode = new Node(node.value, vector<Node::EDGE>());
        if(previousNode != nullptr) {
            currentNode->edges.emplace_back(*previousNode, cost);
            delete previousNode;
        }
        mst->vertices.push_back(*currentNode);
        previousNode = currentNode;

        for(auto& edge: node.edges) {
            const auto contains = visitedNodes.find(get<0>(edge).toString()) != visitedNodes.end();
            if(contains) continue;
            heap.push(edge);
        }
    }

    delete previousNode;
    return mst;
}

double TSPSolver::calculateMinimumSpanningTreeCost() {
    double cost = 0.0;
    for(auto& node: this->minimumSpanningTree->vertices) {
        if(!node.edges.empty()) {
            for(auto& edge: node.edges) {
                cost += get<1>(edge);
            }
        }
    }
    return cost;
}

void TSPSolver::exportTree(const std::string& path) {
    if(minimumSpanningTree == nullptr) return;

    remove( path.c_str());
    ofstream file(path, std::ios_base::app);
    for(auto i = 1; i < this->minimumSpanningTree->vertices.size(); i++) {
        auto& previousNode = this->minimumSpanningTree->vertices[i - 1];
        auto& node = this->minimumSpanningTree->vertices[i];
        file << previousNode.toString() << "\n";
        file << node.toString() << "\n";
    }
    file.flush();
    file.close();
}

void TSPSolver::exportCycle(const std::string& path) {

}