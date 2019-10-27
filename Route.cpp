/************************************************
 ** File: Route.cpp
 ** Project: CMSC 202 Project 3, Bus Routes
 ** Author: Steven Ryan
 ** Date: 3/20/19
 ** Section: 12
 ** E-Mail: sryan6@umbc.edu
 **
 ** This file is used to write the source code
 ** for the Route methods
 ***********************************************/

//Preprocessor Directives
#include "Route.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <string>
using namespace std;

//Default Constructor
Route::Route(){
  m_start = nullptr;
  m_size = 0;
}

//Default Destructor
Route::~Route(){
  Clear();
}

//Inserts a new stop into the route
void Route::InsertAt(string name, int location, int riders, double cost){

  //Creats a new Dynamically allocated stop to be loaded with the variables
  Stop *newStop = new Stop(name, location, riders, cost);

  //if the Route is empty, puts in the new stop
  if(IsEmpty() == true){
    m_start = newStop;
    m_size = 1;
    return;
  }
  //Else the linked list has at least one entry
  else{

    //Iterates through the linked list
    for(Stop *curr = m_start; curr != nullptr; curr = curr->m_next){

      //If the stop is to be placed at the beginning of the list
      if((newStop->m_location < curr->m_location) &&
	 (curr->m_location == m_start->m_location)){

	//makes starting pointer point to newStop and newStop to the original start
	newStop->m_next = curr;
	m_start = newStop;
	m_size += 1;

	//returns to exit as soon as the stop is inserted
	return;
      }

      //If the stop is to be placed at the end of the list
      else if((curr->m_next == nullptr) && (newStop->m_location > curr->m_location)){

	//makes the last stop point to newStop and newStop to nullptr
	curr->m_next = newStop;
	newStop->m_next = nullptr;
	m_size += 1;
	return;
      }

      //If the stop is the be placed in the middle of the list
      else if(newStop->m_location < curr->m_next->m_location){

	//inserts a new stop in the middle of two stops by looking
	//ahead with a second pointer
	newStop->m_next = curr->m_next;
	curr->m_next = newStop;
	m_size += 1;
	return;
      }
    }
  }
}

//Prints out the Route including each stop
void Route::DisplayRoute(){
  int i = 1;
  if(IsEmpty()){
    cout << "The Route is empty" << endl;
    return;
  }
  for(Stop *curr = m_start; curr != nullptr; curr = curr->m_next){
    cout << "Stop " << i << " - " << curr->m_name << "(" << curr->m_location << ")\n";
    i++;
  }
}

//Returns true if empty and false if not empty
bool Route::IsEmpty(){
  if(m_size == 0){
    return true;
  }
  return false;
}

//Getter function for Route Earnings
double Route::GetRouteEarnings(double riderFare){
  double total = 0;
  for(Stop *curr = m_start; curr != nullptr; curr = curr->m_next){
    total += (riderFare * (double)curr->m_riders);
  }
  return total;
}

//Getter function for Route Expenses
double Route::GetRouteExpenses(){
  double total = 0;
  for(Stop *curr = m_start; curr != nullptr; curr = curr ->m_next){
    total += curr->m_cost;
  }
  return total;
}

//destroys the whole list of stops
void Route::Clear(){
  Stop *temp = m_start;
  while(m_start != nullptr){
    //deallocates memory to each pointer and saves their m_next in a temp variable
    temp = m_start->m_next;
    delete m_start;
    m_start = temp;
  }
  m_start = nullptr;
  m_size = 0;
}

//Deletes any routes that make less money than they cost
void Route::OptimizeRoute(double riderFare){
  Stop *curr = m_start;
  Stop *temp;
  while(curr != nullptr){
    temp = curr->m_next;
    //checks condition if the route has made a net loss profit
    if(((double)curr->m_riders * riderFare) < (curr->m_cost)){
      RemoveStop(curr->m_location);
    }
    curr = temp;
  }
}

//Deletes stop in the route via location value
void Route::RemoveStop(int stopLocation){
  //Iterates through the linked list
  m_size -= 1;
  //if the stop to remove is the first object in the linked list
  if(m_start->m_location == stopLocation){
    Stop *temp = m_start->m_next;
    delete m_start;
    m_start = temp;
    return;
  }
  //else the stop to remove is not the first object in the linked list
  else{
    for(Stop *curr = m_start; curr != nullptr; curr = curr->m_next){
      if(curr->m_next->m_location == stopLocation){
	//looks ahead to delete a stop by using a second, temporary pointer
	Stop *temp = curr->m_next->m_next;
	delete curr->m_next;
	curr->m_next = temp;
	return;
      }
    }
  }
}

//Prints data for each stop
void Route::DisplayStopData(double riderFare){
  //Prints out the total Earnings and Expenses
  cout << "Earnings: " << GetRouteEarnings(riderFare) << endl;
  cout << "Expenses: " << GetRouteExpenses() << endl;
  
  //Calculates Earnings vs Expenses per each stop
  for(Stop *curr = m_start; curr != nullptr; curr = curr->m_next){
    cout << curr->m_name << endl;
    cout << " Earnings: " << curr->m_riders << "@$" << riderFare << " = $" <<
      (double)curr->m_riders * riderFare << endl;
    cout << " Expenses: $" << curr->m_cost << endl;
    cout << " Total: $" << ((double)curr->m_riders * riderFare) - curr->m_cost << endl;
  }
}

//Getter function for the size of the route
int Route::GetSize(){
  return m_size;
}

ostream &operator<< (ostream &output, Route &myRoute){
  myRoute.DisplayRoute();
  return output;
}
