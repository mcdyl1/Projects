#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "proj2proto.h"

static unsigned int next_random = 90001;
static struct SkipList *syscalls[NUM_OF_SYSCALLS + 1];

static unsigned int generate_random_int(void){
  next_random = next_random * 1103515245 + 12345;
  return (next_random / 65536) % 32768;
}

static unsigned seed_random(unsigned int seed){
  next_random = seed;
}

int get_random_level(){
  int level = 1;
  while(generate_random_int() < (32767/ 2) && level < MAX_LEVEL){
    level++;
  }

  printf("level: %d\n", level);
  return level;
}

struct SkipList** sbx421_get_array(void){
  return syscalls;
}

void init_syscall_list(unsigned long nr){
  int i;
  
  sbx421_get_array()[nr] = malloc(sizeof(struct SkipList));
  syscalls[nr]->MaxLevel = MAX_LEVEL;
  syscalls[nr]->LevelProb = PROB;
  syscalls[nr]->CurrentLevel = 1;

  struct SkipNode *header = malloc(sizeof(struct SkipNode));
  syscalls[nr]->header = header;
  header->process_id = MAX_ID;
  header->forward = malloc(sizeof(struct SkipNode *) * (MAX_LEVEL + 1));

  for(i = 0; i <= MAX_LEVEL; i++){
    header->forward[i] = syscalls[nr]->header;
  }
}

long sbx421_block(pid_t proc, unsigned long nr){
  if(sbx421_get_array()[nr] == NULL){
    printf("IN HERE\n");
    init_syscall_list(nr);
  }

  struct SkipList *list = sbx421_get_array()[nr];
  struct SkipNode *update[list->MaxLevel + 1];
  struct SkipNode *x = list->header;
  int level, i;

  for(i = list->CurrentLevel; i >= 1; i--){
    while(x->forward[i]->process_id < proc){
      x = x->forward[i];
    }
    update[i] = x;
  }

  x = x->forward[1];

  if(x->process_id == proc){
    printf("Process is already blocked by this system call\n");
    return -1;
  }
  else{
    level = get_random_level();
    if(level > list->CurrentLevel){
      for(i = list->CurrentLevel + 1; i <= level; i++){
	update[i] = list->header;
      }
      list->CurrentLevel = level;
    }

    x = malloc(sizeof(struct SkipNode));
    x->process_id = proc;
    x->forward = malloc(sizeof(struct SkipNode*) * (level + 1));
    for(i = 1; i <= level; i++){
      x->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = x;
    }
  }
  
  return 0;
}

long sbx421_unblock(pid_t proc, unsigned long nr){
  struct SkipNode *update[syscalls[nr]->MaxLevel + 1];
  struct SkipNode *x = syscalls[nr]->header;
  int i;

  for(i = syscalls[nr]->CurrentLevel; i >= 1; i--){
    while(x->forward[i]->process_id < proc){
      x = x->forward[i];
    }
    update[i] = x;
  }

  x = x->forward[1];

  if(x->process_id == proc){
    for(i = 1; i <= syscalls[nr]->CurrentLevel; i++){
      if(update[i]->forward[i] != x){
	break;
      }
      update[i]->forward[i] = x->forward[i];
    }

    free(x->forward);
    x->forward = NULL;
    free(x);
    x = NULL;

    while(syscalls[nr]->CurrentLevel > 1 && syscalls[nr]->header->forward[syscalls[nr]->CurrentLevel] == syscalls[nr]->header){
      syscalls[nr]->CurrentLevel--;
    }

    return 0;
  }

  printf("Process ID to unblock is not blocked\n");
  return -1;
}

long sbx421_count(pid_t proc, unsigned long nr){
  //search system call list to see if process exist, return count.
  return 0;
}

long sbx421_shutdown(void){
  int i;

  for(i = 0; i < NUM_OF_SYSCALLS; i++){
    if(syscalls[i] != NULL){
      struct SkipNode *x = syscalls[i]->header->forward[1];
      struct SkipNode *temp;

      while(x != syscalls[i]->header){
	temp = x->forward[1];
	free(x->forward);
	free(x);
	x = temp;
      }

      free(syscalls[i]->header->forward);
      free(syscalls[i]->header);
      free(syscalls[i]);
    }
  }
  return 0;
}

void print_syscall_list(unsigned long nr){
  int i;
  for(i = 0; i < NUM_OF_SYSCALLS; i++){
    if(syscalls[i] != NULL){
      struct SkipNode *x = syscalls[i]->header;
      printf("System call %d blocked list\n", i);
      while(x && x->forward[1] != syscalls[i]->header){
	printf("%d->", x->forward[1]->process_id);
	x = x->forward[1];
      }
      printf("NIL\n");
    }
  }
}

int main(){
  seed_random(time(0));
  
  /* sbx421_block(23, 67);
  sbx421_block(54, 67);
  print_syscall_list(67);

  sbx421_unblock(23, 67);
  sbx421_unblock(23, 67);
  sbx421_unblock(54, 67);


  print_syscall_list(67);

  sbx421_block(54, 67);
  print_syscall_list(67);

  sbx421_shutdown();
  */

  get_random_level();
  return 0;
}
