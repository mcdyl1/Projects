#ifndef MEDIANHEAP_H
#define MEDIANHEAP_H

#include <stdexcept>
#include <iostream>
using namespace std;

template <class T>
class MedianHeap;

template <class T>
class Heap{
public:

  Heap();
  
  Heap(int cap, bool (*comparison)(const T&, const T&));

  ~Heap();

  Heap(const Heap<T>& otherH);

  const Heap<T>& operator=(const Heap<T>& rhs);

  int size();

  int capacity();

  void insert(const T& item);

  bool deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&));

  T locateInHeap(int pos);

  void trickleUp(int pos, const T& item);

  void trickleDown(int pos);

  void deleteRoot();

  T getNewMaxOrMin();

private:
  int m_capacity;
  int m_size;
  T* m_array;
  bool (*compare)(const T&, const T&);
  friend MedianHeap<T>;
};

template <class T>
Heap<T>::Heap(){
}

template <class T>
Heap<T>::Heap(int cap, bool (*comparison)(const T&, const T&)){
  compare = comparison;
  m_size = 0;
  m_capacity = cap;
  m_array = new T[m_capacity];
}

template <class T>
Heap<T>::~Heap(){
  delete [] m_array;
  m_array = NULL;
}

template <class T>
Heap<T>::Heap(const Heap<T>& otherH){
  m_capacity = otherH.m_capacity;
  compare = otherH.compare;
  m_size = otherH.m_size;
  m_array = new T[m_capacity];

  for(int i = 1; i <= m_size; i++){
    m_array[i] = otherH.m_array[i];
  }
}

template <class T>
const Heap<T>& Heap<T>::operator=(const Heap<T>& rhs){
  if(this != &rhs){
    delete [] m_array;
    m_capacity = rhs.m_capacity;
    compare = rhs.compare;
    m_size = rhs.m_size;
    m_array = new T[m_capacity];
    for(int i = 1; i <= m_size; i++){
      m_array[i] = rhs.m_array[i];
    }
  }
  return *this;
}

template <class T>
int Heap<T>::size(){
  return m_size;
}

template <class T>
int Heap<T>::capacity(){
  return m_capacity;
}

template <class T>
void Heap<T>::insert(const T& item){
  if(m_size == m_capacity){
    throw out_of_range("This heap is full");
  }
  else{

    //inserting occurs at end of array
    int pos = ++m_size;
    trickleUp(pos, item);//move up if needed
  }
}

template <class T>
bool Heap<T>::deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&)){
  if(m_size == 0){
    throw out_of_range("Nothing to delete");
  }
  
  else{
    for(int i = 1; i <= m_size; i++){
      if(equalTo(givenItem, m_array[i])){//item found
	givenItem = m_array[i];
	m_array[i] = m_array[m_size--];

	trickleUp(i, m_array[i]);
	trickleDown(i);
	
	return true;
      }
    }
  }
  return false;
}

template <class T>
T Heap<T>::locateInHeap(int pos){
  if((pos > m_size + 1) || pos < 1){
    throw out_of_range("Invalid index");
  }
  return m_array[pos];
}

template <class T>
void Heap<T>::trickleUp(int pos, const T& item){
  for(; pos > 1 && compare(item, m_array[pos/2]); pos /= 2){
    m_array[pos] = m_array[pos/2];
  }

  m_array[pos] = item;
}

template<class T>
void Heap<T>::trickleDown(int pos){
  int childPos;
    
  T temp = m_array[pos];
  
  for(; pos * 2 <= m_size; pos = childPos){
    childPos = pos * 2;

    //figure out which child to possibly swap with
    if(childPos != m_size && compare(m_array[childPos+1], m_array[childPos])){
      childPos++;
    }

    //check if trickling down actually needed
    if(compare(m_array[childPos], temp)){
      m_array[pos] = m_array[childPos];
    }
    else{
      break;
    }
  }
  m_array[pos] = temp;
}

template <class T>
void Heap<T>::deleteRoot(){
  if(m_size == 0){
    throw out_of_range("No root to delete");
  }
  
  m_array[1] = m_array[m_size--];

  trickleDown(1);
}

