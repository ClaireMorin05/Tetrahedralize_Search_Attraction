#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <vector>
//#include "tetrahedron.hpp"
#include <set>
#include <cstdio>

namespace tetrasearch{

    class tetrahedron;

    //bool comparatorSet(point a, point b){ return a.samePoints(b); }

    class point{

        public :

            point(){};
            /*point( float _x, float _y, float _z, std::vector<tetrahedron> _tetra ) 
            : x( _x ), y( _y ), z( _z ), tetra( _tetra ) {};*/

            point( int _id, float _x, float _y, float _z) 
            : id(_id), x( _x ), y( _y ), z( _z ) {};

            ~point(){};

            static bool comparatorSet(point a, point b){ return a.samePoints(&b); }

            std::vector<float> getCoord(); 
            int getId();
            std::vector<tetrahedron*> getTetrahedron();
            std::vector<point* > getPointAttract();
            std::vector<point* > getNeighbours();

            //===========test set================
            //std::set<point, decltype(comparatorSet)> getNeighbours();

            inline void printCoord(){ printf("(x: %lf, y: %lf, z: %lf\n)", x, y, z); };

            bool isAttract ( point* p, float attract_distance );

            void addPoint ( point* p );

            void searchAdjPoint ();

            void computeNeighbours();

            bool samePoints ( point* p );

            void computePointAttract( float r );

            void addTetrahedron ( tetrahedron* t);

        private :

            int id;
            float x;
            float y;
            float z;
        
            std::vector<tetrahedron*> tetra;
            std::vector<point* > point_attract;
            std::vector<point* > neighbours;

            //===========test set================
            //std::set<point, decltype(comparatorSet)> neighbours;

    };
}

#endif