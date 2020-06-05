#include "HashTable.h"
#include "primes.h"
#include <stdexcept>
#include <string.h>
#include <cstring>
#include <iostream>
using namespace std;

char * const HashTable::DELETED = (char *) &DELETED;

HashTable::HashTable(int n){
  if(roundUpPrime(n) == 0){
    throw out_of_range("REQUESTED SIZE IS TO LARGE");
  }
  else{
    capH = roundUpPrime(n);
  }
  sizeH = 0;
  sizeH2 = 0;
  capH2 = 0;
  reHashing = false;
  hashIndex = 0;
  H = NULL;
  H = new char*[capH];
  H2 = NULL;
  probeSize = 1;

  for(unsigned int i = 0; i < capH; i++){
    H[i] = NULL;
  }
}

HashTable::~HashTable(){
  if(H != NULL){
    for(unsigned int i = 0; i < capH; i++){
      if(H[i] != DELETED){
	free(H[i]);
	H[i] = NULL;
      }
      else{
	H[i] = NULL;
      }
    }
    delete [] H;
    H = NULL;
  }
  
  if(H2 != NULL){
    for(unsigned int i = 0; i < capH2; i++){
      if(H2[i] != DELETED){
	free(H2[i]);
	H2[i] = NULL;
      }
      else{
	H2[i] = NULL;
      }
    }
    delete [] H2;
    H2 = NULL;
  }
}

HashTable::HashTable(HashTable& other){
  if(other.reHashing == false){
    sizeH = other.sizeH;
    capH = other.capH;
    hashIndex = other.hashIndex;
    probeSize = other.probeSize;
    H = new char*[capH];
    for(unsigned int i = 0; i < capH; i++){
      if(other.H[i] != DELETED and other.H[i] != NULL)
	H[i] = strdup(other.H[i]);
      else if(H[i] == DELETED){
	H[i] = DELETED;
      }
      else{
	H[i] = NULL;
      }
    }
  }
  else{
    other.reHashing = false;
    other.moveAll();
    sizeH = other.sizeH;
    capH = other.capH;
    hashIndex = other.hashIndex;
    probeSize = other.probeSize;
    H = new char*[capH];
    for(unsigned int i = 0; i < capH; i++){
      if(other.H[i] != DELETED and other.H[i] != NULL)
        H[i] = strdup(other.H[i]);
      else if(other.H[i] == DELETED){
        H[i] = DELETED;
      }
      else{
        H[i] = NULL;
      }
    }
  }
}

const HashTable& HashTable::operator=(HashTable& rhs){
  if(this != &rhs){
    delete [] H;
    H = NULL;
    delete [] H2;
    H2 = NULL;
    if(rhs.reHashing == false){
      sizeH = rhs.sizeH;
      capH = rhs.capH;
      hashIndex = rhs.hashIndex;
      probeSize = rhs.probeSize;
      H = new char*[capH];
      for(unsigned int i = 0; i < capH; i++){
	if(rhs.H[i] != DELETED and rhs.H[i] != NULL)
	  H[i] = strdup(rhs.H[i]);
	else if(rhs.H[i] == DELETED){
	  H[i] = DELETED;
	}
	else{
	  H[i] = NULL;
	}
      }
    }
    else{
      rhs.reHashing = false;
      rhs.moveAll();
      sizeH = rhs.sizeH;
      capH = rhs.capH;
      hashIndex = rhs.hashIndex;
      probeSize = rhs.probeSize;
      H = new char*[capH];
      for(unsigned int i = 0; i < capH; i++){
	if(rhs.H[i] != DELETED and rhs.H[i] != NULL)
	  H[i] = strdup(rhs.H[i]);
	else if(rhs.H[i] == DELETED){
	  H[i] = DELETED;
	}
	else{
	  H[i] = NULL;
	}
      }
    }
  }
  return *this;
}

unsigned int HashTable::hashCode(const char *str){
  unsigned int val = 0;
  const unsigned int thirtyThree = 33; //magic number from textbook

  int i = 0;
  while(str[i] != '\0'){
    val = val * thirtyThree + str[i];
    i++;
  }
  return val;
}

