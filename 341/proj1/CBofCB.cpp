// file: CBofCB.cpp

#include "CBofCB.h"
#include <stdexcept>
#include <iostream>
using namespace std;


// default constructor
CBofCB::CBofCB(){
  for(int i = 0; i < m_obCapacity; i++){
    m_buffers[i] = NULL;
  }
  m_newest = 0;//index newest buffer
  m_oldest = 0;//index oldest buffer
  m_buffers[m_newest] = new InnerCB();//defaults to size 10;
  m_obSize = 1;//ob size is now 1
}

// copy constructor
CBofCB::CBofCB(const CBofCB& other){
  for(int i = 0; i < m_obCapacity; i++){
    if(other.m_buffers[i] == NULL){
      m_buffers[i] = NULL;
    }
    else{
      m_buffers[i] = other.m_buffers[i];
      m_buffers[i] = new InnerCB(*other.m_buffers[i]);
    }
  }
  m_obSize = other.m_obSize;
  m_newest = other.m_newest;
  m_oldest = other.m_oldest;
}

// destructor
CBofCB::~CBofCB(){
  for(int i = 0; i < m_obCapacity; i++){
    delete m_buffers[i];
    m_buffers[i] = NULL;
  }
}

// add item to this data structure
void CBofCB::enqueue(int data){
  if(isFull()){
    //both outer and last inner buffer full
    throw overflow_error("Completely full");
  }
  else{
    //just the newest buffer is full
    if(m_buffers[m_newest]->isFull()){
      //create new InnerCB, put one spot forward and double capacity
      int oldNewest = m_newest;
      m_newest = (m_newest + 1) % m_obCapacity;
      m_buffers[m_newest] = new InnerCB((m_buffers[oldNewest]->capacity()*2));
      m_buffers[m_newest]->enqueue(data);//new newest add data
      //cout << "ADDING TO SIZE" << endl;
      m_obSize++;
    }
    else{
      //current newest inner buffer can just add data
      m_buffers[m_newest]->enqueue(data);
    }
  }
}

// remove item from this data structure
int CBofCB::dequeue(){
  if(isEmpty()){
    throw underflow_error("No buffers inside buffer");
  }
  else{
    
    int rmed_value = m_buffers[m_oldest]->dequeue();
    //after value removed if inner buffer empty delete it if not only buffer
    if(m_buffers[m_oldest]->isEmpty() && m_obSize > 1){
      delete m_buffers[m_oldest];
      m_buffers[m_oldest] = NULL;
      m_oldest = (m_oldest + 1) % m_obCapacity;//move oldest to next buffer
      m_obSize--;
    }
    return rmed_value;
  }
}

// returns true if cannot add more items
bool CBofCB::isFull(){
  if(m_obSize == m_obCapacity && m_buffers[m_newest]->isFull()){
    return true;
  }
  return false;
}

// returns true if no items stored in data structure
bool CBofCB::isEmpty(){
  if(m_obSize == 1 && m_buffers[m_oldest]->isEmpty()){
    return true;
  }
  return false;  
}

// number of items in the data structure as a whole.
// Note: not the number of InnerCB's
int CBofCB::size(){
  int dataSize = 0;

  for(int i = m_oldest; i < m_oldest + m_obSize; i++){
    int temp = i;
    temp = temp % m_obCapacity;
    dataSize += m_buffers[temp]->size();
  }
  
  return dataSize;
  
}

// overloaded assignment operator
const CBofCB& CBofCB::operator=(const CBofCB& rhs){
  if(this != &rhs){
    for(int i = 0; i < m_obCapacity; i++){
      delete m_buffers[i];
      m_buffers[i] = NULL;
      
      if(rhs.m_buffers[i] != NULL){
	m_buffers[i] = new InnerCB(*rhs.m_buffers[i]);
      }
    }
  }
  
  m_obSize = rhs.m_obSize;
  m_oldest = rhs.m_oldest;
  m_newest = rhs.m_newest;
  
  return *this;
}

// debugging function, prints out contents of data structure
void CBofCB::dump(){
  cout << "---------------------------------------" << endl;
  cout << "Outer Circular buffer dump(), m_obSize = " << m_obSize << endl;


  for(int i = m_oldest; i < m_oldest + m_obSize; i++){
    int temp = i;
    temp = temp % m_obCapacity;
    cout << "[" << temp << "]";
    m_buffers[temp]->dump();
  }

  cout << "---------------------------------------" << endl; 
}
