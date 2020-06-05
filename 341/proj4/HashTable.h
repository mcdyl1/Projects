#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

class HashTable{

public:

  HashTable(int n = 101);

  ~HashTable();

  HashTable(HashTable& other);

  const HashTable& operator=(HashTable& rhs);

  unsigned int hashCode(const char *str);

  void moveCluster(const char *str);

  void moveAll();

  void thirdTable();

  void insert(const char *str);

  bool find(const char *str);

  char* remove(const char *str);

  void dump();

  //grading functions
  bool isRehashing();

  int tableSize(int table=0);

  int size(int table=0);

  const char* at(int index, int table=0);

private:

  unsigned int sizeH;
  unsigned int sizeH2;
  unsigned int capH;
  unsigned int capH2;
  char ** H;
  char ** H2;
  bool reHashing;
  unsigned int hashIndex;
  unsigned int probeSize;
  static char * const DELETED;
  
};

#endif

