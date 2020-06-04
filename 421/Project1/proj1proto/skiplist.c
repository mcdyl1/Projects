#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

struct MsgNode{
  unsigned char *msg;
  long msgLen;
  struct MsgNode *next;
};

struct SkipNode{
  unsigned long id;
  struct MsgNode *MsgListHead;
  struct SkipNode **forward;
};

struct SkipList{
  unsigned int CurrentLevel;
  unsigned int MaxLevel;
  unsigned int LevelProb;
  struct SkipNode *header;
};

static struct SkipList *list;
static unsigned long MAX_ID = ULONG_MAX;
static unsigned long MIN_ID = 0;
static unsigned int next_random = 9001;
///////////////////////////////////////////////////

static unsigned int generate_random_int(void){
  next_random = next_random * 1103515245 + 12345;
  return (next_random / 65536) % 32768;
}

static void seed_random(unsigned int seed){
  next_random = seed;
}
///////////////////////////////////////////////////

int get_random_level(){
  int level = 1;
  while(generate_random_int() < (32767 / list->LevelProb) && level < list->MaxLevel){
    level++;
  }
  return level;
}

long mbx421_init(unsigned int ptrs, unsigned int prob){
  if(prob != 2 && prob != 4 && prob != 8 && prob != 16){
    printf("Prob value is not acceptable\n");
    return 1;
  }
  if(ptrs <= 0){
    printf("ptrs value must be greater than 0\n");
    return 1;
  }
  if(list != NULL){
    printf("A skiplist has already been made\n");
    return 1;
  }
  
  seed_random(time(0));
  int i;
  list = malloc(sizeof(struct SkipList));
  list->MaxLevel = ptrs;
  list->LevelProb = prob;
  list->CurrentLevel = 1;

  struct SkipNode *header = malloc(sizeof(struct SkipNode));
  list->header = header;
  header->id = MAX_ID;
  header->MsgListHead = NULL;//no messages in header of skiplist
  header->forward = malloc(sizeof(struct SkipNode *) * (ptrs + 1));

  for(i = 0; i <= ptrs; i++){
    header->forward[i] = list->header;
  }

  return 0;
}

long mbx421_shutdown(void){
  int i;
  if(list != NULL){
    struct SkipNode *x = list->header->forward[1];
    struct SkipNode *temp;
    while( x != list->header){
      struct MsgNode *n = x->MsgListHead;
      struct MsgNode *next;
      while(n != NULL){
	next = n->next;
	free(n->msg);
	free(n);
	n = next;
      }
      temp = x->forward[1];
      free(x->forward);
      free(x);
      x = temp;
    }
    free(list->header->forward);
    free(list->header);
    free(list);
    list = NULL;
  }
  return 0;
}

long mbx421_create(unsigned long id){
  if(id == MIN_ID || id == MAX_ID){
    printf("Not a proper id\n");
    return 1;
  }
  struct SkipNode *update[list->MaxLevel + 1];
  struct SkipNode *x = list->header;
  int i, level;

  for(i = list->CurrentLevel; i >= 1; i--){
    while(x->forward[i]->id < id){
      x = x->forward[i];
    }
    update[i] = x;
  }
  x = x->forward[1];

  if(x->id == id){
    printf("A mailbox with that id already exist\n");
    return 1;
  }
  else{
    level = get_random_level();
    if(level > list->CurrentLevel){
      for(i = list->CurrentLevel + 1; i < level + 1; i++){
	update[i] = list->header;
      }
      list->CurrentLevel = level;
    }

    x = malloc(sizeof(struct SkipNode));
    x->id = id;
    x->MsgListHead = NULL;
    x->forward = malloc(sizeof(struct SkipNode*) * (level + 1));
    for(i = 1; i <= level; i++){
      x->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = x;
    }
  }
  return 0;
}

