#ifndef REBEL_H
#define REBEL_H

#include "Ship.h"

class Rebel:public Ship{
 public:
  // Name: Rebel (Default Constructor)
  // Preconditions: Uses ship constructor (initialization list)
  // Postconditions: Creates a Rebel ship
  Rebel(string name, string type, int attack, int defense)
   :Ship(name, type, attack, defense){}
  // Name: Attack (inherited from Ship)
  // Preconditions: Requires valid enemy ship
  // Postconditions: Compares Rebel attack to Imperial defense
  // Returns 1 if destroyed or 0 if damaged
  bool attack(Ship* enemy);
  // Name: toString() - method to format a rebel
  // Preconditions: A rebel object
  // Postconditions: returns the rebel object as a ostream object
  ostream& toString(ostream& os);
};

#endif
