#ifndef _TETRA_HPP_
#define _TETRA_HPP_

#include <vector>
#include "point.hpp"

namespace tetrasearch{

    class tetrahedron
    {
        public :
            tetrahedron( int _id, int p1, int p2, int p3, int p4 ) : id(_id)
            { 
                
                points.push_back(p1);
                points.push_back(p2);
                points.push_back(p3);
                points.push_back(p4);
                
            };
            ~tetrahedron(){};

            std::vector<int> getPoints();
            int getId();
            
        private :

            int id;
            std::vector<int> points;
        

    };
}



#endif