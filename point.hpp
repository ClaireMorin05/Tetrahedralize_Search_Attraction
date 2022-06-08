#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <vector>
//#include "tetrahedron.hpp"
#include <set>

namespace tetrasearch{

    class tetrahedron;

    class point{

        public :

            point( float _x, float _y, float _z, std::vector<tetrahedron> _tetra ) 
            : x( _x ), y( _y ), z( _z ), tetra( _tetra ), point_attract(std::vector<point>()), neighbours( computeNeighbours() ) {};

            ~point(){};

            std::vector<float> getCoord(); 
            std::vector<tetrahedron> getTetrahedron();
            std::vector<point> getPointAttract();
            std::set<point> getNeighbours();

            bool isAttract ( point p, float attract_distance );

            void addPoint ( point p );

            void searchAdjPoint ();

            std::set<point> computeNeighbours();

            bool samePoints ( point p );

            void computePointAttract( float r );

        private :

            float x;
            float y;
            float z;
        
            std::vector<tetrahedron> tetra;
            std::vector<point> point_attract;
            std::set<point> neighbours;
    };
}

#endif