#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <vector>
//#include "Tetrahedron.hpp"
#include <set>
#include <cstdio>

namespace tetrasearch{

    class Tetrahedron;

    //bool comparatorSet(point a, point b){ return a.samePoints(b); }

    class Point{

        struct compare
        {
            bool operator()(const Point* pa, const Point* pb)const
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

            Point(){};
            /*Point( float _x, float _y, float _z, std::vector<tetrahedron> _tetra ) 
            : x( _x ), y( _y ), z( _z ), tetra( _tetra ) {};*/

            Point( int _id, float _x, float _y, float _z) 
            : id(_id), x( _x ), y( _y ), z( _z ) {};

            ~Point(){};

            //static bool comparatorSet(Point a, Point b){ return a.samePoints(&b); }

            std::vector<float> getCoord() const; 
            int getId();
            std::vector<int> getTetrahedron();
            std::vector<int> getPointAttract();
            std::vector<int> getNeighbours();

            
            inline void printCoord(){ printf("(x: %lf, y: %lf, z: %lf\n)", x, y, z); };

            bool isAttract ( Point* p, float attract_distance );

            void addPoint ( Point* p );

            void searchAdjPoint ();

            void computeNeighbours( std::vector<Tetrahedron*> tetraList );

            //============Voisins V2============

            void computeNeighboursV2( std::vector<Tetrahedron*> tetraList );

            bool samePoints ( Point* p );

            void addTetrahedron ( Tetrahedron* t);

            Point* findPoint ( std::vector<Point*> PointList, int id );

            Tetrahedron* findTetra ( std::vector<Tetrahedron*> PointList, int id );


            void computePointAttract( float r, std::vector<Point*> PointList );

            //============Point Attract V2============

            void computePointAttractV2( float r, std::vector<Point*> PointList );

            //============Point Attract V3============

            void computePointAttractV3( float r, std::vector<Point*> PointList, std::vector<int> traveled_point );


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