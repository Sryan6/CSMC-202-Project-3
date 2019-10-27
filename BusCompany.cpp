/************************************************
 ** File: BusCompany.cpp
 ** Project: CMSC 202 Project 3, Bus Routes
 ** Author: Steven Ryan
 ** Date: 3/20/19
 ** Section: 12
 ** E-Mail: sryan6@umbc.edu
 **
 ** This file is used to write the source code
 ** for the BusCompany methods
 ***********************************************/

//Preprocessor Directives
#include "Route.h"
#include "BusCompany.h"

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
BusCompany::BusCompany(){
  MainMenu();
}

//Overloaded Constructor
BusCompany::BusCompany(string fileName){
  ReadFile(fileName);
  MainMenu();
}

//Destructor iterates through the routes vector and deallocates memory to each route
BusCompany::~BusCompany(){
  for(int i = (int)m_routes.size() - 1; i >= 0; i--){
    delete m_routes.at(i);
  }
}

//Loads the vector m_routes with Route objects created from the file.
void BusCompany::ReadFile(string fileName){
  ifstream inputStream;

  //Dynamically allocates a new route
  m_newRoute = new Route();
  
  inputStream.open(fileName);

  //checks if the file has opened properly
  if(inputStream.is_open()){
    //stop struct variables
    string name;
    int location;
    int riders;
    double cost;
    
    string whitespaceHolder;

    //while there is more input to be taken from the file
    while(inputStream){
      getline(inputStream, name, ',');

      //this is true when the end of the route isn't yet reached
      if(name != "End Route"){
	inputStream >> location;
      	inputStream >> riders;
	inputStream >> cost;
	cost = double(cost);

	//ignores newline
	inputStream.ignore(1);

	//creates a new stop for the route
	m_newRoute->InsertAt(name, location, riders, cost);
      }
      else{
	//ignores newline
	if(inputStream.peek() == '\n'){
	  inputStream.ignore();
	}
	//adds the new route to the routes vector
	m_routes.push_back(m_newRoute);
	
	//ignores whitespace between inputs
	if(inputStream.peek() == ' '){
	  getline(inputStream, whitespaceHolder);
	}

	//ignores newline
	if(inputStream.peek() == '\n'){
	  inputStream.ignore();
	}
	//if there is more routes in the file, a new one is created
	if(inputStream){
	  m_newRoute = new Route();
	}
      }
    }
  }
  //produces error message if file cannot be opened
  else{
    cerr << "Error: File could not be opened.";
  }
  //closes file
  inputStream.close();
  for(int i = 0; i < (int)m_routes.size(); i++){
    cout << "Route " << i + 1 << " loaded with " <<
      m_routes.at(i)->GetSize() << " stops." << endl;
  }
}

//Creates the user interface
void BusCompany::MainMenu(){
  int choice;
  cout << "Welcome to the UMBC Transit Sumulator" << endl;

  //Keeps asking for input unless the user selects "Exit"
  do{
    cout << "\nWhat would you like to do?:" << endl;
    cout << "1. Display Routes" << endl;
    cout << "2. Display Earnings vs Expenses By Route" << endl;
    cout << "3. Optimize Route" << endl;
    cout << "4. Exit" << endl;
    cin >> choice;

    //if user chooses selection 1
    if(choice == 1){
      DisplayRoutes();
    }
    //if user chooses selection 2
    else if(choice == 2){
      for(int i = 0; i < (int)m_routes.size(); i++){
	cout << "*** Route " << i + 1 << " ***" << endl;
	m_routes.at(i)->DisplayStopData(RIDER_FARE);
      }
    }
    //if user chooses selection 3
    else if(choice == 3){
      OptimizeRoute();
    }
  } while(choice != 4);
}

//prints out each route by calling each route's DisplayRoute function in the vector
void BusCompany::DisplayRoutes(){
  for(int i = 0; i < (int)m_routes.size(); i++){
    cout << "*** Route " << i + 1 << " ***" << endl;
    cout << *m_routes.at(i);
    cout << "END" << endl;
  }
}

//Asks for user input to choose which route to optimize
void BusCompany::OptimizeRoute(){
  int choice;
  //If there is more than one route
  if((int)m_routes.size() > 1){
    do{
      cout << "Which route would you like to optimize?" << endl;
      for(int i = 0; i < (int)m_routes.size(); i++){
	cout << "Route " << i + 1 << endl;
      }
      cout << "Enter 1 - " << (int)m_routes.size() << " inclusive:" << endl;
      cin >> choice;

      //validates input. The user's choice must be one of the routes
    } while((choice < 1) || (choice > (int)m_routes.size()));
  }
  else{
    //if there is only one route the route is optimized without prompting
    choice = 1;
  }
  
  //decrements by one for indexing
  choice--;

  //calls OptimizeRoute for the route of choice
  m_routes.at(choice)->OptimizeRoute(RIDER_FARE);
}