template <class T>
T Heap<T>::getNewMaxOrMin(){
  if(m_size == 0){
    throw out_of_range("The heap is empty");
  }
  
  T newItem = m_array[1];

  for(int i = 1; i <= m_size; i++){
    if(compare(newItem, m_array[i]))
      newItem = m_array[i];
  }

  return newItem;
}

template <class T>
class MedianHeap{
public:

  MedianHeap();
  //first two parameters are function pointers. 1. returns true if first parameter < second
  //second function returns true if first parameter > second
  MedianHeap(bool(*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap=100);

  //copy constructor (may not need to code)
  MedianHeap(const MedianHeap<T>& otherH);

  //destructor(may not need to code)
  ~MedianHeap();

  //overloaded assignment operator(may not need to code)
  const MedianHeap& operator=(const MedianHeap<T>& rhs);

  //total # of items in heap
  int size();

  //max # of items that can be stored
  int capacity();

  //should throw out of range if cant store more
  void insert(const T& item);

  T getMedian();

  T getMin();

  T getMax();

  bool deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&));

  void dump();

  int maxHeapSize();

  int minHeapSize();

  T locateInMaxHeap(int pos);

  T locateInMinHeap(int pos);

private:
  Heap<T>* m_maxHeap;
  Heap<T>* m_minHeap;
  int m_totSize;
  int m_maxCap;
  T m_max;
  T m_min;
  T m_median;
  bool (*less)(const T&, const T&);
  bool (*greater)(const T&, const T&);
};

//Median Heap Functions

template <class T>
MedianHeap<T>::MedianHeap(){
}

