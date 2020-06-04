#ifndef PROJ2PROTO
#define PROJ2PROTO

struct SkipNode{
  unsigned int process_id;
  unsigned int count;
  struct SkipNode **forward;
};

struct SkipList{
  unsigned int CurrentLevel;
  unsigned int MaxLevel;
  unsigned int LevelProb;
  struct SkipNode *header;
};

#define NUM_OF_SYSCALLS 436
#define PROB 2
#define MAX_LEVEL 31
#define MAX_ID UINT_MAX;

extern struct SkipList** sbx421_get_array(void);

#endif
