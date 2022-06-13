#include "point.hpp"
#include "tetrahedron.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <cmath>

using namespace std;

namespace tetrasearch {

    vector<point*> points;
    vector<tetrahedron*> tetras;

     point* findPoint( int id )
    {
        return points[id];
    }

    tetrahedron* findTetra ( int id )
    {
        return tetras[id];
    }

    void printPointsTetra( tetrahedron* t )
    {
        point* p1;
        for (int i = 0; i < (int)t->getPoints().size(); i++)
        {
            p1 = findPoint(t->getPoints()[i]);
            printf ("id: %i, ",  p1->getId() );
            printf ( "x: %1.3f, ", p1->getCoord()[0] );
            printf ( "y: %1.3f, ", p1->getCoord()[1] );
            printf ( "z: %1.3f \n", p1->getCoord()[2] );
        }
    }

    void printNeighbours(point* p)
    {
        printf( "\n points voisins (nb voisins: %i): \n", (int)p->getNeighbours().size());
        point* p1;
        for (int i = 0; i < (int)p->getNeighbours().size(); i++)
        {
            p1 = findPoint(p->getNeighbours()[i]);
            printf ("id: %i, ",  p1->getId() );
            printf ( "x: %1.3f, ", p1->getCoord()[0] );
            printf ( "y: %1.3f, ", p1->getCoord()[1] );
            printf ( "z: %1.3f \n", p1->getCoord()[2] );
        }
    }

    void printPointAttract(point* p)
    {
        printf ( "\n points attracts: \n");

        if( (int)p->getPointAttract().size() == 0 )
            printf("Pas de points d'attraction\n");
        else
        {
            std::vector<float> p_coord; 
            p_coord = p->getCoord();

            float xp = p_coord[0] ;
            float yp = p_coord[1] ;
            float zp = p_coord[2] ;
            float x, y ,z;
            point* p1;

            for (int i = 0; i < (int)p->getPointAttract().size(); i++)
            {
                p1 = findPoint( p->getPointAttract()[i] );
                x = xp - p1->getCoord()[0];
                y = yp - p1->getCoord()[1];
                z = zp - p1->getCoord()[2];


                printf ( "id: %i, ",  p1->getId() );
                printf ( "x: %1.3f, ", p1->getCoord()[0] );
                printf ( "y: %1.3f, ", p1->getCoord()[1] );
                printf ( "z: %1.3f ", p1->getCoord()[2] );
                printf ( "distance : %f\n", sqrt( x * x + y * y + z * z));
            }
        }
    }

    



    //================Reading files=================
    //=====================Nodes=======================
    void readNodes( string fileName )
    {
        ifstream fileNode( fileName, ios::in);

        if ( fileNode )
        {
            printf( "(lecture du fichier node...) Youpi ça fonctionne ! :D \n");
        
            string line;
        
            getline( fileNode, line); // skip the first line 
            float cx, cy, cz;
            int id;

            while ( getline( fileNode, line) )
            {
                if (line[0] != '#')
                {
                    std::istringstream iss(line);
                    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                    std::istream_iterator<std::string>());

                    id = stoi( results[0] );
                    cx = stof( results[1] );
                    cy = stof( results[2] );
                    cz = stof( results[3] );

                    points.push_back( new point(id, cx, cy, cz));
                }
            }
            fileNode.close();
        }
        else printf( "Ouverture du fichier .node impossible \n");

    }

    //======================Tetrahedrons==========================
    //prerequisite: have to be called after readNodes.
    void readTetras( string fileName )
    {
        ifstream fileTetra( fileName, ios::in);
        tetrahedron* t ;

        if ( fileTetra )
        {
            printf( "(lecture du fichier ele...) Youpi ça fonctionne ! :D \n");
            string line;
            getline( fileTetra, line); // skip the first line 
            int p1, p2, p3, p4, id;

            while ( getline( fileTetra, line) )
            {
                if (line[0] != '#')
                {
                    std::istringstream iss(line);
                    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                    std::istream_iterator<std::string>());       

                    id = stoi( results[0] );
                    p1 = stoi( results[1] );
                    p2 = stoi( results[2] );
                    p3 = stoi( results[3] );
                    p4 = stoi( results[4] );

                    t = new tetrahedron(id, p1, p2, p3, p4 );
                    tetras.push_back( t );

                    points[p1]->addTetrahedron( t );
                    points[p2]->addTetrahedron( t );
                    points[p3]->addTetrahedron( t );
                    points[p4]->addTetrahedron( t );

                    
                }
            }
            fileTetra.close();
        }
        else printf( "Ouverture du fichier .node impossible \n");
    }

   

    int main(int argc, char const *argv[])
    {
        string fileNodes = "data/tetgen-tmpfile.1.node";
        string fileTetra = "data/tetgen-tmpfile.1.ele";
        readNodes( fileNodes );
        readTetras( fileTetra );
        cout << "nombre de points: " << points.size() << endl;
        cout << "nombre de tetraèdres: " << tetras.size() << endl;

        for ( int i = 0; i < (int)points.size(); i++)
        {
            points[i]->computeNeighbours(tetras);
        }

        /*for ( int i = 0; i < (int)points.size(); i++)
        {
            points[i]->computePointAttract( 3.f, points );
        }*/

        printf( "\n===========VOISINS===========\n");
        printNeighbours(points[0]);

       /* printf( "\n===========ATTRACT POINTS===========\n");
        points[0]->computePointAttract( 5.f, points );
        printPointAttract(points[0]);*/

        printf( "\n===========ATTRACT POINTS V2===========\n");
        points[0]->computePointAttract( 5.f, points );
        printPointAttract(points[0]);
        

        /*printf( "\n===========ATTRACT POINTS VERSION SET===========\n");
        points[0]->computePointAttractVSet(20.f);
        printPointAttract(points[0]);*/
        return 0;
    }

 
} // end namespace tetrasearch



int main(int argc, char const *argv[])
{
    return tetrasearch::main(argc, argv);
}