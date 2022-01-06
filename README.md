# jtj4-johndd2-reedpg2-cvauk2
Repo for jtj4-johndd2-reedpg2-cvauk2

## Important Locations

the majority of code is in parksGraph.h/parksGraph.cpp. This is where we have functions to read in data, build our adjacency matrix, and then subsequently create a Min Spanning Tree / Solution to our Travelling Salesmen Problem.

The data we are reading comes from "data.txt", although the parksGraph constructor will take any file name to read from. for example parksGraph j("data.txt", num) creates a parksGraph object of size num that stores all the parks in data.txt

All tests can be found in tests.cpp (found in the tests folder).

All of our user interface is ran through main.cpp and after the user input is taken, we create a parksGraph object and solve/display our final output to the console through main as well. 

## Formatting Data
Data should be given as a txt file where each line follows this format:  
Park Name , State , Latitude , Longitude
##### For example:
Capitol Reef National Park, Utah , 38.08 , -111
## Running the project
1). Enter "make" into the terminal\
2). Enter "./parksGraph" into terminal\
3). Answer terminal prompts (invalid responses may crash or break project)\
4). DFS traversal is displayed to terminal\
5). Minimum spanning tree (formated as edges/weights) is displayed to terminal\
6). Shortest path from start to every park and back is displayed in terminal

## Running tests
1). Enter "make test" into the terminal\
2). Enter "./test" into the terminal\
3). All test cases will be ran and score will be displayed to terminal

  *Note ( All test cases can be found in tests.cpp in the tests folder)*
## Tests overview
### Testing the TSP solver
#### Small Graph
The first TSP case is hand solved for the first 5 parks in our dataset, We then compare our hand-computed solution to the solution of our algorith to see if it passes
#### Medium Graph
This solution was computed by using easycalculation.com's TSP solver and entering the relevant adjacency matrix. We compare our solution to theirs to see if our algorithm passes this test. 
### Testing Prim's Algorithm
#### Tests small dataset
The first Prim's Algorithim test case compares the Minimum spanning tree with a hand solved solution for the first 5 parks. We then compare our hand-computed solution to the solution of out algorithim to see if it passes
#### Tests medium dataset
The second Prim's Algorithim test case compares the Minimum spanning tree with a hand solved solution for the first ten parks. We then compare our hand-computed solution to the solution of our algorithim to see if it passes.
#### Tests random
The final Prim's Algorithim test case uses randomly inmputed parks that is not linear and then compares the solution from the algorithim to the hand-computed solution to see if it passes. 
### Testing DFS Algorithm
#### Tests that DFS searches by depth
The first test of our DFS traversal ensures that we search through the traversal vector in order, starting from the user provided index i > i+1 > ... > 0 > ... > to i-1.
#### Tests that DFS stays in bounds
Confirms that the user inputting an index that is out of range of the traversal vector still provides a traversal from index % traversal size and then performs the traversal correctly.
