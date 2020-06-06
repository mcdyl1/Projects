/* Name:    Car.h
   Project: CMSC 202 Project 3, Spring 2018
   Project Design: Felipe Bastos
   Date:    03/12/2018
   Desc: This file contains the class for the Car class. The Car class acts as 
         the nodes for the linked list. The train is the linked list and the
	 cars are the nodes. Each car can hold any/some/none of the cargo types
	 listed below. The cargo is the data for that node.
*/

#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

enum CARGO_TYPE { //All of the possible cargo types (or car types)
  BIOLOGICAL,
  POISONOUS,
  COMBUSTIBLE,
  OXIDIZER,
  RADIOACTIVE,
  LOCOMOTIVE,
  CABOOSE
};

class Car {
 public:    
  // Name: Car (Default Constructor)
  // PreCondition:  none
  // PostCondition: instantiates a default-constructed Car object
  Car();
  
  // Name: Car (Overloaded Constructor)
  // PreCondition:  CARGO_TYPE is valid
  // PostCondition: instantiates a Car object with given cargo
  Car(CARGO_TYPE);
  
  // Name: ~Car (Destructor)
  // PreCondition:  none
  // PostCondition: destroys car object and deallocates memory
  ~Car();
  
  // Name: getCargo
  // PreCondition:  none
  // PostCondition: returns current cargo
  CARGO_TYPE getCargo() const;
  
  // Name: Car
  // PreCondition:  CARGO_TYPE is valid
  // PostCondition: sets a new cargo type for the object
  void setCargo(CARGO_TYPE);
  
  // Name: getNext
  // PreCondition:  none
  // PostCondition: returns the next node in the list (or null)
  Car *const getNext() const;
  
  // Name: setNext
  // PreCondition:  given Car* is a valid pointer to a car object
  // PostCondition: sets the next car to the given pointer.
  void setNext(Car*);
  
  // Name: getLength
  // PreCondition:  none
  // PostCondition: returns the current length of the train, assuming callee
  //                is the head of the list.
  int getLength() const;
  
 private:
  CARGO_TYPE m_cargo; //Type of cargo in a car (max one)
  Car *m_next; //pointer to the next car in train
};

#endif /* CAR_H */
