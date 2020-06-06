/*File: proj2.cpp
  Proj: CMSC 202 Proj2, Spring 2018
  Author: Dylan McQuaid
  Date: 3/27/18
  Section: 4
  Email: mcdyl1@umbc.edu
  Description: A game where user gets to find dragons and build a collection of dragons
  that can be hatched, grown, and fight other dragons
*/
#include "Dragon.h"
#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

int main () {
  Game newGame;
  newGame.StartGame();
  return 0;
}
