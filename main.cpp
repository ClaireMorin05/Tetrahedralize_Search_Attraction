#include "point.hpp"
#include "tetrahedron.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <cmath>
#include <chrono>

using namespace std;

namespace tetrasearch {

    vector<Point*> points;
    vector<Tetrahedron*> tetras;
    vector<int> traveled_points;

    std::chrono::time_point<std::chrono::system_clock> startV1, endV1;
    std::chrono::time_point<std::chrono::system_clock> startV2, endV2;
    std::chrono::time_point<std::chrono::system_clock> startV3, endV3;
    std::chrono::time_point<std::chrono::system_clock> startVoisinV1, endVoisinV1;
    std::chrono::time_point<std::chrono::system_clock> startVoisinV2, endVoisinV2;

    Point* findPoint( int id )
    {
        return points[id];
    }

    Tetrahedron* findTetra ( int id )
    {
        return tetras[id];
    }

    void printPointsTetra( Tetrahedron* t )
    {
        Point* p1;
        for (int i = 0; i < (int)t->getPoints().size(); i++)
        {
            p1 = findPoint(t->getPoints()[i]);
            printf ("id: %i, ",  p1->getId() );
            printf ( "x: %1.3f, ", p1->getCoord()[0] );
            printf ( "y: %1.3f, ", p1->getCoord()[1] );
            printf ( "z: %1.3f \n", p1->getCoord()[2] );
        }
    }

    void printNeighbours(Point* p)
    {
        printf( "\n points voisins (nb voisins: %i): \n", (int)p->getNeighbours().size());
        Point* p1;
        for (int i = 0; i < (int)p->getNeighbours().size(); i++)
        {
            p1 = findPoint(p->getNeighbours()[i]);
            printf ("id: %i, ",  p1->getId() );
            printf ( "x: %1.3f, ", p1->getCoord()[0] );
            printf ( "y: %1.3f, ", p1->getCoord()[1] );
            printf ( "z: %1.3f \n", p1->getCoord()[2] );
        }
    }

    void printPointAttract(Point* p)
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
            Point* p1;

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

                    points.push_back( new Point(id, cx, cy, cz));
                    traveled_points.push_back(-1);
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
        Tetrahedron* t ;

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

                    t = new Tetrahedron(id, p1, p2, p3, p4 );
                    tetras.push_back( t );

                    points[p1]->addTetrahedron( t );
                    points[p2]->addTetrahedron( t );
                    points[p3]->addTetrahedron( t );
                    points[p4]->addTetrahedron( t );
                    
                }
            }
            fileTetra.close();
        }
        else printf( "Ouverture du fichier .ele impossible \n");
    }

   

    int main(int argc, char const *argv[])
    {
        string fileNodes = "data/tetgen1000points.1.node";
        string fileTetra = "data/tetgen1000points.1.ele";
        readNodes( fileNodes );
        readTetras( fileTetra );
        cout << "nombre de points: " << points.size() << endl;
        cout << "nombre de tetraèdres: " << tetras.size() << endl;

        std::cout << " Calcul des voisins V1 "<<std::endl;
        startVoisinV1 = std::chrono::system_clock::now();
        for ( int i = 0; i < (int)points.size(); i++)
        {
            points[i]->computeNeighbours(tetras);
        }
        endVoisinV1 = std::chrono::system_clock::now();
        std::chrono::duration<double> voisinV1 = endVoisinV1 - startVoisinV1;
        std::cout<< " Voisin version 1 : " << voisinV1.count() <<std::endl;


        std::cout << " Calcul des voisins V2 "<<std::endl;
        startVoisinV2 = std::chrono::system_clock::now();
        for ( int i = 0; i < (int)points.size(); i++)
        {
            points[i]->computeNeighboursV2(tetras);
        }
        endVoisinV2 = std::chrono::system_clock::now();
        std::chrono::duration<double> voisinV2 = endVoisinV2 - startVoisinV2;
        std::cout<< " Voisin version 2 : " << voisinV2.count() <<std::endl;


        std::cout << " Calcul des points attracts"<<std::endl;
        startV1 = std::chrono::system_clock::now();
        for ( int i = 0; i < (int)points.size(); i++)
        {
            points[i]->computePointAttract( 3.f, points );
        }
        endV1 = std::chrono::system_clock::now();
        std::chrono::duration<double> tempsV1 = endV1 - startV1;
        std::cout<< " Temps version 1 : " << tempsV1.count() <<std::endl;


        startV2 = std::chrono::system_clock::now();
        for ( int i = 0; i < (int)points.size(); i++)
        {
            points[i]->computePointAttractV2( 3.f, points );
        }
        endV2 = std::chrono::system_clock::now();
        std::chrono::duration<double> tempsV2 = endV2 - startV2;

        std::cout<< " Temps version 2 : " << tempsV2.count() <<std::endl;


        startV3 = std::chrono::system_clock::now();
        for ( int i = 0; i < (int)points.size(); i++)
        {
            points[i]->computePointAttractV3( 3.f, points, traveled_points );
        }
        endV3 = std::chrono::system_clock::now();
        std::chrono::duration<double> tempsV3 = endV3 - startV3;

        std::cout<< " Temps version 3 : " << tempsV3.count() <<std::endl;

        printf( "\n===========VOISINS===========\n");
        printNeighbours(points[50]);

       /* printf( "\n===========ATTRACT POINTS===========\n");
        points[0]->computePointAttract( 5.f, points );
        printPointAttract(points[0]);*/

        /*printf( "\n===========ATTRACT POINTS V2===========\n");
        points[0]->computePointAttractV2( 20.f, points );
        printPointAttract(points[0]);*/

        /*printf( "\n===========ATTRACT POINTS V3===========\n");
        points[0]->computePointAttractV3( 5.f, points, traveled_points );
        printPointAttract(points[0]);*/
        

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