void HashTable::moveCluster(const char *str){
  if(H2 == NULL){//allocate second table if needed
    capH2 = roundUpPrime(sizeH*4);
    if(capH2 == capH){
      capH2 = roundUpPrime(capH2+1);
    }
    if(capH2 < 101 or capH2 > 199999){
      throw out_of_range("table size too big or too small");
    }
    H2 = new char*[capH2];
    for(unsigned int i = 0; i < capH2; i++){
      H2[i] = NULL;
    }
  }

  //finding beginning of cluster
  //something about this causes test 4 to be off
  unsigned int clusterStart = 0;
  clusterStart = hashCode(str) % capH;
  
  if(clusterStart == 0){
    if(H[capH - 1] == NULL){
      clusterStart = 0;
    }
    else{
      clusterStart = (capH - 1);
      while(H[clusterStart] != NULL){
	clusterStart--;
      }
    }
  }
  else{
    while(H[clusterStart] != NULL){
      if(clusterStart == 0 and H[capH - 1] == NULL){
	clusterStart = 0;
	break;
      }
      else if(clusterStart == 0 and H[capH - 1] != NULL){
	clusterStart = (capH - 1);
      }
      clusterStart--;
    }
  }

  if(H[clusterStart] == NULL){
    clusterStart++;
  }
  
  //loop through til end of cluster and rehash into second table
  while(H[clusterStart] != NULL and H[clusterStart] != DELETED){
    probeSize = 0;
    hashIndex = hashCode(H[clusterStart]) % capH2;
    while(H2[hashIndex] != NULL and H2[hashIndex] != DELETED){
      probeSize++;
      hashIndex++;
      if(hashIndex == capH2)
	hashIndex = 0;
    }
    
    probeSize++;
    H2[hashIndex] = H[clusterStart];
    H[clusterStart] = NULL;
    sizeH2++;
    sizeH--;
    if(probeSize >= 10){
      reHashing = false;
    }
    
    clusterStart++;
    if(clusterStart == capH){
      clusterStart = 0;
    }
  }

  //if rehashing was triggered, after all values moved
  //move all into third table
  if(reHashing == false){
    thirdTable();
  }

}

//old table below 3%
void HashTable::moveAll(){
  for(unsigned int i = 0; i < capH; i++){
    if(H[i] != DELETED and H[i] != NULL){
      hashIndex = hashCode(H[i]) % capH2;
      while(H2[hashIndex] != NULL and H2[hashIndex] != DELETED){
	hashIndex++;
	if(hashIndex == capH2)
	  hashIndex = 0;
      }
      H2[hashIndex] = H[i];
      sizeH2++;
      H[i] = NULL;
      sizeH--;
    }
  }
  
  delete[] H;
  H = NULL;

  H = H2;
  sizeH = sizeH2;
  capH = capH2;
  capH2 = 0;
  sizeH2 = 0;
  H2 = NULL;
}

//second table causes rehashing as well
void HashTable::thirdTable(){
  unsigned int capH3 = roundUpPrime((sizeH+sizeH2)*4);
  unsigned int sizeH3 = 0;
  if(capH3 < 101 or capH3 > 199999){
    throw out_of_range("table size too big or too small");
  }
  char **H3;
  H3 = new char*[capH3];
  for(unsigned int i = 0; i < capH3; i++){
    H3[i] = NULL;
  }

  for(unsigned int i = 0; i < capH2; i++){
    if(H2[i] != DELETED and H2[i] != NULL){
      hashIndex = hashCode(H2[i]) % capH3;
      while(H3[hashIndex] != NULL and H3[hashIndex] != DELETED){
	hashIndex++;
	if(hashIndex == capH3)
	  hashIndex = 0;
      }
      H3[hashIndex] = H2[i];
      sizeH3++;
      H2[i] = NULL;
      sizeH2--;
    }
  }

  delete [] H2;
  H2 = NULL;

  for(unsigned int i = 0; i < capH; i++){
    if(H[i] != DELETED and H[i] != NULL){
      hashIndex = hashCode(H[i]) % capH3;
      while(H3[hashIndex] != NULL and H3[hashIndex] != DELETED){
        hashIndex++;
        if(hashIndex == capH3)
          hashIndex = 0;
      }
      H3[hashIndex] = H[i];
      sizeH3++;
      H[i] = NULL;
      sizeH--;
    }
  }
  delete [] H;
  H = NULL;

  H = H3;
  sizeH = sizeH3;
  capH = capH3;
  capH2 = 0;
  sizeH2 = 0;
  H3 = NULL;

}

