#ifndef TQUEUE_H
#define TQUEUE_H

#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
class Tqueue {
public:
  //Name: Tqueue - Default Constructor
  //Precondition: None (Must be templated)
  //Postcondition: Creates a queue using dynamic array
  Tqueue(); //Default Constructor
  //Name: Copy Constructor
  //Precondition: Existing Tqueue
  //Postcondition: Copies an existing Tqueue
  Tqueue( const Tqueue<T>& x ); //Copy Constructor
  //Name: Destructor
  //Precondition: Existing Tqueue
  //Postcondition: Destructs existing Tqueue
  ~Tqueue(); //Destructor
  //Name: enqueue
  //Precondition: Existing Tqueue
  //Postcondition: Adds item to back of queue.
  //If queue is at capacity, doubles size and copies everything starting at 0
  void enqueue(T data); //Adds item to queue (to back)
  //Name: dequeue
  //Precondition: Existing Tqueue
  //Postcondition: Removes item from front of queue
  //If queue is less than half capacity, halves capacity
  //and copies everything starting at 0 
  void dequeue(); //Removes item from queue (from front)
  //Name: queueFront
  //Precondition: Existing Tqueue
  //Postcondition: Returns front item in queue (does not remove it)
  T& queueFront();    // Retrieve front (does not remove it)
  //Name: getBack()
  //Precondition: Existing Tqueue
  //Postcondition: Retrieve int of m_back
  int getBack();
  //Name: getFront()
  //Precondition: Existing Tqueue
  //Postcondition: Retrieve int of m_front
  int getFront();
  //Name: isEmpty
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is empty else 0
  int isEmpty(); //Returns 1 if queue is empty else 0
  //Name: size
  //Precondition: Existing Tqueue
  //Postcondition: Returns size of queue (not capacity but m_back - m_front)
  int size(); //Returns size of queue
  //Name: Overloaded assignment operator
  //Precondition: Existing Tqueue
  //Postcondition: Sets one Tqueue to same as a second Tqueue using =
  Tqueue<T>& operator=( const Tqueue<T> &y); //Overloaded assignment operator for queue
  //Name: Overloaded [] operator
  //Precondition: Existing Tqueue
  //Postcondition: Returns object from Tqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from queue
  //Name: displayTqueue (Test function)
  //Precondition: Existing Tqueue
  //Postcondition: Used to display all members in the Tqueue
  void displayTqueue();
private:
  T* m_data; //Data of the queue (Must be dynamically allocated array)
  int m_front; //Front of the queue
  int m_back; //Back of the queue
  int m_capacity; //Capacity of the queue
};

//Name: Tqueue - Default Constructor
//Precondition: None (Must be templated)
//Postcondition: Creates a queue using dynamic array
template <class T>
Tqueue<T>::Tqueue(){
  m_capacity = 1;
  m_front = 0;
  m_back = 0;
  m_data = new T[m_capacity];//Tqueue starts at capacity of 1
}

//Name: Copy Constructor
//Precondition: Existing Tqueue
//Postcondition: Copies an existing Tqueue
template <class T>
Tqueue<T>::Tqueue( const Tqueue<T>& x ):m_front(x.m_front), m_back(x.m_back), m_capacity(x.m_capacity){
  cout << "Copy" << endl;
  m_data = new T[m_capacity];
  //loop through and copy all values in passed in array
  for(int i = m_front; i < m_capacity; i++){
    m_data[i] = x.m_data[i];
  }
}

//Name: Destructor
//Precondition: Existing Tqueue
//Postcondition: Destructs existing Tqueue
template <class T>
Tqueue<T>::~Tqueue(){
  delete [] m_data;
  m_data = NULL;
}

//Name: enqueue
//Precondition: Existing Tqueue
//Postcondition: Adds item to back of queue.
//If queue is at capacity, doubles size and copies everything starting at 0
template <class T>
void Tqueue<T>::enqueue(T data){
  //make sure capacity can change
  if(m_capacity == 0){
    m_capacity = 1;
  }
  
  //if queue is not full
  if(m_capacity != m_back){
    m_data[m_back] = data;
    m_back++;
  }

  //full queue
  else{
    m_capacity = m_capacity * 2;//doubles capacity

    //copy all data from current queue to temporary queue
    T *newArr = new T[m_capacity];
    for(int i = m_front; i < m_back; i++){
      newArr[i] = m_data[i];
    }
    //get rid of current array
    delete[] m_data;
    m_data = NULL;
    //create a new empty queue with new capacity
    m_data = new T[m_capacity];

    //copy all data back into queue
    for(int i = m_front; i < m_back; i++){
      m_data[i] = newArr[i];
    }

    //free memory, add data to back of queue then move back forward
    //inside queue's capacity
    delete [] newArr;
    newArr = NULL;
    m_data[m_back] = data;
    m_back++;
  }
}

