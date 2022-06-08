#ifndef _TETRA_HPP_
#define _TETRA_HPP_

#include <vector>
#include "point.hpp"

namespace tetrasearch{

    class tetrahedron
    {
        public :
            tetrahedron( std::vector<point> _points ) : points(_points) {};
            ~tetrahedron(){};

            std::vector<point> getPoints();
            
        private :

            std::vector<point> points;
        

    };
}



#endif