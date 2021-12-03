#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>

class Node;
struct Point;

struct Graph {
    std::vector<Node*> vertices;

    Graph();
    explicit Graph(const std::vector<Point*>& values);
    ~Graph();
};

#endif
