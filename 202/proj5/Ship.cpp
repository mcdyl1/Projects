#include "Ship.h"

Ship::Ship(string name, string type, int attack, int defense){
  setName(name);
  setType(type);
  setAttack(attack);
  setDefense(defense);
}

string Ship::getName(){
  return m_name;
}

void Ship::setName(string name){
  m_name = name;
}

string Ship::getType(){
  return m_type;
}

void Ship::setType(string type){
  m_type = type;
}

int Ship::getAttack(){
  return m_attack;
}

void Ship::setAttack(int attack){
  m_attack = attack;
}

int Ship::getDefense(){
  return m_defense;
}

void Ship::setDefense(int defense){
  m_defense = defense;
}

ostream& operator<<(ostream& os, Ship& b){
  b.toString(os);
  return os;
}

