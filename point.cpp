#include <cmath>
#include "point.hpp"
#include "tetrahedron.hpp"

namespace tetrasearch{

    std::vector<float> point::getCoord() 
    {
        std::vector<float> coord;
        coord.push_back(this->x);
        coord.push_back(this->y);
        coord.push_back(this->z);

        return coord;
    }


    std::vector<tetrahedron> point::getTetrahedron()
    {
        return this->tetra;
    }

    std::vector<point> point::getPointAttract()
    {
        return this->point_attract;
    }

    std::set<point> point::getNeighbours()
    {
        return this->neighbours;
    }

    bool point::isAttract(point p, float attract_distance)
    {
        std::vector<float> p_coord; 
        p_coord = p.getCoord();

        float x = p_coord[0] - this->x;
        float y = p_coord[1] - this->y;
        float z = p_coord[2] - this->z;

        if ( sqrt( x * x + y * y + z * z) > attract_distance)
            return false;

        else
            return true;
    }

    void point::addPoint( point p )
    {
        point_attract.push_back(p);
    }

    bool point::samePoints( point p )
    {
        std::vector<float> pCoords = p.getCoord();

        if ( pCoords[0] != this->x || pCoords[1] != this->y || pCoords[2] != this->z )
            return false;
        
        else
            return true;
    }

    std::set<point> point::computeNeighbours()
    {
        /*std::set<point> neighbours;

        for ( int i = 0; i < tetra.size(); i++)
        {
            for ( int j = 0; j < 4; j++)
            {
                if ( !this->samePoints(tetra[i].getPoints()[j]) )
                    neighbours.insert(tetra[i].getPoints()[j]);
            } 
        }
        
        return neighbours;*/
        return std::set<point>();
    }

    void point::computePointAttract( float r )
    {
        std::set<point> points = this->computeNeighbours();

    }

}