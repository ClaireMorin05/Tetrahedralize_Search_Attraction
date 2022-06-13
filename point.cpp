#include <cmath>
#include "point.hpp"
#include "tetrahedron.hpp"
#include <iostream>
#include <cstdio>
namespace tetrasearch{

    std::vector<float> point::getCoord() const
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
        this->tetra.push_back(t->getId());
    }

    std::vector<int> point::getTetrahedron()
    {
        return this->tetra;
    }

    std::vector<int> point::getPointAttract()
    {
        return this->point_attract;
    }

    std::vector<int> point::getNeighbours()
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
        point_attract.push_back(p->getId());
    }

    bool point::samePoints( point* p )
    {
        std::vector<float> pCoords = p->getCoord();

        if ( pCoords[0] != this->x || pCoords[1] != this->y || pCoords[2] != this->z )
            return false;
        
        else
            return true;
    }

    void point::computeNeighbours( std::vector<tetrahedron*> tetraList)
    {
        bool belongs = false;

        tetrahedron* tetrahedron;

        for ( int i = 0; i < (int)tetra.size(); i++)
        {
            tetrahedron = findTetra(tetraList, tetra[i]);

            for ( int j = 0; j < 4; j++)
            {
                belongs = false;

                if ( this->id != tetrahedron->getPoints()[j] )
                {
                    for ( int k = 0; k < (int)neighbours.size(); k++ )
                    {
                        if(this->neighbours[k] == tetrahedron->getPoints()[j])
                        {
                            belongs = true;
                            break;
                        }
                    }

                    if ( !belongs )
                        neighbours.push_back(tetrahedron->getPoints()[j]);
                }
            } 
        }
        
    }


    point* point::findPoint ( std::vector<point*> pointList, int id )
    {
        return pointList[id];
    }

    tetrahedron* point::findTetra ( std::vector<tetrahedron*> tetraList, int id )
    {
        return tetraList[id];
    }

    void point::computePointAttract( float r, std::vector<point*> pointList )
    {
        std::vector<int > points = this->neighbours;
        std::vector<int > traveled_points = this->neighbours;
        bool belongs = false;
        point* p;

        while ( points.size() != 0)
        {

            p = findPoint(pointList, points[0]);
            if ( this->isAttract( p, r ) )
            {
                this->point_attract.push_back(points[0]);
                for ( int i = 0; i < (int)p->getNeighbours().size(); i++ )
                {
                    belongs = false;

                    for ( int j = 0; j < (int)traveled_points.size(); j++ ) 
                    {
                        
                        if ( p->getNeighbours()[i] == traveled_points[j] || this->id == p->getNeighbours()[i] )
                        {
                            belongs = true;
                            break;
                        }
                            
                    }

                    if ( !belongs )
                    {
                        traveled_points.push_back(p->getNeighbours()[i]);
                        points.push_back(p->getNeighbours()[i]);
                    }

                }
            }

            points.erase(points.begin());
        }

    }

    /*void point::computePointAttractV2( float r, std::vector<point*> pointList )
    {
        std::vector<int > points = this->neighbours;
        std::vector<int > traveled_points = this->neighbours;

        int tailleActu;

        int nbPointsAttrac;

        bool belongs = false;
        point* p;

        while ( points.size() != 0)
        {
            nbPointsAttrac = 0;
            tailleActu = (int)points.size();

            for ( int i = 0; i<tailleActu; i++ )
            {
                if ( this->isAttract( p, r ) )
                {
                    this->point_attract.push_back(points[0]);
                    nbPointsAttrac += 1;
                }
            }

            if ( nbPointsAttrac == tailleActu )
            {

            }

            else
            {
                points.clear();
            }


            p = findPoint(pointList, points[0]);
            if ( this->isAttract( p, r ) )
            {
                this->point_attract.push_back(points[0]);
                for ( int i = 0; i < (int)p->getNeighbours().size(); i++ )
                {
                    belongs = false;

                    for ( int j = 0; j < (int)traveled_points.size(); j++ ) 
                    {
                        
                        if ( p->getNeighbours()[i] == traveled_points[j] || this->id == p->getNeighbours()[i] )
                        {
                            belongs = true;
                            break;
                        }
                            
                    }

                    if ( !belongs )
                    {
                        traveled_points.push_back(p->getNeighbours()[i]);
                        points.push_back(p->getNeighbours()[i]);
                    }

                }
            }

            points.erase(points.begin());
        }

    }*/


    
    /*void point::computePointAttractVSet( float r )
    {
        std::set<point*, point::compare> points;
        std::set<point*, point::compare > traveled_points;
        std::cout<<"taille voisin : "<<this->neighbours.size()<<std::endl;

        for ( int i = 0; i < (int)this->neighbours.size(); i++ )
        {
            std::cout<< neighbours[i]->getId()<<std::endl;
            points.insert(this->neighbours[i]);
            traveled_points.insert(this->neighbours[i]);
        }


        while ( points.size() != 0)
        {
            std::cout<< "taille points : " << points.size()<<std::endl;
            std::cout<< "taille traveled_points : " << traveled_points.size()<<std::endl;

            if ( this->isAttract( *points.begin(), r ) )
            {
                std::cout<<"dans le if"<<std::endl;
                
                this->point_attract.push_back(*points.begin());
                for ( int i = 0; i < (int)(*points.begin())->getNeighbours().size(); i++ )
                {
                   
                    
                    traveled_points.insert((*points.begin())->getNeighbours()[i]);
                    points.insert((*points.begin())->getNeighbours()[i]);



                }
            }

            points.erase(points.begin());
        }

    }*/


}