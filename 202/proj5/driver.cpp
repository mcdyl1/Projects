#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Tqueue.cpp"
#include "Ship.h"
#include "StarWars.h"
#include "Imperial.h"
#include "Rebel.h"
using namespace std;

int main (int argc, char* argv[]) {
  if(argc != 3){
    cout << "Program requires two file: proj5_imperial.txt and proj5_rebel.txt" << endl;
    cout << "Try: ./proj5 proj5_imperial.txt proj5_rebel.txt" << endl;
    return -1;
  }

  StarWars newStarWars;
  char* files[] = {argv[1],argv[2]};
  newStarWars.Start(files);
  return 0;
}
