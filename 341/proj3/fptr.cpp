// File: fptr.cpp
// 
// CMSC 341 Fall 2017
//
// Simple use of function pointers
//

#include <iostream>
using namespace std ;

// An example function
//
int add3(int x) {
   return  x + 3 ;
}


// Another function that has same
// signature as add3()
//
int add5(int x) {
   return x + 5 ;
}


// function that takes two parameters
//
int addpair3(int x, int y) {
   return x + y + 3 ;
}


// Another function that has same 
// signature as addpair3()
//
int addpair5(int x, int y) {
   return x + y + 5 ;
}


int main() {

   // Declare function pointer named "fptr" that can 
   // point to functions that take an int parameter
   // and returns an int.
   //
   int (*fptr)(int ) ;

   int n ;

   // use fptr to invoke add3
   //
   fptr = add3 ;   // assigns function to function pointer
   n = fptr(8) ;

   cout << "n = " << n << endl ;   // should be 11

   // use fptr to invoke add5
   //
   fptr = add5 ;   // assigns function to function pointer
   n = fptr(8) ;

   cout << "n = " << n << endl ;   // should be 13

   // Declare a function pointer named "anotherFptr"
   // that points to a function that takes two
   // int parameters and returns an int.
   //
   int (*anotherFptr) (int, int) ;

   anotherFptr = addpair3 ;  // function pointer assignment
   n = anotherFptr(17, 13) ;
   cout << "n = " << n << endl ;   // should be 33

   anotherFptr = addpair5 ;  // function pointer assignment
   n = anotherFptr(17, 13) ;
   cout << "n = " << n << endl ;   // should be 35

   return 0 ;
}
