/**
 * file @parksGraph.cpp
 * Implementation of our parksGraph class
 */
#define _USE_MATH_DEFINES
#include "parksGraph.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <float.h>

/** 
 * =========================================================================================
 * Constructors and initialization functions for the parksGraph
 * =========================================================================================
 */ 

//Constructor for a parksGraph object
parksGraph::parksGraph(std::string data, unsigned num_parks) :
    num_parks(num_parks), idx_count(0)
{
    readData(data);
    spots_left = num_parks;
}

//helper function to take data from data.txt and put it into our all_parks vector
//ERROR: doesn't grab the last park for some reason, im not sure why
void parksGraph::readData(std::string data) {
    char c;
    Park p;
    std::ifstream inFile;
    std::string temp_Long; std::string temp_Lat;
    unsigned i = 0;

    inFile.open(data);
    if (!inFile) {
        std::cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    while (inFile.get(c)) {
        //if current character is a new line character, we are done gathering info about the current park
        if (c == 10) {
            //this check is necessary to skip a park if the data is written incorrectly
            if (i == 3) {
                p.set_Long(std::stof(temp_Long)); p.set_Lat(std::stof(temp_Lat));
                all_parks.push_back(p);
            }
            p.reset();
            i = 0; temp_Long.erase(); temp_Lat.erase();
        }
        //char c is a piece of data for a Park object
        else
        {
            //if current character is a comma, we want to increment which value within p we are setting
            if (c == 44) i++;
            //check i to see which part of Park p our data char c applies to
            else
            {
                if (i == 0) p.set_name(c);
                else if (i == 1) p.set_state(c);
                else if (i == 2) temp_Lat.push_back(c); 
                else if (i == 3) temp_Long.push_back(c);
            }
        }
    }
    inFile.close();
}

//prints all_parks in a user-friendly format
void parksGraph::print_all_parks() {
    for (unsigned i = 0; i < all_parks.size(); i++)
        std::cout << all_parks[i].get_name() + ", " + all_parks[i].get_state()  << "      ( # " << i << "  )" <<  std::endl;
}

//Adds user chosen parks to a chosen_parks vector
//returns true if chosen park was added succesfully, false if not
bool parksGraph::add_chosen_park(int i) {
    if( i < 0 || i > (int)all_parks.size()-1 ) {
         std::cout << "XXXXXXX      index does not exist      XXXXXXXX" << std::endl << std::endl;
         return false;
    }
    for( auto park : chosen_parks ) {
        if ( all_parks[i].get_name() == park.get_name() ) {
            std::cout << "XXXXXXX      You are already visiting that park. Try and be more original      XXXXXXXX" << std::endl << std::endl;
            return false;
        }
    }
    chosen_parks.push_back( all_parks[i] );
    spots_left--;
    return true;
}

void parksGraph::print_chosen_parks() {
    std::cout << "-------CHOSEN PARKS-------- " << std::endl;
    std::cout << "-----( " << spots_left << " Spots Left )-----" << std::endl;
    for (unsigned i = 0; i < chosen_parks.size(); i++) 
        std::cout << chosen_parks[i].get_name() + ", " + chosen_parks[i].get_state()  <<  std::endl;
}

/** 
 * =========================================================================================
 * Functions to implement and print a DFS traversal
 * =========================================================================================
 */ 

void parksGraph::dfs(unsigned i) 
{
    //wrap user input to be within num_parks in the case that their number is invalid (avoids a segfault)
    unsigned a = i%num_parks;
    
    for (unsigned j = a; j < (num_parks + a); j++) {
        if (!visited[a]) {
            traversal.push_back(chosen_parks[a]);
            visited[a] = true;
            dfs(j+1);
        }
    }
}

void parksGraph::print_dfs()
{
    std::cout << "Begin Park Traversal: " << std::endl;
    for (unsigned i = 0; i < traversal.size(); i++)
        std::cout << traversal[i].get_name() + ", " + traversal[i].get_state() << std::endl;
     std::cout << "End Park Traversal " << std::endl << std::endl;
}

/** 
 * =========================================================================================
 * Functions to build and print the adjacency matrix
 * =========================================================================================
 */ 

double parksGraph::harversineFormula(double lat1, double long1, double lat2, double long2) {
    double distance_latitude = (lat2 -lat1) * M_PI/ 180.0;
    double distance_longitude = (long2 - long1) * M_PI / 180.0;
    double latitude_1 = (lat1) * M_PI / 180.0;
    double latitude_2 = (lat2) * M_PI / 180.0;
    double a = pow(sin(distance_latitude / 2),2) + pow(sin(distance_longitude / 2),2) * cos(latitude_1) * cos(latitude_2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c / 100;
}

void parksGraph::build_adjacency_matrix() {
    std::vector<std::vector<float>> adj;

    for (unsigned i = 0; i < num_parks; i++) {
        std::vector<float> distances;

        for (unsigned j = 0; j < num_parks; j++ ) {

            float park1_lat = chosen_parks[i].get_Lat();
            float park1_long = chosen_parks[i].get_Long();

            float park2_lat = chosen_parks[j].get_Lat();
            float park2_long = chosen_parks[j].get_Long();

            float distance = harversineFormula( park1_lat , park1_long , park2_lat , park2_long );
            distances.push_back(distance);
        }
        adj.push_back(distances);
        visited.push_back(false);
    }

    adjacency_matrix = adj;
}

void parksGraph::print_adjacency_matrix() {

    std::cout << std::endl << std::endl <<  "------------------------------------------------------------------|   ADJACENCY  MATRIX   |-----------------------------------------------------" << std::endl;
    for( unsigned i = 0; i < num_parks; i++) {
        std::cout << chosen_parks[i].get_name() << "     ";
    }
    
    std::cout << std::endl;

    for(unsigned i = 0; i < num_parks; i++)
    {
        for (unsigned j = 0; j < adjacency_matrix[i].size(); j++)
        {
            std::cout << adjacency_matrix[i][j] << "                         ";
        } 
        std::cout << std::endl << std::endl;
    }
}

/** 
 * =========================================================================================
 * Functions to perform Prim's algorithm and to implement the MST
 * =========================================================================================
 */ 

void parksGraph::printMST(std::vector<float> parent,std::vector<std::vector<float>> adj) {
    std::cout<<"Edge \tWeight\n";
    for(size_t i = 1; i < num_parks; i++) {
        std::cout<<parent[i]<<" - "<<i<<" \t" <<adj[i][parent[i]] << " \n";
    }
}

float parksGraph::minKey(std::vector<float> parent, std::vector<bool> msetSet) {
    float min = FLT_MAX;
    float min_index;
    for(size_t i = 0; i < num_parks; i++) {
        if(msetSet[i] == false && parent[i] < min) {
            min = parent[i];
            min_index = i;
        }
    }
    return min_index;
}

void parksGraph::prims_algorithim() {
    std::vector<float> inMST;
    std::vector<float> key;
    std::vector<bool> msetSet;
    for(size_t i = 0; i < num_parks; i++) {
        key.push_back(FLT_MAX);
        msetSet.push_back(false);
        inMST.push_back(0);
    }
    key[0] = 0;
    inMST[0] = -1;
    for(size_t count = 0; count < num_parks - 1; count++ ) {
        float u = minKey(key,msetSet);
        msetSet[u] = true;
        for(size_t j = 0; j < num_parks; j++) {
            if(adjacency_matrix[u][j] != 0  && msetSet[j] == false && adjacency_matrix[u][j] < key[j]) {
                inMST[j] = u;
                key[j] = adjacency_matrix[u][j];
            }
        }
    }
    MST = inMST;
    std::cout<< "Minimum Spanning Tree"<<std::endl;
    printMST(inMST,adjacency_matrix);
}

/** 
 * =========================================================================================
 * Functions to solve the Traveling Salesman Problem
 * =========================================================================================
 */ 

//helper for mincost
int parksGraph::least( int c ) {
    unsigned i;
    int nc = 999;
    int min = 999, kmin;

    for (i = 0; i < num_parks; i++) {
        if ((adjacency_matrix[c][i] != 0) && (completed[i] == 0)) {
            if (adjacency_matrix[c][i] + adjacency_matrix[i][c] < min ) {
                min = adjacency_matrix[i][0] + adjacency_matrix[c][i];
                kmin = adjacency_matrix[c][i];
                nc = i;
            }
        }
    }
    if (min != 999) 
        cost += kmin;

    return nc;
}


// Helper function that fills vector named solution with the indexes of
// the shortest path ( aka the solution to TSP )
void parksGraph::mincost( int park ) {
    cost = 0;
    int npark;
    completed[park] = 1;
    solution.push_back(park);
    npark = least( park );

    if ( npark == 999 ) {
        npark = 0;
        solution.push_back(npark);
        cost += adjacency_matrix[park][npark];
        return;
    }
    mincost(npark);
}

void parksGraph::tsp() {
    //needed so that mincost() doesn't segfault
    completed.resize(num_parks);

    //fills solution vector
    mincost(0);
}

void parksGraph::print_tsp() {

    std::cout << "\n   Chosen Parks: \n";
    std::cout<<"Index \t Park Name\n";

    for( unsigned i = 0; i < chosen_parks.size(); i++ ) {
        std::cout << i << "\t " << chosen_parks[i].get_name() << "\n";
    }

    std::cout << "\nShortest Path (by index): ";

    for(unsigned i = 0; i < solution.size(); i++) {
        if ( i == solution.size() - 1 ) {
            std::cout << solution[i] << std::endl;
            break;
        }
        std::cout << solution[i] << "  ---->  ";
    }

    std::cout << "\n\nShortest Path (by park name): \n";

    for(unsigned i = 0; i < solution.size(); i++) {
        if ( i == solution.size() - 1 ) {
            std::cout << chosen_parks[  solution[i]  ].get_name() << std::endl;
            break;
        }

        std::cout << chosen_parks[  solution[i]  ].get_name() << "   ---->   ";
    }

}