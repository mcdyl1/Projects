#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Ship{
 public:
  // Name: Ship (Default Constructor)
  // Preconditions: Cannot call directly (used by subclasses)
  // Postconditions: Either a Imperial or Rebel ship is created
  Ship(string name = "",string type = "",int attack = 0, int defense = 0);
  // Name: Getters and Setters
  // Preconditions: Must have a ship
  // Postconditions: Either sets or gets part of class
  string getName();
  void setName(string name);
  string getType();
  void setType(string type);
  int getAttack();
  void setAttack(int attack);
  int getDefense();
  void setDefense(int defense);
  // Name: attack (Purely virtual)
  // Preconditions: One ship is attacking another ship
  // Postconditions: Returns a 1 if enemy is destroyed, 0 if enemy damaged
  virtual bool attack(Ship* enemy) = 0;
  // operator<<(ostream&, Ship&) - overload the << operator to handle a Ship object
  // Preconditions: a valid ostream and Ship operator (calls toString)
  // Postconditions: returns an ostream object
  friend ostream& operator<<(ostream& os, Ship& b);
 private:
  // Name: toString (purely virtual)
  // Preconditions: Requires a valid ship object
  // Postconditions: returns an ostream object (uses either Imperial or Rebel)
  virtual ostream& toString(ostream& o) = 0;
  string m_name; //Ship name
  string m_type; //Ship type
  int m_attack; //Ship attack
  int m_defense; //Ship defense
};

#endif
