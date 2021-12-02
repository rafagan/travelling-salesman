#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

#include <cmath>

typedef struct Point {
    double x;
    double y;
} Point;

static double calcEuclidianDistance(const Point* p1, const Point* p2) {
    return sqrt(
            (float)pow(p1->x - p2->x, 2.0) +
            (float)pow(p1->y - p2->y, 2.0));
}

#endif
