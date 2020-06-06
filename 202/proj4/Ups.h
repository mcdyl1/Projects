#ifndef UPS_H
#define UPS_H

#include "Carrier.h"

class Ups : public Carrier{
public:
  // Constructor
  // Preconditions: None
  // Postconditions: None
  Ups();

  // Destructor
  // Preconditions: An allocated object in memory
  // Postconditions: Deallocates the memory
  ~Ups();

  // deliver() - performs the actions of delivering as a UPS object
  // Preconditions: mail present in m_storage
  // Postconditions: outputs data and returns a status # (0 - fail, 1 - success)
  int deliver();

private:
  // toString() - method to format the object as a string
  // Preconditions: a valid UPS object
  // Postconditions: returns the UPS object as a string
  ostream& print(ostream&) const;

};

#endif
