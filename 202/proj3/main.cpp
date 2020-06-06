/*File: main.cpp
  Proj: CMSC 202 Proj3, Spring 2018
  Author: Dylan McQuaid
  Date: 4/10/18
  Section: 4
  Email: mcdyl1@umbc.edu
  Description: Builds linked list that are imagined as trains holding cars
  carrying cargo. Then checks to see if trains are valid based upon
  their cargo
*/
#include "Car.h"
#include "Train.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){
  vector <Train*> trains;

  string strTrainNum;
  string addOrRem;
  string cargo;
  CARGO_TYPE enumCargo;
  int trainCounter = 0;
  ifstream infile(argv[1]);

  //reading in file
  while(!infile.eof()){
    getline(infile, strTrainNum, ',');
    getline(infile, addOrRem, ',');
    getline(infile, cargo);

    if(cargo == "BIOLOGICAL")
      enumCargo = BIOLOGICAL;
    if(cargo == "POISONOUS")
      enumCargo = POISONOUS;
    if(cargo == "COMBUSTIBLE")
      enumCargo = COMBUSTIBLE;
    if(cargo == "OXIDIZER")
      enumCargo = OXIDIZER;
    if(cargo == "RADIOACTIVE")
      enumCargo = RADIOACTIVE;
    if(cargo == "LOCOMOTIVE")
      enumCargo = LOCOMOTIVE;
    if(cargo == "CABOOSE")
      enumCargo = CABOOSE;
    
    //to prevent reading in last line twice
    if(infile.peek() == '\n')
      infile.ignore('\n');

    int trainNum = atoi(strTrainNum.c_str());
    
    //make first train
    if(trains.size() == 0){
      Train *train = new Train(trainNum);
      trains.push_back(train);
    }
    
    //see if need to make new train
    else{
      if(trains.at(trainCounter)->getNumber() != trainNum){
	Train *train = new Train(trainNum);
	trains.push_back(train);
	trainCounter++;
      }      
    }

    //add car or remove cars of that type based on whats read in
    if(addOrRem == "add"){
      trains.at(trainCounter)->addCar(enumCargo, trains.at(trainCounter)->getLength());
    }
    if(addOrRem == "remove"){
      trains.at(trainCounter)->removeCar(enumCargo);
    }
  }
  
  //print trains
  for(unsigned int i = 0; i < trains.size(); i++){
    cout << *trains.at(i);
  }

  //for(unsigned int i = 0; i < trains.size(); i++){
  //  delete trains.at(i);
  //}

  infile.close();

  return 0;
}
