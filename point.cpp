#include <cmath>
#include "point.hpp"
#include "tetrahedron.hpp"
#include <iostream>
#include <cstdio>
namespace tetrasearch{

    std::vector<float> point::getCoord() 
    {
        std::vector<float> coord;
        coord.push_back(this->x);
        coord.push_back(this->y);
        coord.push_back(this->z);

        return coord;
    }

    int point::getId()
    {
        return this->id;
    }
    void point::addTetrahedron(tetrahedron* t)
    {
        this->tetra.push_back(t);
    }

    std::vector<tetrahedron*> point::getTetrahedron()
    {
        return this->tetra;
    }

    std::vector<point*> point::getPointAttract()
    {
        return this->point_attract;
    }

    std::vector<point*> point::getNeighbours()
    {
        return this->neighbours;
    }

    bool point::isAttract(point* p, float attract_distance)
    {
        std::vector<float> p_coord; 
        p_coord = p->getCoord();

        float x = p_coord[0] - this->x;
        float y = p_coord[1] - this->y;
        float z = p_coord[2] - this->z;

        if ( sqrt( x * x + y * y + z * z) > attract_distance)
            return false;

        else
            return true;
    }

    void point::addPoint( point* p )
    {
        point_attract.push_back(p);
    }

    bool point::samePoints( point* p )
    {
        std::vector<float> pCoords = p->getCoord();

        if ( pCoords[0] != this->x || pCoords[1] != this->y || pCoords[2] != this->z )
            return false;
        
        else
            return true;
    }

    void point::computeNeighbours()
    {
        bool belongs = false;

        for ( int i = 0; i < (int)tetra.size(); i++)
        {
            for ( int j = 0; j < 4; j++)
            {
                belongs = false;

                if ( !this->samePoints(tetra[i]->getPoints()[j]) )
                {
                    for ( int k = 0; k < (int)neighbours.size(); k++ )
                    {
                        if( this->neighbours[k]->samePoints(tetra[i]->getPoints()[j]))
                        {
                            belongs = true;
                            break;
                        }
                    }

                    if ( !belongs )
                        neighbours.push_back(tetra[i]->getPoints()[j]);
                }
            } 
        }
        
    }

    void point::computePointAttract( float r )
    {
        std::vector<point* > points = this->neighbours;
        std::vector<point* > traveled_points = this->neighbours;
        bool belongs = false;

        while ( points.size() != 0)
        {

            if ( this->isAttract( points[0], r ) )
            {
                this->point_attract.push_back(points[0]);
                for ( int i = 0; i < (int)points[0]->getNeighbours().size(); i++ )
                {
                    belongs = false;

                    for ( int j = 0; j < (int)traveled_points.size(); j++ ) 
                    {
                        
                        if ( points[0]->getNeighbours()[i]->samePoints( traveled_points[j]) || this->samePoints(points[0]->getNeighbours()[i]) )
                        {
                            belongs = true;
                            break;
                        }
                            
                    }

                    if ( !belongs )
                    {
                        traveled_points.push_back(points[0]->getNeighbours()[i]);
                        points.push_back(points[0]->getNeighbours()[i]);
                    }

                }
            }

            points.erase(points.begin());
        }

    }

}