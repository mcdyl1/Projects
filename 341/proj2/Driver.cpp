#include <iostream>
#include <fstream>
using namespace std ;

#include "Sally.h"

int main() {
   ifstream ifile("test.sally") ;

   Sally S(ifile) ;

   S.mainLoop() ;

   ifile.close() ;
   return 0 ;
}
