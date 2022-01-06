#include <iostream>
#include <stdlib.h>

#include "parksGraph.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {

  // User interface below gets needed information and builds graph/solution accordingly

  unsigned num_parks;
  vector<parksGraph::Park> parks;

  //begin prompting user to begin the program
  cout << "Welcome to State-Park-Travel-sim-7000" << endl;
  cout << "How many state parks do you want to see? (pick a number 5-94) (enter 94 to select all parks) " << endl; //add list of all state parks
  cin >> num_parks;
  while (num_parks < 5 ) {
    if (num_parks < 5) cout << "You have selected too few parks, where's your adventurous spirit??" << endl;
    else if (num_parks > 94) cout << "You have selected too many parks, you're legs wouldn't make it through the trip!" << endl;
    cout << "Please enter a number of parks between 5 and 95, inclusive." << endl;
    cin >> num_parks;
  }

  //now num_parks is properly specified, initialize our parksGraph object
  parksGraph j("data.txt", num_parks);

  // //DISPLAYS EVERY PARK
  j.print_all_parks();

  // // asks the user for an index and adds that park to chosen parks vector
  if ( num_parks != 94 ) {

    //user will input index of parks they want, those parks will be taken from all parks vector and put into chosen parks
    for (unsigned i = 0; i < num_parks; i++) {
      cout << "/-------------------------------------------------------------------/";
      cout << endl << endl << "Enter the number of a park you'd like to visit from the list above^" << endl;
      int input; cin >> input;
      cout << endl;
    
      //adds chosen parks index and checks that it was succsefully added
      if ( j.add_chosen_park( input ) == false ) {
        i--;
        //repeats the loop if there was an invalid input
      }

    j.print_chosen_parks();

    }

  } else {
    j.set_all_parks();
  }

  /*
      END OF USER INPUT
  */

  //Builds the adj matrix based of the parks chosen by users
  j.build_adjacency_matrix();

  //function below Prints the adjacency matrix (works better with smaller sizes, as the terminal is too small for large adj matrices)
  //j.print_adjacency_matrix();
  
  std::cout << "\n\n";

  //Builds DFS traversal starting at 0th park
  j.dfs(0);
  j.print_dfs();

  //Builds the Minimum Spanning tree for our graph and displays the Edges and Weight. Weight is in KM scaled down by 100, to accomodate the tsp solver
  j.prims_algorithim();

  //Solves the traveling-salesman problem based on the parks chosen and displays solution
  j.tsp();
  j.print_tsp();

  return 0;
}
