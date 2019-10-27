#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct Stop {
  Stop(){
    m_name = "New";
    m_location = 0;
    m_riders = 0;
    m_cost = 0;
    m_next = NULL;
  }
  Stop(string name, int location, int riders, double cost){
    m_name = name;
    m_location = location;
    m_riders = riders;
    m_cost = cost;
    m_next = NULL;
  }
  string m_name; //Name of the stop
  int m_location; //Numerical order of this stop (must be unique and ordered 0 - n)
  int m_riders; //Number of monthly riders
  double m_cost; //Cost to have this stop
  Stop *m_next; //Pointer to next stop
};

class Route {
 public:
  // Name: Route() - Default Constructor
  // Desc: Used to build a new bus route (which is a linked list)
  // Preconditions: None
  // Postconditions: Creates a new bus route where m_start and m_end point to NULL
  Route();
  // Name: ~Route() - Destructor
  // Desc: Used to destruct a route (which is a linked list)
  // Preconditions: There is an existing route with at least one stop
  // Postconditions: A route is deallocated (including all dynamically allocated stops)
  //                 to have no memory leaks!
 ~Route();
  // Name: InsertAt
  // Preconditions: Takes in a name, location, number of riders,
  //                and a cost (in dollars).
  //                Creates new stop.
  //                Inserts each Stop based on their integer location
  //                Requires a route.
  // Postconditions: Adds a new stop to the route at a unique location.
  void InsertAt(string name, int location, int riders, double cost);
  // Name: DisplayRoute
  // Preconditions: Outputs the route.
  // Postconditions: Returns a numbered list of all stops on a route.
  void DisplayRoute();
  // Name: IsEmpty
  // Preconditions: Requires a route
  // Postconditions: Returns if the route is empty.
  bool IsEmpty();
  // Name: GetRouteEarnings
  // Preconditions: Requires a bus route
  // Postconditions: Iterates over complete route and sums total earnings per month
  //                 Fare per rider * riders per stop (Fare is a constant in BusCompany.h)
  double GetRouteEarnings(double riderFare);
  // Name: GetRouteExpenses
  // Preconditions: Requires a Bus Route
  // Postconditions: Iterates over route and sums total cost per station per month
  double GetRouteExpenses();
  // Name: Clear
  // Preconditions: Requires a route
  // Postconditions: Removes all stops in a route
  void Clear();
  // Name: OptimizeRoute
  // Desc: Iterates over a bus route. If a specfic stop earns less than it's cost, it is removed
  //       from the route by calling RemoveStop.
  //       Earning = fare * number of riders and cost = m_cost
  // Preconditions: Requires a Bus Route
  // Postconditions:  Removes stops where (fare * riders) < monthly cost for station
  void OptimizeRoute(double riderFare);
  // Name: RemoveStop
  // Preconditions: Requires a Bus Route
  // Postconditions: Removes a specific bus stop
  void RemoveStop(int stopLocation);
  // Name: GetStopData
  // Desc: Displays name, earnings and expenses for stop
  // Preconditions: Requires a bus route passed riderFare (from constant in BusCompany.h)
  // Postconditions: None
  void DisplayStopData(double riderFare);
  // Name: GetSize
  // Precondition: Requires a bus route
  // Postcondition: Returns the number of stops in the route as an integer
  int GetSize();
  // Name: operator<< (Overloaded << operator)
  // Preconditions: Requires a route with stops
  // Postconditions: Returns a route with stops separated by ->
  friend ostream &operator<< (ostream &output, Route &myRoute);
 private:
  Stop *m_start; //Stop pointer for the first stop
  int m_size; //Int size
};

#endif