void HashTable::insert(const char *str){
  if(sizeH > capH/2){//load factor > .5
    reHashing = true;
  }
  
  //when program returns from these two function calls will only be one table
  //program will cont. like normal with str and one table and rehashing = false
  if(reHashing == true and sizeH2 > capH2/2){//second table load factor >.5
    reHashing = false;
    thirdTable();//form both tables into one
  }
  if(reHashing == true and sizeH < .03*(sizeH+sizeH2)){//size of first table below 3%
    reHashing = false;
    moveAll();//move all thats left in old table to new
  }

  bool isDuplicate = false;
  if(reHashing == true){
    hashIndex = hashCode(str) % capH;
    
    while(H[hashIndex] != NULL){
      //use short circuit evaluation
      if(H[hashIndex] != DELETED and strcmp(H[hashIndex], str) == 0){
	isDuplicate = true;
	break;//no need to look further
      }
      else{
	hashIndex++;
	if(hashIndex == capH){
	  hashIndex = 0;
	}
      }
    }
    
    moveCluster(str); //move cluster just looked at in old table

    if(isDuplicate == false and reHashing == true){//if not found in old table search the new one
      hashIndex = hashCode(str) % capH2;
      probeSize = 0;
      
      while(H2[hashIndex] != NULL){
	probeSize++;
	
	if(H2[hashIndex] != DELETED and strcmp(H2[hashIndex], str) == 0){
	  isDuplicate = true;
	  if(probeSize >= 10){
	    //only need to check probe size if duplicate is found.
	    //if one is not found, actual insert will find long probe
	    reHashing = false;
	    thirdTable();
	  }
	  break;//no need to look further
	}
	else{
	  hashIndex++;
	  if(hashIndex == capH2)
	    hashIndex = 0;
	}
      }
    }
    
    //if not found in either table go ahead and insert and third table was not triggerd
    if(isDuplicate == false and reHashing == true){
      hashIndex = hashCode(str) % capH2;
      probeSize = 0;
      
      while(H2[hashIndex] != NULL and H2[hashIndex] != DELETED){
	probeSize++;
	hashIndex++;
	if(hashIndex == capH2)
	  hashIndex = 0;
      }
      probeSize++;
      //insert first then move everything
      H2[hashIndex] = strdup(str);
      sizeH2++;
      if(probeSize >= 10){
	reHashing = false;
	thirdTable();
      }
    }
  }
  
  if(reHashing == false){
    isDuplicate = false;//reset probe and duplicate
    hashIndex = hashCode(str) % capH;
    probeSize = 0;

    //search table to see if string already exist
    while(H[hashIndex] != NULL){
      probeSize++;
      if(H[hashIndex] != DELETED and strcmp(H[hashIndex], str) == 0){
	isDuplicate = true;
	if(probeSize >= 10){
	  reHashing = true;
	  moveCluster(str);
	}
	break;
      }
      else{
	hashIndex++;
	if(hashIndex == capH)
	  hashIndex = 0;
      }
    }

    if(isDuplicate == false and reHashing == false){
      hashIndex = hashCode(str) % capH;
      probeSize = 0;
      
      while(H[hashIndex] != NULL and H[hashIndex] != DELETED){
	probeSize++;
	hashIndex++;
	if(hashIndex == capH)
	  hashIndex = 0;
      }
      probeSize++;
      H[hashIndex] = strdup(str);
      sizeH++;
      //had to look at 10 or more slots until found an empty one
      if(probeSize >= 10){
	reHashing = true;
	moveCluster(str);
      }
    }
  }
}

bool HashTable::find(const char *str){
  if(sizeH > capH/2){//load factor > .5
    reHashing = true;
    if(capH2 == capH){
      capH2 = roundUpPrime(capH2+1);
    }
    if(capH2 < 101 or capH2 > 199999){
      throw out_of_range("table size too big or too small");
    }
    H2 = new char*[capH2];
    for(unsigned int i = 0; i < capH2; i++){
      H2[i] = NULL;
    }
  }

  if(reHashing == true and sizeH2 > capH2/2){
    reHashing = false;
    thirdTable();
  }
  if(reHashing == true and sizeH < .03*(sizeH+sizeH2)){
    reHashing = false;
    //move old table into new table
    moveAll();
  }

  if(reHashing == true){
    hashIndex = hashCode(str) % capH;

    while(H[hashIndex] != NULL){
      if(H[hashIndex] != DELETED and strcmp(H[hashIndex], str) == 0){
	moveCluster(str);
	return true;
      }
      hashIndex++;
      if(hashIndex == capH)
	hashIndex = 0;
    }
    moveCluster(str);

    hashIndex = hashCode(str) % capH2;
    probeSize = 0;
    while(H2[hashIndex] != NULL){
      probeSize++;
      if(H2[hashIndex] != DELETED and strcmp(H2[hashIndex], str) == 0){
	if(probeSize >= 10){
	  reHashing = false;
	  thirdTable();
	}
	return true;
      }
      hashIndex++;
      if(hashIndex == capH2)
	hashIndex = 0;
    }
    
    probeSize++;
    if(probeSize >= 10){
      reHashing = false;
      thirdTable();
    }
    //return false;
  }

  if(reHashing == false){
    probeSize = 0;
    hashIndex = hashCode(str) % capH;

    while(H[hashIndex] != NULL){
      probeSize++;
      if(H[hashIndex] != DELETED and strcmp(H[hashIndex], str) == 0){
	if(probeSize >= 10){
	  reHashing = true;
	  moveCluster(str);
	}
	return true;
      }
      hashIndex++;
      if(hashIndex == capH)
	hashIndex = 0;
    }
    
    probeSize++;
    if(probeSize >= 10){
      reHashing = true;
      moveCluster(str);
    }
    //return false;
  }

  return false;
}

