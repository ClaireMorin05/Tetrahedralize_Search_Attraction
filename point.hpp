#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <vector>
//#include "tetrahedron.hpp"
#include <set>

namespace tetrasearch{

    class tetrahedron;

    //bool comparatorSet(point a, point b){ return a.samePoints(b); }

    class point{

        public :

            point( float _x, float _y, float _z, std::vector<tetrahedron> _tetra ) 
            : x( _x ), y( _y ), z( _z ), tetra( _tetra ), point_attract(std::vector<point>()) { computeNeighbours(); };

            ~point(){};

            static bool comparatorSet(point a, point b){ return a.samePoints(b); }

            std::vector<float> getCoord(); 
            std::vector<tetrahedron> getTetrahedron();
            std::vector<point> getPointAttract();
            std::vector<point> getNeighbours();

            //===========test set================
            //std::set<point, decltype(comparatorSet)> getNeighbours();

            bool isAttract ( point p, float attract_distance );

            void addPoint ( point p );

            void searchAdjPoint ();

            void computeNeighbours();

            bool samePoints ( point p );

            void computePointAttract( float r );

        private :

            float x;
            float y;
            float z;
        
            std::vector<tetrahedron> tetra;
            std::vector<point> point_attract;
            std::vector<point> neighbours;

            //===========test set================
            //std::set<point, decltype(comparatorSet)> neighbours;

    };
}

#endif