#include "point.hpp"
#include "tetrahedron.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>

using namespace std;

namespace tetrasearch {

    vector<point*> points;
    vector<tetrahedron*> tetras;

    void printPointsTetra( tetrahedron* t )
    {
        for (int i = 0; i < (int)t->getPoints().size(); i++)
        {
            t->getPoints()[i]->getCoord();
            printf ("id: %i, ",  t->getPoints()[i]->getId() );
            printf ( "x: %1.3f, ", t->getPoints()[i]->getCoord()[0] );
            printf ( "y: %1.3f, ", t->getPoints()[i]->getCoord()[1] );
            printf ( "z: %1.3f \n", t->getPoints()[i]->getCoord()[2] );
        }
    }

    void printNeighbours(point* p)
    {
        printf( "\n points voisins (nb voisins: %i): \n", (int)p->getNeighbours().size());
        for (int i = 0; i < (int)p->getNeighbours().size(); i++)
        {
            printf ("id: %i, ",  p->getNeighbours()[i]->getId() );
            printf ( "x: %1.3f, ", p->getNeighbours()[i]->getCoord()[0] );
            printf ( "y: %1.3f, ", p->getNeighbours()[i]->getCoord()[1] );
            printf ( "z: %1.3f \n", p->getNeighbours()[i]->getCoord()[2] );
        }
    }

    void printPointAttract(point* p)
    {
        printf ( "\n points attracts: \n");

        if( (int)p->getPointAttract().size() == 0 )
            printf("Pas de points d'attraction\n");
        else
        {
            for (int i = 0; i < (int)p->getPointAttract().size(); i++)
            {
                printf ( "id: %i, ",  p->getPointAttract()[i]->getId() );
                printf ( "x: %1.3f, ", p->getPointAttract()[i]->getCoord()[0] );
                printf ( "y: %1.3f, ", p->getPointAttract()[i]->getCoord()[1] );
                printf ( "z: %1.3f \n", p->getPointAttract()[i]->getCoord()[2] );
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
            int p1, p2, p3, p4;

            while ( getline( fileTetra, line) )
            {
                if (line[0] != '#')
                {
                    std::istringstream iss(line);
                    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                    std::istream_iterator<std::string>());       

                    p1 = stoi( results[1] );
                    p2 = stoi( results[2] );
                    p3 = stoi( results[3] );
                    p4 = stoi( results[4] );

                    t = new tetrahedron(points[p1], points[p2], points[p3], points[p4] );
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
            points[i]->computeNeighbours();
        }

        for ( int i = 0; i < (int)points.size(); i++)
        {
            points[i]->computePointAttract(20.f);
        }

        printf( "\n===========VOISINS===========\n");
        printNeighbours(points[0]);

        printf( "\n===========ATTRACT POINTS===========\n");
        printPointAttract(points[0]);
        return 0;
    }
} // end namespace tetrasearch



int main(int argc, char const *argv[])
{
    return tetrasearch::main(argc, argv);
}