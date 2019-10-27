#ifndef BUSCOMPANY_H
#define BUSCOMPANY_H

#include "Route.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

const double RIDER_FARE = 3.25;

class BusCompany {
 public:
  // Name: BusCompany (default constructor)
  // Preconditions: None
  // Postconditions: A new bus company is created.
  BusCompany();
  // Name: BusCompany (overloaded constructor)
  // Desc: Calls ReadFile and then MainMenu
  // Preconditions: Filename is included
  // Postconditions: A new bus company is created and routes are created from a passed file
  BusCompany(string fileName);
  // Name:  BusCompany (destructor)
  // Preconditions: None
  // Postconditions: All linked lists are destroyed.
  ~BusCompany();
  // Name:  readFile
  // Desc: Populates a vector of linked lists (m_routes of Routes)
  // Preconditions: Valid file name of routes
  // Postconditions: Creates one route as described (file may have multiple routes)
  void ReadFile(string fileName);
  // Name:  mainMenu
  // Preconditions: None
  // Postconditions: None
  void MainMenu();
  // Name:  DisplayRoutes
  // Desc: Iterates over the vector and calls the overloaded << operator for each route
  // Preconditions: At least one route in m_routes;
  // Postconditions: Displays each route in m_routes
  void DisplayRoutes();
  // Name:  OptimizeRoute
  // Desc: Goes through a specific route and removes profit losing stops (3.25 per rider)
  //       Profit is riders * fare per rider vs stop cost
  // Preconditions: Has route
  // Postconditions: Removes up to all stops in a route that lose money
  void OptimizeRoute();
  // Name:  DisplayRouteData()
  // Desc: Displays total earnings and total expenses per route
  //       Displays earnings/expenses by individual stop by route
  // Preconditions: Has route
  // Postconditions: Displays route with stop data
  void DisplayRouteData();
private:
  vector<Route*> m_routes; //Holds all bus routes loaded from files.
                           //Each route is a  linked list
  Route* m_newRoute; //New route that is stored in the m_routes
};

#endif
