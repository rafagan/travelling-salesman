#include "TSPSolver.h"
#include "io/io.h"
#include "graph/Graph.h"
#include "graph/Node.h"

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
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
    outputData.weightSum = this->findDepthFirstSearchCycle();

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
    while(mstEdges.size() < this->graph->vertices.size() - 1) {
        auto lowerEdge = heap.top();
        heap.pop();
        auto destNode = get<1>(lowerEdge);

        // Contains
        if(visitedNodes.find(destNode->toString()) != visitedNodes.end()) continue;

        visitedNodes.insert(destNode->toString());
        if(get<0>(lowerEdge) != nullptr) mstEdges.push_back(lowerEdge);

        for(auto& edge: destNode->edges) {
            auto nextNode = get<1>(edge);
            // Contains
            if(visitedNodes.find(nextNode->toString()) != visitedNodes.end()) continue;
            heap.push(edge);
        }
    }

    return mstEdges;
}

double TSPSolver::findDepthFirstSearchCycle() {
    unordered_map<string, Node*> vertices;
    for(auto edge: this->minimumSpanningTreeEdges) {
        auto origin = get<0>(edge);
        auto dest = get<1>(edge);
        if(vertices.count(origin->toString()) == 0) {
            vertices[origin->toString()] = new Node(origin->value, vector<Node::Edge>());
        }
        if(vertices.count(dest->toString()) == 0) {
            vertices[dest->toString()] = new Node(dest->value, vector<Node::Edge>());
        }

        vertices[origin->toString()]->edges.push_back(edge);
    }

    Graph mst;
    for(auto& pair: vertices) {
        auto node = pair.second;
        mst.vertices.push_back(node);
    }

    for(auto& node: mst.vertices) {
        cout << "Eu sou o " << node->toString();
        cout << " e tenho como filhos:" << endl;
        for(auto& edge: node->edges) {
            cout << "\t" << get<1>(edge)->toString() << endl;
        }
    }

    cout << "xxx" << endl;
    return 0;
}

void TSPSolver::exportTree(const std::string& path) {
    remove( path.c_str());
    ofstream file(path, std::ios_base::app);
    for(auto edge: this->minimumSpanningTreeEdges) {
        auto origin = get<0>(edge);
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