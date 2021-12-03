#include "Graph.h"

#include "math/math_util.h"
#include "Node.h"

using namespace std;

Graph::Graph() = default;

Graph::Graph(const std::vector<Point*>& values) {
    vertices = vector<Node*>();
    for(auto& point : values) {
        vertices.push_back(new Node(point, vector<Node::Edge>()));
    }

    for(auto i = 0; i < values.size(); i++) {
        Node* node = vertices[i];
        for(int j = 0; j < values.size(); j++) {
            if(i == j) continue;
            node->edges.emplace_back(
                    node,
                    vertices[j],
                    calcEuclidianDistance(node->value, vertices[j]->value)
            );
        }
    }
}

Graph::~Graph() {
    for(Node* node: vertices) {
        delete node;
    }
}