long mbx421_destroy(unsigned long id){
  struct SkipNode *update[list->MaxLevel + 1];
  struct SkipNode *x = list->header;
  int i;

  for(i = list->CurrentLevel; i >= 1; i--){
    while(x->forward[i]->id < id){
      x = x->forward[i];
    }
    update[i] = x;
  }
  x = x->forward[1];

  if(x->id == id){
    for(i = 1; i <= list->CurrentLevel; i++){
      if(update[i]->forward[i] != x){
	break;
      }
      update[i]->forward[i] = x->forward[i];
    }
    struct MsgNode *n = x->MsgListHead;
    struct MsgNode *tempn;
    while(n != NULL){
      tempn = n->next;
      free(n->msg);
      free(n);
      n = tempn;
    }
    free(x->forward);
    free(x);//call a function that frees the node's memory

    while(list->CurrentLevel > 1 && list->header->forward[list->CurrentLevel] == list->header){
      list->CurrentLevel--;
    }
    return 0;
  }

  printf("Mailbox to delete does not exist\n");
  return 1;
}

long mbx421_count(unsigned long id){
  struct SkipNode *x = list->header;
  int i;
  int count = 0;
  for(i = list->CurrentLevel; i >= 1; i--){
    while(x->forward[i]->id < id){
      x = x->forward[i];
    }
  }
  x = x->forward[1];
  if(x->id == id){
    struct MsgNode *n = x->MsgListHead;
    while(n != NULL){
      count++;
      n = n->next;
    }
    return count;
  }

  printf("mailbox to count does not exist\n");
  return 1;
}

long mbx421_send(unsigned long id, unsigned char *msg, long len){
  struct SkipNode *x = list->header;
  int i;
  
  for(i = list->CurrentLevel; i >= 1; i--){
    while(x->forward[i]->id < id){
      x = x->forward[i];
    }
  }
  x = x->forward[1];
  
  if(x->id == id){
    struct MsgNode *newMsg = malloc(sizeof(struct MsgNode));
    struct MsgNode *n = x->MsgListHead;

    newMsg->msgLen = len;
    printf("Size: %ld\n", newMsg->msgLen);
    newMsg->msg = malloc(sizeof(unsigned char) * len);
    memcpy(newMsg->msg, msg, len);
    newMsg->next = NULL;

    if(x->MsgListHead == NULL){
      x->MsgListHead = newMsg;
      printf("First message inserted\n");
      return 0;
    }
    while(n->next != NULL){
      n = n->next;
    }
    
    n->next = newMsg;
    printf("Message inserted successfully\n");
  }
  return 0;
}

void skiplist_print(){
  if(list != NULL){
    for(int i = 1; i <= list->CurrentLevel; i++){
      struct SkipNode *x = list->header->forward[i];
      printf("Level %d: ", i);

      while(x != list->header){
	printf("%d ", x->id);
	//x = x->forward[i];
	if(x->id == 1){
	  if(x->MsgListHead != NULL){
	    //struct MsgNode *new_node = (struct MsgNode*) malloc(sizeof(struct MsgNode));
	    struct MsgNode *last = x->MsgListHead;

	    while(last != NULL){
	      for(int j = 0; j < last->msgLen; j++){
		printf("%c", last->msg[j]);
	      }
	      last = last->next;
	    }
	  }
	}
	x = x->forward[i];
      }
      printf("\n");
    }
  }
  else{
    printf("no list to print\n");
  }
}

int main(){
  printf("INITIALIZING MAILBOX SYSTEM\n");
  long status = mbx421_init(4,2);
  printf("INSERTING MAILBOXES, 1, 3, 90, AND 40\n");
  status = mbx421_create(1);
  status = mbx421_create(3);
  status = mbx421_create(90);
  status = mbx421_create(40);
  printf("SENDING TWO MESSAGES TO MAILBOX 1\n");
  status = mbx421_send(1, "dog", 3);
  status = mbx421_send(1, "hello", 8);
  skiplist_print();

  printf("COUNTING NUMBER OF MESSAGES IN MAILBOX 1\n");
  status = mbx421_count(1);
  printf("Count of messages in mailbox 1: %ld\n", status);
  printf("DESTROYING MAILBOX 1\n");
  status = mbx421_destroy(1);
  printf("ATTEMPTING TO COUNT MESSAGES IN MAILBOX 1 AFTER DELETE\n");
  status = mbx421_count(1);
  status = mbx421_create(1);
  status = mbx421_send(1, "whatupdawg\0", 10);
  status = mbx421_count(1);
  skiplist_print();
  status = mbx421_shutdown();
  
  return 0;
}

