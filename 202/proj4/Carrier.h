#ifndef CARRIER_H
#define CARRIER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "Mail.h"

using namespace std;

class Carrier{

public:
  // Constructor
  // Preconditions: None
  // Postconditions: None
  Carrier();
  
  // Destructor
  // Preconditions: An initialized Carrier object in memory
  // Postconditions: Object deallocated
  virtual ~Carrier(){};
  
  // insert(Mail*) - Inserts mail into the vector of Mail*
  // Preconditions: A valid Mail pointer. Not at max capacity
  // Postconditions: Adds the mail pointer to m_storage
  int insert(Mail*);
  
  // deliver() - Virtual function to handle delivering mail
  // Preconditions: Mail to be present in m_storage
  // Postconditions: Displays info about the delivery
  virtual int deliver() = 0;
  
  // setMaxCapacity(int) - Sets the max capacity of the Carrier
  // Preconditions: a positive int
  // Postconditions: m_max_capacity is set
  void setMaxCapacity(int);
  
  // setRate(float) - Sets the delivery cost rate of the Carrier
  // Preconditions: a positve float
  // Postconditions: m_delivery_rate is set
  void setRate(float);
  
  // operator<<(ostream&, const Carrier&) - Allows the << operator to be 
  // used on a Carrier object
  // Preconditions: valid ostream and Carrier objects
  // Postconditions: returns ostream
  friend ostream &operator<<(ostream&,const Carrier&);

 protected:
  // toString - Virtual function to return a string version of Carrier
  // Preconditions: Carrier object exists
  // Postconditions: Returns string
  virtual ostream& print(ostream&) const = 0;
  

  int m_max_capacity;
  float m_delivery_rate;
  vector<Mail*> m_storage;
};

#endif
