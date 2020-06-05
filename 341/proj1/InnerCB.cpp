// file: InnerCB.cpp

#include "InnerCB.h"
#include <stdexcept>
#include <iostream>
using namespace std;

// Constructor, default size is 10.
InnerCB::InnerCB(int n){
  m_buffer = new int[n];
  m_capacity = n;
  m_size = 0;
  m_start = 0;//oldest item 
  m_end = 0;//newest item
}

// Copy constructor
InnerCB::InnerCB(const InnerCB& other){
  m_capacity = other.m_capacity;
  m_start = other.m_start;
  m_end = other.m_end;
  m_size = other.m_size;
  m_buffer = new int[m_capacity];
  //copy all values from 
  for(int i = 0; i < m_capacity; i++){
    m_buffer[i] = other.m_buffer[i];
  }
}

// Destructor
InnerCB::~InnerCB(){
  delete [] m_buffer;
  m_buffer = NULL;
}

// Add item to circular buffer
void InnerCB::enqueue(int data){
  if(isFull()){
    throw overflow_error("Buffer is full");
  }
  //empty add to index 0
  if(isEmpty()){
    m_buffer[m_start] = data;
    m_size++;
  }
  else{
    //move m_end forward, add data
    m_end = (m_end + 1) % m_capacity;
    m_buffer[m_end] = data;
    m_size++;
  }
}

// Remove item from circular buffer
int InnerCB::dequeue(){
  if(isEmpty()){
    throw underflow_error("Buffer is empty");
  }
  else{
    int value = m_buffer[m_start];//item being removed
    //move start forward
    m_start = (m_start + 1) % m_capacity;
    m_size--;

    return value;
  }  
}

// True if no space left in buffer
bool InnerCB::isFull(){
  if(m_size == m_capacity){
    return true;
  }
  return false;
}

// True if buffer holds no items
bool InnerCB::isEmpty(){
  if(m_size == 0){
    return true;
  }
  return false;
}

// return maximum number of items this buffer can hold
int InnerCB::capacity(){
  return m_capacity;
}

// return number of items currently held in the buffer
int InnerCB::size(){
  return m_size;
}

// overloaded assignment operator
const InnerCB& InnerCB::operator=(const InnerCB& rhs){
  if(this != &rhs){
    delete [] m_buffer;
    m_capacity = rhs.m_capacity;
    m_start = rhs.m_start;
    m_end = rhs.m_end;
    m_size = rhs.m_size;
    m_buffer = new int[m_capacity];
    for(int i = 0; i < m_capacity; i++){
      m_buffer[i] = rhs.m_buffer[i];
    }
  }
  return *this;
}

// debugging function. Prints out contents.
void InnerCB::dump(){
  cout << "InnerCB dump(): m_size = " << m_size << endl;

  for(int i = m_start; i < m_start + m_size; i++){
    int temp = i;
    temp = temp % m_capacity;
    cout << "[" << temp << "]" << m_buffer[temp] << ", ";
    
  }
  cout << endl;
  
}
