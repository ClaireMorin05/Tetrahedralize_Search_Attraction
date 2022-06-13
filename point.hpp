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

        struct compare
        {
            bool operator()(const point* pa, const point* pb)const
            {
                std::vector<float> a = pa->getCoord();
                std::vector<float> b = pb->getCoord();
                if( a[0] != b[0] || a[1] != b[1] || a[2] != b[2] )
                    return true;
                else
                    return false;
                /*return  a[0] != b[0] ? a[0] < b[0] : 
                            (a[1] != b[1] ? a[1] < b[1] : 
                                (a[2] != b[2] ? a[2] < b[2] : true ) ); */
            }
        };

        public :

            point(){};
            /*point( float _x, float _y, float _z, std::vector<tetrahedron> _tetra ) 
            : x( _x ), y( _y ), z( _z ), tetra( _tetra ) {};*/

            point( int _id, float _x, float _y, float _z) 
            : id(_id), x( _x ), y( _y ), z( _z ) {};

            ~point(){};

            //static bool comparatorSet(point a, point b){ return a.samePoints(&b); }

            std::vector<float> getCoord() const; 
            int getId();
            std::vector<int> getTetrahedron();
            std::vector<int> getPointAttract();
            std::vector<int> getNeighbours();

            
            inline void printCoord(){ printf("(x: %lf, y: %lf, z: %lf\n)", x, y, z); };

            bool isAttract ( point* p, float attract_distance );

            void addPoint ( point* p );

            void searchAdjPoint ();

            void computeNeighbours( std::vector<tetrahedron*> tetraList );

            bool samePoints ( point* p );

            void computePointAttract( float r, std::vector<point*> pointList );

            void addTetrahedron ( tetrahedron* t);

            point* findPoint ( std::vector<point*> pointList, int id );

            tetrahedron* findTetra ( std::vector<tetrahedron*> pointList, int id );

            //============Point Attract V2============

            //void computePointAttractV2( float r, std::vector<point*> pointList );

            //=======Version avec set===========

            void computePointAttractVSet( float r );

        private :

            int id;
            float x;
            float y;
            float z;
        
            std::vector<int> tetra;
            std::vector<int> point_attract;
            std::vector<int> neighbours;

            //===========test set================
            //std::set<point, decltype(comparatorSet)> neighbours;

    };
}

#endif