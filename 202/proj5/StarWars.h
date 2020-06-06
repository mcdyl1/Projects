#include "Ship.h"
#include "Imperial.h"
#include "Rebel.h"
#include "Tqueue.cpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;
#ifndef STARWARS_H
#define STARWARS_H

class StarWars{
 public:
  // Name: StarWars (Default Constructor)
  // Preconditions: None
  // Postconditions: Creates a new Star War object
  StarWars(); 
  // Name: ~StarWars (Destructor)
  // Preconditions: None
  // Postconditions: Destructs Star War object
  ~StarWars();
  // Name: loadShips
  // Preconditions: Two files (imperial ships then rebel ships) passed in array
  // Postconditions: Populates m_imperialShips and m_rebelShips (returns 1 on success)
  bool loadShips(char* files[]);
  // Name: Start
  // Desc: Manages the game (loadsShips, requests team size, createsTeams, and Battles)
  // Preconditions: Two files (imperial ships then rebel ships) passed in array
  // Postconditions: None (game ends when it ends)
  void Start(char* files[]);
  // Name: createTeams
  // Desc: Populates two Tqueues of ships randomly
  //        Tqueue m_myShips is populated from m_rebelShips (enqueue)
  //        Tqueue m_imperialShips is populated from m_imperialShips (enqueue)
  // Preconditions: None
  // Postconditions: Teams created
  void createTeams(int numShips);
  // Name: battle
  // Desc: Manages the battles (random team starts
  //       Front of Tqueue attacks front of second Tqueue
  //       If a member is destroyed, dequeued from Tqueue
  //       Alternate turns and repeat until one of the Tqueues is empty
  //       Note: If a ship is destroyed, it does not attack
  // Preconditions: Two Tqueues of ships are populated
  // Postconditions: A winner must be displayed
  void battle();
 private:
  Tqueue<Ship*> m_myShips; //My Team (rebel ships only)
  Tqueue<Ship*> m_enemyShips; //Enemy Team (imperial ships only)
  vector<Ship*> m_imperialShips; //Imperial Ships
  vector<Ship*> m_rebelShips; //Rebel ships
};

#endif
