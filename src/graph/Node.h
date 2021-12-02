#ifndef __NODE__H__
#define __NODE__H__

#include <utility>
#include <vector>
#include <string>

struct Point;

struct Node {
    typedef std::tuple<Node, double> EDGE;

    const Point* value = nullptr;
    std::vector<EDGE> edges;

    Node() = default;;

    Node(const Point* value, std::vector<EDGE> edges)
        : value(value), edges(std::move(edges)) {};

    std::string toString() const;
};

#endif
