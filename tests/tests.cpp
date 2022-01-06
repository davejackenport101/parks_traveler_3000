#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../parksGraph.h"

#include <vector>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
/   TEST CASES FOR TSP SOLVER
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////



TEST_CASE("Checking TSP solution for small journey", "[weight=1]" ) {


    //Hand computed all paths for parks 0-4, Shortest path is 0-->2-->1-->3-->4-->0
    std::vector<int> computed_solution { 0 , 2 , 1 , 3, 4 , 0};
  
    parksGraph j("data.txt", 5);

    j.add_chosen_park(0);
    j.add_chosen_park(1);
    j.add_chosen_park(2);
    j.add_chosen_park(3);
    j.add_chosen_park(4);

    j.build_adjacency_matrix();
    j.tsp();

    REQUIRE( j.get_solution() == computed_solution );
}


TEST_CASE("Checking TSP solution for larger journey", "[weight=1]" ) {

    //Computed solution using by plugging adj matrix into easy calculation.com TSP solver
    //https://www.easycalculation.com/operations-research/traveling-salesman-problem.php

    std::vector<int> computed_solution { 0 , 5, 4 , 6, 3, 1 , 2 , 0 };
  
    parksGraph j("data.txt", 7);

    j.add_chosen_park(1);
    j.add_chosen_park(3);
    j.add_chosen_park(5);
    j.add_chosen_park(7);
    j.add_chosen_park(9);
    j.add_chosen_park(10);
    j.add_chosen_park(13);

    j.build_adjacency_matrix();
    j.tsp();

    REQUIRE( j.get_solution() == computed_solution );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
/   TEST CASES FOR Prim's Algorithm
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


TEST_CASE("Primm's Algorithim does correct MST for Parks 1-5","[weight=1]") {
  parksGraph j("data.txt",5);
 
  j.add_chosen_park(1);
  j.add_chosen_park(2);
  j.add_chosen_park(3);
  j.add_chosen_park(4);
  j.add_chosen_park(5);
  j.build_adjacency_matrix();
  j.prims_algorithim();
  REQUIRE(j.MST[0] == -1);
  REQUIRE(j.MST[1] == 0);
  REQUIRE(j.MST[2] == 1);
  REQUIRE(j.MST[3] == 0);
  REQUIRE(j.MST[4] == 3);
  
  
}

TEST_CASE("Prim's Algorithim does correct MST for Parks 1-10", "[weight=1]") {
  parksGraph j("data.txt",10);
  j.add_chosen_park(1);
  j.add_chosen_park(2);
  j.add_chosen_park(3);
  j.add_chosen_park(4);
  j.add_chosen_park(5);
  j.add_chosen_park(6);
  j.add_chosen_park(7);
  j.add_chosen_park(8);
  j.add_chosen_park(9);
  j.add_chosen_park(10);
  j.build_adjacency_matrix();
  j.prims_algorithim();
  REQUIRE(j.MST[0] == -1);
  REQUIRE(j.MST[1] == 9);
  REQUIRE(j.MST[2] == 6);
  REQUIRE(j.MST[3] == 7);
  REQUIRE(j.MST[4] == 5);
  REQUIRE(j.MST[5] == 3);
  REQUIRE(j.MST[6] == 1);
  REQUIRE(j.MST[7] == 0);
  REQUIRE(j.MST[8] == 1);
  REQUIRE(j.MST[9] == 7);
}

TEST_CASE("Prim's algorthim does correct MST for parks not inserted linearlily", "[weight = 1]") {
  parksGraph j("data.txt",9);
  j.add_chosen_park(14);
  j.add_chosen_park(27);
  j.add_chosen_park(43);
  j.add_chosen_park(4);
  j.add_chosen_park(18);
  j.add_chosen_park(31);
  j.add_chosen_park(55);
  j.add_chosen_park(67);
  j.add_chosen_park(1);
  j.build_adjacency_matrix();
  j.prims_algorithim();
  REQUIRE(j.MST[0] == -1);
  REQUIRE(j.MST[1] == 0);
  REQUIRE(j.MST[2] == 1);
  REQUIRE(j.MST[3] == 4);
  REQUIRE(j.MST[4] == 7);
  REQUIRE(j.MST[5] == 4);
  REQUIRE(j.MST[6] == 0);
  REQUIRE(j.MST[7] == 6);
  REQUIRE(j.MST[8] == 7);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
/   TEST CASES FOR DFS Algorithm
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("DFS properly searches the chosen_parks in order of depth") {
  parksGraph j("data.txt",5);
  j.add_chosen_park(1);
  j.add_chosen_park(2);
  j.add_chosen_park(3);
  j.add_chosen_park(4);
  j.add_chosen_park(5);
  j.build_adjacency_matrix();
  j.dfs(0);

  REQUIRE(j.get_traversal_at_index(0) == j.get_all_park_at_index(1));
  REQUIRE(j.get_traversal_at_index(1) == j.get_all_park_at_index(2));
  REQUIRE(j.get_traversal_at_index(2) == j.get_all_park_at_index(3));
  REQUIRE(j.get_traversal_at_index(3) == j.get_all_park_at_index(4));
  REQUIRE(j.get_traversal_at_index(4) == j.get_all_park_at_index(5));
}

TEST_CASE("DFS properly wraps if the user's input is larger than num_parks") {
  parksGraph j("data.txt",5);
  j.add_chosen_park(1);
  j.add_chosen_park(2);
  j.add_chosen_park(3);
  j.add_chosen_park(4);
  j.add_chosen_park(5);
  j.build_adjacency_matrix();
  j.dfs(7);

  REQUIRE(j.get_traversal_at_index(0) == j.get_all_park_at_index(3));
  REQUIRE(j.get_traversal_at_index(1) == j.get_all_park_at_index(4));
  REQUIRE(j.get_traversal_at_index(2) == j.get_all_park_at_index(5));
  REQUIRE(j.get_traversal_at_index(3) == j.get_all_park_at_index(1));
  REQUIRE(j.get_traversal_at_index(4) == j.get_all_park_at_index(2));
}