template <class T>
MedianHeap<T>::MedianHeap(bool(*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap){
  m_totSize = 0;
  m_maxCap = cap;
  less = lt;
  greater = gt;
  m_maxHeap = new Heap<T>((cap/2)+2, greater);
  m_minHeap = new Heap<T>((cap/2)+2, less);
}

template <class T>
MedianHeap<T>::~MedianHeap(){
  //if commented out, test 6 will run without segfaulting
  //however commenting them out also causes memory leaks
  //in the other test
  delete m_minHeap;
  m_minHeap = NULL;
  delete m_maxHeap;
  m_maxHeap = NULL;
}

template <class T>
MedianHeap<T>::MedianHeap(const MedianHeap<T>& otherH){
  m_totSize = otherH.m_totSize;
  m_maxCap = otherH.m_maxCap;
  m_max = otherH.m_max;
  m_min = otherH.m_min;
  m_median = otherH.m_median;
  less = otherH.less;
  greater = otherH.greater;
  m_maxHeap = new Heap<T>(*otherH.m_maxHeap);
  m_minHeap = new Heap<T>(*otherH.m_minHeap);
}

template <class T>
const MedianHeap<T>& MedianHeap<T>::operator=(const MedianHeap<T>& rhs){
  if(this != &rhs){
    //delete m_minHeap;
    //delete m_maxHeap;
    m_totSize = rhs.m_totSize;
    m_maxCap = rhs.m_maxCap;
    m_max = rhs.m_max;
    m_min = rhs.m_min;
    m_median = rhs.m_median;
    less = rhs.less;
    greater = rhs.greater;
    m_minHeap = rhs.m_minHeap;
    m_maxHeap = rhs.m_maxHeap;
  }

  return *this;
}

template <class T>
int MedianHeap<T>::size(){
  return m_totSize;
}

template <class T>
int MedianHeap<T>::capacity(){
  return m_maxCap;
}

template <class T>
void MedianHeap<T>::insert(const T& item){
  if(m_totSize == m_maxCap){
    throw out_of_range("cant insert");
  }

  //start in maxheap
  if(m_totSize == 0){
    m_min = item;
    m_max = item;
    m_maxHeap->insert(item);
  }

  else{
    //smaller numbers go into maxheap
    if(less(item, m_median)){
      //rebalance heap if size differ by more than one
      if(maxHeapSize() + 1 > minHeapSize() + 1){

	//maxheap bigger than minheap
	m_minHeap->insert(m_maxHeap->m_array[1]);
	m_maxHeap->deleteRoot();
      }
      m_maxHeap->insert(item);//now insert
    }

    //bigger numbers into minheap
    else if(greater(item, m_median)){
      
      if(minHeapSize() + 1 > maxHeapSize() + 1){
	m_maxHeap->insert(m_minHeap->m_array[1]);
	m_minHeap->deleteRoot();
      }
      m_minHeap->insert(item);
    }

    //if the item is same as current median
    //insert it into the maxheap
    else{
      
      if(maxHeapSize() + 1 > minHeapSize() + 1){
	m_minHeap->insert(m_maxHeap->m_array[1]);
	m_maxHeap->deleteRoot();
      }
      m_maxHeap->insert(item);
    }

    //adjust min and max
    if(less(item, m_min))
      m_min = item;
    if(greater(item, m_max))
      m_max = item;
  }

  //adjust median
  if(maxHeapSize() >= minHeapSize()){
    m_median = m_maxHeap->m_array[1];
  }
  else{
    m_median = m_minHeap->m_array[1];
  }

  m_totSize++;
}

template <class T>
T MedianHeap<T>::getMedian(){
  return m_median;
}

template <class T>
T MedianHeap<T>::getMin(){
  return m_min;
}

template <class T>
T MedianHeap<T>::getMax(){
  return m_max;
}

template <class T>
bool MedianHeap<T>::deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&)){
  if(m_totSize == 0){
    throw out_of_range("cant delete");
  }

  if(m_maxHeap->deleteItem(givenItem, equalTo) ||
     m_minHeap->deleteItem(givenItem, equalTo)){
    m_totSize--;
    
    //check to make sure delete did not ruin balance
    if(minHeapSize() > maxHeapSize() + 1){
      m_maxHeap->insert(m_minHeap->m_array[1]);
      m_minHeap->deleteRoot();
    }
    if(maxHeapSize() > minHeapSize() + 1){
      m_minHeap->insert(m_maxHeap->m_array[1]);
      m_maxHeap->deleteRoot();
    }

    //special cases

    //deleted all items in particular array
    if(maxHeapSize() == 0 && minHeapSize() != 0){
      m_min = m_minHeap->m_array[1];
      m_max = m_min;
    }
    if(maxHeapSize() != 0 && minHeapSize() == 0){
      m_min = m_maxHeap->m_array[1];
      m_max = m_min;
    }
    
    //deleted item was equal to min or max
    if(equalTo(givenItem, m_max)){
      m_max = m_minHeap->getNewMaxOrMin();
    }
    if(equalTo(givenItem, m_min)){
      m_min = m_maxHeap->getNewMaxOrMin();
    }

    //deleted item was the median
    if(equalTo(givenItem, m_median)){
      if(maxHeapSize() > minHeapSize()){
	m_median = m_maxHeap->m_array[1];
      }
      else{
	m_median = m_minHeap->m_array[1];
      }
    }
    return true; 
  }
  
  return false;
}

template <class T>
void MedianHeap<T>::dump(){
  cout << ".... MedianHeap::dump() ...." << endl;
  cout << endl;
  cout << "-------Max Heap---------" << endl;
  cout << "size = " << maxHeapSize() << ", " << "capacity = " << m_maxHeap->capacity() << endl;

  for(int i = 1; i <= maxHeapSize(); i++){
    cout << m_maxHeap->m_array[i] << endl;
  }
    
  cout << endl;
  
  cout << "-----Min Heap-----------" << endl;
  cout << "size = " << minHeapSize() << ", " << "capacity = " << m_maxHeap->capacity() << endl;

  for(int i = 1; i <= minHeapSize(); i++){
    cout << m_minHeap->m_array[i] << endl;
  }

  cout << endl;
  
  cout << "MIN = " << m_min << endl;
  cout << "MEDIAN = " << m_median << endl;
  cout << "MAX = " << m_max << endl;

  cout << endl;
}
template <class T>
int MedianHeap<T>::maxHeapSize(){
  return m_maxHeap->size();
}

template <class T>
int MedianHeap<T>::minHeapSize(){
  return m_minHeap->size();
}

template <class T>
T MedianHeap<T>::locateInMaxHeap(int pos){
  return m_maxHeap->locateInHeap(pos);
}

template <class T>
T MedianHeap<T>::locateInMinHeap(int pos){
  return m_minHeap->locateInHeap(pos);
}

#endif
