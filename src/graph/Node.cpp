#include "Node.h"
#include <iomanip>
#include <string>
#include <sstream>

#include "math/math_util.h"

using namespace std;

string Node::toString() const {
    std::stringstream stream;
    stream << (int)value->x;
    stream << " ";
    stream << (int)value->y;
    return stream.str();
}