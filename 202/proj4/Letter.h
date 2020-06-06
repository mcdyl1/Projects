#ifndef LETTER_H
#define LETTER_H

#include "Mail.h"

class Letter:public Mail{
 public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Letter();
  
  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Letter(int, string, string, float, float);
  
  // Destructor
  // Preconditions: A letter object allocated in memory
  // Postconditions: Deallocates the object in memory
  ~Letter();
  
  // toString() - method to format the Letter object as a string
  // Preconditions: A Letter object
  // Postconditions: returns the letter object as a string
  string toString();
  
};

#endif
