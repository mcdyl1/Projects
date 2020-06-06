/*
File: proj1.cpp
Project: CMSC 202 Project 1, Spring 2018
Author: Dylan McQuaid
Date: 2/16/18
Section: 04
E-mail: mcdyl1@umbc.edu
Description: Loads a document containing surface types, then gets a base
temperature from the user and uses multipliers to show the effect of the
surface types on the temperature
*/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const int LOAD = 1; //first option in menu
const int MODEL = 2;//second option in menu
const int EXIT = 3;//third option in menu
const int MINBASETEMP = -130;//minimum temperature the user can enter
const int MAXBASETEMP = 134;//max temperature the user can enter
const int COL = 5;//num of columns for the 2D array
const int ROW = 6;//num of rows for the 2D array

//-----------------------------------------------------------------------
// Name: mainMenu
// PreCondition: None
// PostCondition: Tells user thank you or calls to other function
//-----------------------------------------------------------------------
int mainMenu();
//-----------------------------------------------------------------------
// Name: loadFile
// PreCondition: a file exist to be loaded
// PostCondition: 2D array created or no file opened
//-----------------------------------------------------------------------
void loadFile(char landcovers[ROW][COL]);
//-----------------------------------------------------------------------
// Name: printGrid
// PreCondition: a 2D array exist
// PostCondition: printed 2D array in grid format
//-----------------------------------------------------------------------
void printGrid(char landcovers[ROW][COL]);
//-----------------------------------------------------------------------
// Name: modelTemps
// PreCondition: passed an array full of chars
// PostCondition: an array full of doubles representing temperatures
//                is formed and printed out in same grid format
//-----------------------------------------------------------------------
void modelTemps(char landcovers[ROW][COL]);
//-----------------------------------------------------------------------

int main()
{
  mainMenu();
  return 0;
}

int mainMenu(){
  char landcovers[ROW][COL];
  int userInput;
  //the main menu keeps running until the user enters 3
  do{
    cout<< "1. Load Land Cover File" << endl;
    cout<< "2. Model Temperatures Based on Land Cover" << endl;
    cout<< "3. Exit" << endl;

    cout << "Enter 1, 2, or 3: ";
    cin >> userInput;
    
    //what to do based on the user's input
    switch (userInput){
        case LOAD:
	  loadFile(landcovers);
	  break;
        case MODEL:
	  modelTemps(landcovers);
	  break;
    }

  }while(userInput != 3);

  cout << "Thank you for Using the Urban Heat Island Model" << endl;
}

void loadFile(char landcovers[ROW][COL]){
  string userFile = "";
  cout<< "What is the name of the file to import? " << endl;
  cin >> userFile;

  //opens the file(converts to cstring)
  ifstream myfile(userFile.c_str());

  if(myfile.is_open()){
    cout << "File successfully loaded" << endl;

    //creates a 2D array from the data in the file
    for(int i = 0; i < ROW; i++){
      for(int j = 0; j < COL; j++){
	myfile >> landcovers[i][j];
      }
    }
    printGrid(landcovers);
  }
  else{
    cout << "The file " << userFile << " was not opened" << endl;
  }

  myfile.close();
}


void printGrid(char landcovers[ROW][COL]){
  //loops over 2D array and prints out the elements of the array
  for (int i = 0; i < ROW; i++){
    for(int j = 0; j < COL; j++){
      cout << landcovers[i][j] << " ";
    }
    cout << endl;
  }
}

void modelTemps(char landcovers[ROW][COL]){
  double baseTemp;
  double temperatures[ROW][COL] = {{ 0 }};
  char check = landcovers[0][0];

  //makes sure a file is loaded and the array is filled
  if(check == 'R' || check == 'S' || check == 'C' || check == 'U' || 
     check == 'D' || check == 'P' || check == 'F'){

    //getting user input
    do{
      cout << "What is the base temperature?" << endl;
      cin >> baseTemp;
    }while(baseTemp < MINBASETEMP || baseTemp > MAXBASETEMP);

    //formats temperatures to one decimal place
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(1);
    cout.fill(' ');

    //chars in landcovers array tell what to multiply the base temp by
    //the products are then put into the temperatures array
    for(int i = 0; i < ROW; i++){
      for(int j = 0; j < COL; j++){
	if(landcovers[i][j] == 'R'){
	  temperatures[i][j] = (baseTemp * 1.01);
	}
	else if(landcovers[i][j] == 'S'){
	  temperatures[i][j] = (baseTemp * 1.03);
	}
	else if(landcovers[i][j] == 'C'){
	  temperatures[i][j] = (baseTemp * 1.05);
	}
	else if(landcovers[i][j] == 'U'){
	  temperatures[i][j] = (baseTemp * 1.04);
	}
	else if(landcovers[i][j] == 'D'){
	  temperatures[i][j] = (baseTemp * 1.09);
	}
	else if(landcovers[i][j] == 'P'){
	  temperatures[i][j] = (baseTemp * 1.02);
	}
	else if(landcovers[i][j] == 'F'){
	  temperatures[i][j] = (baseTemp * 1);
	}
	
	//prints out elements of array with 10 fill characters 
	//to the left of them
	cout << setw(10) << temperatures[i][j];
      }
      cout << endl;
    }
  }
  else{
    cout << "Error must have file loaded" << endl;
  }
}
