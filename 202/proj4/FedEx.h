#ifndef FEDEX_H
#define FEDEX_H

#include "Carrier.h"

class FedEx : public Carrier{
public:
  // Constructor
  // Preconditions: None
  // Postconditions: None
  FedEx();
  
  // Destructor
  // Preconditions: An allocated object in memory
  // Postconditions: Deallocates the memory
  ~FedEx();
  
  // deliver() - performs the actions of delivering as a FedEx object
  // Preconditions: mail present in m_storage
  // Postconditions: outputs data and returns a status # (0 - fail, 1 - success)
  int deliver();
 private:
  // toString() - method to format the object as a string
  // Preconditions: a valid FedEx object
  // Postconditions: returns the FedEx object as a string
  ostream& print(ostream&) const;
};

#endif
