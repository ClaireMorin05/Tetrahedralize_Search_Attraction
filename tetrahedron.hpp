#ifndef _TETRA_HPP_
#define _TETRA_HPP_

#include <vector>
#include "point.hpp"

namespace tetrasearch{

    class tetrahedron
    {
        public :
            tetrahedron( point* p1, point* p2, point* p3, point* p4 ) 
            { 
                points.push_back(p1);
                points.push_back(p2);
                points.push_back(p3);
                points.push_back(p4);
            };
            ~tetrahedron(){};

            std::vector<point*> getPoints();
            
        private :

            std::vector<point*> points;
        

    };
}



#endif