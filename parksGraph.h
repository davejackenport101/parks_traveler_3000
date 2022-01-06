/**
 * file @parksGraph.h
 * This is the header file for our parksGraph Class
 */
 #pragma once
 
 #include <string>
 #include <iostream>
 #include <fstream>
 #include <vector>
 #include <stack>
 
 class parksGraph {
    public:

    //A node structure to represent each park in our graph
    class Park {
        public:

            //Default constructor for a Park node
            Park() {  /* nothing  */  }
            
            //setter functions for each Park since the variables are private
            void set_name (char c) {  park_name.push_back(c);  }
            void set_state (char c) {  state.push_back(c);  }
            void set_Long(float f) {  Long = f;  }
            void set_Lat(float f) {  Lat = f;  }

            //getter functions, notice these convert the park_name and state from vector to string
            std::string get_name() {
                std::string ret;
                for (unsigned i = 0; i < park_name.size(); i++) ret.push_back(park_name[i]);
                return ret;
            }
            std::string get_state() {
                std::string ret;
                for (unsigned i = 0; i < state.size(); i++) ret.push_back(state[i]);
                return ret;
            }

            float get_Long() {  return Long;  }
            float get_Lat() {  return Lat;  }

            //helper function that resets the park object, helpful for the readData() function
            void reset() {
               park_name.clear();
               state.clear();
               Long = 0.0;
               Lat = 0.0;
            }

        private:
            std::vector<char> park_name;
            std::vector<char> state;
            float Long;
            float Lat;
    };

    //default Constructor for a parksGraph object
    parksGraph() {  /*  nothing  */  }

    //Constructor for a parksGraph object
    parksGraph(std::string data, unsigned num_parks);

    void print_all_parks();
    void print_dfs();
    void print_chosen_parks();

    unsigned numParks() 
    {
        return num_parks;
    }

    double harversineFormula(double lat1, double lat2, double long1, double long2);

    // getter and setter functions for our parksGraph object
    void set_all_parks() { chosen_parks = all_parks; }
    std::string get_all_park_at_index(unsigned idx) { return all_parks[idx%all_parks.size()].get_name(); }
    std::string get_traversal_at_index(unsigned idx) { return traversal[idx%traversal.size()].get_name(); }

    //takes an index and adds that park from all parks into chosen parks
    bool add_chosen_park(int i);

    //functions to build/display adj matrix after user has chosen parks
    void build_adjacency_matrix();
    void print_adjacency_matrix();
    std::vector<int> get_solution() {  return solution;  }
    
    // functions to build and print out MST
    void printMST(std::vector<float> parent,std::vector<std::vector<float>> adj);
    float minKey(std::vector<float> parent, std::vector<bool> msetSet);
    void prims_algorithim();
    // this vector stores the MST Not necessary for implementation but used to test if it is the correct order in test cases.
    std::vector<float> MST;
    //Functions for TSP solver
    int least( int c );
    void mincost( int park );
    void tsp();
    void dfs(unsigned i);

    void print_tsp();

private:
    //helper function to deal with the whole data.txt -> all_parks mess
    void readData(std::string data);

    std::vector<Park> all_parks;
    std::vector<Park> chosen_parks;
    std::vector<Park> traversal;
    std::vector<bool> visited;

    std::vector<std::vector<float>> adjacency_matrix;
    std::vector<std::vector<Park>> adjacency_matrix_park;
    
    unsigned num_parks;
    unsigned spots_left;
    unsigned idx_count;

    //completed and cost are used in tsp() to fill solution with the shortest path by index
    std::vector<int> completed;
    std::vector<int> solution;
    float cost;

    void printstatment();


};
