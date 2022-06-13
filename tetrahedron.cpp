#include "tetrahedron.hpp"

namespace tetrasearch{

    std::vector<int> tetrahedron::getPoints()
    {
        return points;
    }

    int tetrahedron::getId()
    {
        return id;
    }
}