char* HashTable::remove(const char *str){
  if(sizeH > capH/2){//load factor > .5
    reHashing = true;
    if(capH2 == capH){
      capH2 = roundUpPrime(capH2+1);
    }
    if(capH2 < 101 or capH2 > 199999){
      throw out_of_range("table size too big or too small");
    }
    H2 = new char*[capH2];
    for(unsigned int i = 0; i < capH2; i++){
      H2[i] = NULL;
    }
  }

  if(reHashing == true and sizeH2 > capH2/2){
    reHashing = false;
    thirdTable();
  }

  if(reHashing == true and sizeH < .03*(sizeH+sizeH2)){
    reHashing = false;
    //move old table into new table
    moveAll();
  }

  if(reHashing == true){
    probeSize = 0;
    hashIndex = hashCode(str) % capH;
    while(H[hashIndex] != NULL){
      if(H[hashIndex] != DELETED and strcmp(H[hashIndex], str) == 0){
	char* temp = H[hashIndex];
	H[hashIndex] = DELETED;
	sizeH--;
	moveCluster(str);
	return temp;
      }
      hashIndex++;
      if(hashIndex == capH){
	hashIndex = 0;
      }
    }
    
    moveCluster(str);
    hashIndex = hashCode(str) % capH2;
    
    while(H2[hashIndex] != NULL){
      probeSize++;
      if(H2[hashIndex] != DELETED and strcmp(H2[hashIndex], str) == 0){
	char* temp = H2[hashIndex];
	H2[hashIndex] = DELETED;
	sizeH2--;
	if(probeSize >= 10){
	  reHashing = false;
	  thirdTable();
	  return temp;
	}
	return temp;
      }
      else{
	hashIndex++;
	if(hashIndex == capH2){
	  hashIndex = 0;
	}
      }
    }
    
    probeSize++;
    if(probeSize >= 10){
      reHashing = false;
      thirdTable();
      return NULL;
    }
    return NULL;
  }

  if(reHashing == false){
    probeSize = 0;
    hashIndex = hashCode(str) % capH;
    
    while(H[hashIndex] != NULL){
      probeSize++;
      
      if(H[hashIndex] != DELETED and strcmp(H[hashIndex], str) == 0){
	if(probeSize >= 10){
	  reHashing = true;
	  char* temp = H[hashIndex];
	  H[hashIndex] = DELETED;
	  sizeH--;
	  moveCluster(str);
	  return temp;
	}
	char* temp = H[hashIndex];
	H[hashIndex] = DELETED;
	sizeH--;
	return temp;
      }
      
      else{
	hashIndex++;
	if(hashIndex == capH){
	  hashIndex = 0;
	}
      }
    }

    probeSize++;
    if(probeSize >= 10){
      reHashing = true;
      moveCluster(str);
      return NULL;
    }
   
    //return NULL;
  }
  return NULL;
}

void HashTable::dump(){
  if(H != NULL){
    cout << "HashTable #1: "
	 << "size = " << sizeH
	 << " tableSize = " << capH << endl;
    for(unsigned int i = 0; i < capH; i++){
      cout << "H1[ " << i << "] = ";
      if(H[i] == NULL){
	cout << "NULL" << endl;
      }
      else if(H[i] == DELETED){
	cout << "DELETED" << endl;
      }
      else{
	cout << H[i] << " (" << hashCode(H[i]) % capH << ")"  << endl;
      }
    }
  }

  cout << endl;
  cout << endl;
  
  if(H2 != NULL){
    cout << "HashTable #2: "
	 << "size = " << sizeH2
	 << " tableSize = " << capH2 << endl;
    
    for(unsigned int i = 0; i < capH2; i++){
      cout << "H2[ " << i << "] = ";
      if(H2[i] == NULL){
        cout << "NULL" << endl;
      }
      else if(H2[i] == DELETED){
        cout << "DELETED" << endl;
      }
      else{
        cout << H2[i] << " (" << hashCode(H2[i]) % capH2 << ")"  << endl;
      }
    }
  }
}

//grading functions
bool HashTable::isRehashing(){
  return reHashing;
}

int HashTable::tableSize(int table){
  if(table == 0)
    return capH;
  if(table == 1)
    return capH2;

  return 0;
}

int HashTable::size(int table){
  if(table == 0)
    return sizeH;
  if(table == 1)
    return sizeH2;

  return 0;
}

const char* HashTable::at(int index, int table){
  if(index < 0 or index > tableSize(table)){
    throw out_of_range("index not in range");
  }
  else{
    if(table == 0){
      if(H[index] != DELETED)
	return H[index];
      if(H[index] == DELETED)
	return NULL;
    }
    if(table == 1){
      if(H2[index] != DELETED)
	return H2[index];
      if(H2[index] == DELETED)
	return NULL;
    }
  }
  return NULL;
}

