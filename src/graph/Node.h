#ifndef __NODE__H__
#define __NODE__H__

#include <utility>
#include <vector>
#include <string>

struct Point;

struct Node {
    typedef std::tuple<Node*, Node*, double> Edge;

    const Point* value = nullptr;
    std::vector<Edge> edges;

    Node() = default;;

    Node(const Point* value, std::vector<Edge> edges)
        : value(value), edges(std::move(edges)) {};

    [[nodiscard]] std::string toString() const;
};

#endif
