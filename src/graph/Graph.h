#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include "Node.h"

struct Graph {
    std::vector<Node> vertices;

    explicit Graph(const std::vector<Point*>& values);
};

#endif
