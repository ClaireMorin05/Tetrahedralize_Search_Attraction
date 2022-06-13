#include "tetrahedron.hpp"

namespace tetrasearch{

    std::vector<int> Tetrahedron::getPoints()
    {
        return points;
    }

    int Tetrahedron::getId()
    {
        return id;
    }
}