//Name: dequeue
//Precondition: Existing Tqueue
//Postcondition: Removes item from front of queue
//If queue is less than half capacity, halves capacity
//and copies everything starting at 0
template <class T>
void Tqueue<T>::dequeue(){
  if(size() == 0){
   return;
  }

  //one thing in queue complete reset of array
  if(size() == 1){
    m_back = 0;
    m_capacity = 0;
    m_front = 0;
  }

  //half capacity if size is less than half the capacity
  else if (size() <= (m_capacity/2)){
    m_capacity /= 2;

    //create temporary queue
    T *newArr = new T[m_capacity];
    int j = 0;

    //skip first element in current queue and copy it to spot 0
    //in temporary queue
    for(int i = m_front; i < m_back; i++){
      newArr[j] = m_data[i+1];
      j++;
    }

    //delete current queue
    delete [] m_data;
    m_data = NULL;

    //create new queue with new capacity
    m_data = new T[m_capacity];
    m_back = size() - 1; //update back index of array
    m_front = 0; //reset front 
    for(int i = m_front; i < m_back; i++){
      m_data[i] = newArr[i];
    }

    //free up temporary queue
    delete [] newArr;
    newArr = NULL;
  }
  else{
    m_front+=1;//skip front 
  }
}

//Name: queueFront
//Precondition: Existing Tqueue
//Postcondition: Returns front item in queue (does not remove it)
template <class T>
T& Tqueue<T>::queueFront(){
  return m_data[m_front];
}

//Name: getBack()
//Precondition: Existing Tqueue
//Postcondition: Retrieve int of m_back
template <class T>
int Tqueue<T>::getBack(){
  return m_back;
}

//Name: getFront()
//Precondition: Existing Tqueue
//Postcondition: Retrieve int of m_front
template <class T>
int Tqueue<T>::getFront(){
  return m_front;
}

//Name: isEmpty
//Precondition: Existing Tqueue
//Postcondition: Returns 1 if queue is empty else 0
template <class T>
int Tqueue<T>::isEmpty(){
  if(size() == 0){
    return 1;
  }
  else{
    return 0;
  }
}

//Name: size
//Precondition: Existing Tqueue
//Postcondition: Returns size of queue (not capacity but m_back - m_front)
template <class T>
int Tqueue<T>::size(){
  return (m_back - m_front);
}

//Name: Overloaded assignment operator
//Precondition: Existing Tqueue
//Postcondition: Sets one Tqueue to same as a second Tqueue using =
template <class T>
Tqueue<T>& Tqueue<T>::operator=( const Tqueue<T> &y){  
  //free up current queue
  delete[] m_data;
  m_data = NULL;
  if(this == &y){
    return *this;
  }
  m_capacity = y.m_capacity;
  m_front = y.m_front;
  m_back = y.m_back;
  m_data = new T[m_capacity];
  for(int i = m_front; i < m_back; i++){
    m_data[i] = y.m_data[i];
  }
  return *this;
}

//Name: Overloaded [] operator
//Precondition: Existing Tqueue
//Postcondition: Returns object from Tqueue using []
//Overloaded [] operator to pull data from queue
template <class T>
T& Tqueue<T>::operator[] (int x){
  return m_data[x];
}

//Name: displayTqueue (Test function)
//Precondition: Existing Tqueue
//Postcondition: Used to display all members in the Tqueue
template <class T>
void Tqueue<T>::displayTqueue(){
  for(int i = m_front; i < m_back; i++){
    cout << m_data[i] << ", ";
  }
  cout << endl;
}



// This is the type of code you should test your Tqueue with
// Once you have coded all of the functions, compile just Tqueue and test it
/*
int main () {
      
  cout << "newQ" << endl;
  Tqueue<int> newQ;
  newQ.displayTqueue();
  newQ.enqueue(10);
  cout << "AFTER ADDING 10" << endl;
  newQ.displayTqueue();
  
  cout << "AFTER ADDING 20" << endl;
  newQ.enqueue(20);
  newQ.displayTqueue();
  cout << "AFTER ADDING 30" << endl;
  newQ.enqueue(30);
  newQ.displayTqueue();
  
 
  cout << "AFTER REMOVING 10" << endl;
  newQ.dequeue();
  newQ.displayTqueue();
  cout << "AFTER REMOVING 20" << endl;
  newQ.dequeue();
  newQ.displayTqueue();
  cout << "AFTER REMOVING 30" << endl;
  newQ.dequeue();
  newQ.displayTqueue();
  cout << "AFTER REMOVING NOTHING" << endl;
  newQ.dequeue();
  newQ.displayTqueue();
  cout << "AFTER ADDING 40" << endl;
  newQ.enqueue(40);
  newQ.displayTqueue();
  
  cout << "AFTER ADDING 40 and 50" << endl;
  newQ.enqueue(40);
  newQ.enqueue(50);
  newQ.displayTqueue();
  cout << "newQ2 using assignment operator" << endl;
  Tqueue<int> newQ2;
  newQ2 = newQ;
 
  newQ2.displayTqueue();

  cout << "newQ3 using copy constructor" << endl;
  Tqueue<int> newQ3(newQ2);
  newQ3.displayTqueue();
  
  cout << endl << "newQ after two dequeue" << endl;
  newQ.dequeue();
  newQ.dequeue();
  newQ.displayTqueue();
  cout << endl;
  
  cout << "newQ4 using copy with deletes" << endl;
  Tqueue<int> newQ4(newQ);
  newQ4.dequeue();
  newQ4.dequeue();
  newQ4.dequeue();
  newQ4.dequeue();
  newQ4.displayTqueue();
  
  newQ3 = newQ4;
  newQ3.displayTqueue();
  
  Tqueue<int> newQ5;
  for(int i = 0;i<400;i++){
    newQ5.enqueue(i);
  }
  cout << "size()=" << newQ5.size() << endl;
  newQ5.displayTqueue(); 
    
  return 0;
}
*/
#endif
