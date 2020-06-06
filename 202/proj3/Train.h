/*  Name :    Train.h
    Project: CMSC 202 Project 3, Spring 2018
    Project Design: Felipe Bastos
    Desc: This file contains the classdef for the Train class. The Train
          is the linked list in this project. The Car class is the individual nodes.
*/

#ifndef TRAIN_H
#define TRAIN_H

#include "Car.h"

class Train {
 public:
  // Name: Train (Default Constructor)
  // PreCondition:  none
  // PostCondition: instantiates a default-constructed Train object
  Train();

  // Name: Train (Overloaded Constructor)
  // PreCondition:  none
  // PostCondition: instantiates a Train object with a given number
  Train(int);

  // Name: ~Train
  // PreCondition:  none
  // PostCondition: destroys train object
  ~Train();
  
  // Name: display
  // PreCondition:  given ostream& is valid
  // PostCondition: appends own train information to a given ostream&
  void display(ostream&) const;
  
  // Name: isValid
  // PreCondition:  none
  // PostCondition: returns a boolean indicating whether the current
  //                arrangement of the train is valid
  bool isValid() const;
  
  // Name: addCar
  // PreCondition:  given CARGO_TYPE is valid, given integer is a valid 
  //                index (where to insert in train)
  // PostCondition: adds car to the train, at given index. zero-indexed
  int addCar(const CARGO_TYPE&, int);

  // Name: removeCar
  // PreCondition:  given integer is a valid index
  // PostCondition: removes Car from train at given index. zero-indexed
  int removeCar(int);

  // Name: removeCar
  // PreCondition:  given CARGO_TYPE is valid
  // PostCondition: removes every car of given cargo_type from train.
  int removeCar(CARGO_TYPE);
  
  // Name: getLength
  // PreCondition:  none
  // PostCondition: returns current length of the train
  int getLength() const;

  // Name: getNumber
  // PreCondition:  none
  // PostCondition: returns current number of the train (The number is the name of the train)
  int getNumber() const;

  // Name: setNumber
  // PreCondition:  none
  // PostCondition: sets a new number for the train
  void setNumber(int);
  
  // Name: operator<<
  // PreCondition:  given arguments are valid
  // PostCondition: appends train information to ostream&
  // This function just calls the display function and allows us to cout << myTrain
  friend std::ostream &operator<<(std::ostream& output, const Train& myTrain);

 private:
  int m_len; //total size of train
  int m_number; //integer "name" of the train. For example, Train 441
  Car *m_head; //pointer to the first car (should be a locomotive)
};

#endif /* TRAIN_H */
