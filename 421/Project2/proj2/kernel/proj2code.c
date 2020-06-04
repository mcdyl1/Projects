#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/random.h>
#include <linux/cred.h>
#include <linux/proj2.h>

int get_random_level(void){
  int level = 1;
  int i = 0;
  while(i <= 0){
    get_random_bytes(&i, sizeof(i));
    i = i % 32;
  }
  
  level = abs(i);
  return level;
}

//must add 1 so goes from 0-437
static struct SkipList *syscalls[NUM_OF_SYSCALLS + 1];

//accessor function
struct SkipList** sbx421_get_array(void){
  return syscalls;
}

//called if a system calls list of PIDs has not been initialized
void init_syscall_list(unsigned long nr){
  int i;
  
  syscalls[nr] = kmalloc(sizeof(struct SkipList), GFP_KERNEL);
  syscalls[nr]->MaxLevel = MAX_LEVEL;
  syscalls[nr]->LevelProb = PROB;
  syscalls[nr]->CurrentLevel = 1;

  struct SkipNode *header = kmalloc(sizeof(struct SkipNode), GFP_KERNEL);
  syscalls[nr]->header = header;
  header->process_id = MAX_ID;
  header->forward = kmalloc(sizeof(struct SkipNode *) * (MAX_LEVEL + 1), GFP_KERNEL);

  for(i = 0; i <= MAX_LEVEL; i++){
    header->forward[i] = syscalls[nr]->header;
  }
  
}


SYSCALL_DEFINE2(sbx421_block, pid_t, proc, unsigned long, nr){
  //tried to block another process while not root
  if(proc > 0 && current_cred()->uid.val != 0){
    //printk("block: tried to block another process while not root\n");
    return -EACCES;
  }
  //PID passed in was not valid
  if(proc < 0 || proc > MAX_ID){
    //printk("block: proc passed in is not valid\n");
    return -EINVAL;
  }
  //system call number passed in was not valid
  if(nr < 0 || nr > NUM_OF_SYSCALLS){
    //printk("block: nr passed in is not valid\n");
    return -EINVAL;
  }

  //PID of 0 passed in, means block current PID
  if(proc == 0){
    //printk("block: block current process\n");
    proc = current->pid;
  }
  //system call list not allocated yet
  if(syscalls[nr] == NULL){
    //printk("block: that system call's list is still NULL\n");
    init_syscall_list(nr);
  }

  //skiplist code
  struct SkipNode *update[MAX_LEVEL + 1];
  struct SkipNode *x = syscalls[nr]->header;
  int level, i;

  for(i = syscalls[nr]->CurrentLevel; i >= 1; i--){
    while(x->forward[i]->process_id < proc){
      x = x->forward[i];
    }
    update[i] = x;
  }
  
  x = x->forward[1];

  if(x->process_id == proc){
    return -EEXIST;
  }
  else{
    level = get_random_level();
    if(level > syscalls[nr]->CurrentLevel){
      for(i = syscalls[nr]->CurrentLevel + 1; i <= level; i++){
	update[i] = syscalls[nr]->header;
      }
      syscalls[nr]->CurrentLevel = level;
    }

    x = kmalloc(sizeof(struct SkipNode), GFP_KERNEL);
    x->process_id = proc;
    x->count = 0;
    x->forward = kmalloc(sizeof(struct SkipNode*) * (level + 1), GFP_KERNEL);
    for(i = 1; i <= level; i++){
      x->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = x;
    }
  }
  
  return 0;
}

SYSCALL_DEFINE2(sbx421_unblock, pid_t, proc, unsigned long, nr){
  //must be root to call unblock
  if(current_cred()->uid.val != 0){
    //printk("unblock: Must be root to run unblock system call\n");
    return -EACCES;
  }
  //PID must be greater than 0
  if(proc <= 0){
    //printk("unblock: Proc must be greater than 0\n");
    return -EINVAL;
  }
  //system call number not valid
  if(nr < 0 || nr > NUM_OF_SYSCALLS){
    //printk("unblock: nr value passed in is not valid\n");
    return -EINVAL;
  }
  //system call has no PIDs blocked
  if(syscalls[nr] == NULL){
    //printk("unblock: This system call's list is empty\n");
    return -ENOENT;
  }

  //skiplist code
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

    kfree(x->forward);
    x->forward = NULL;
    x->count = 0;
    kfree(x);
    x = NULL;

    while(syscalls[nr]->CurrentLevel > 1 && syscalls[nr]->header->forward[syscalls[nr]->CurrentLevel] == syscalls[nr]->header){
      syscalls[nr]->CurrentLevel--;
    }

    return 0;
  }

  //printk("unblock: Did not find this process on the system calls list\n");
  return -ENOENT;
}

SYSCALL_DEFINE2(sbx421_count, pid_t, proc, unsigned long, nr){
  //must be root to call count system call
  if(current_cred()->uid.val != 0){
    //printk("count: Must be root to run count system call\n");
    return -EACCES;
  }
  //PID must be greater than 0
  if(proc <= 0){
    //printk("count: Proc must be greater than 0\n");
    return -EINVAL;
  }
  //system call number not valid
  if(nr < 0 || nr > NUM_OF_SYSCALLS){
    //printk("count: nr value passed in is invalid\n");
    return -EINVAL;
  }
  //no PIDs blocked by that system call
  if(syscalls[nr] == NULL){
    //printk("count: This system call's list is empty\n");
    return -ENOENT;
  }

  //skiplist code
  struct SkipNode *x = syscalls[nr]->header;
  int i;

  for(i = syscalls[nr]->CurrentLevel; i >= 1; i--){
    while(x->forward[i]->process_id < proc)
      x = x->forward[i];
  }

  x = x->forward[1];

  if(x->process_id == proc){
    return x->count;
  }

  //printk("count: Did not find this process on the system calls list\n");
  return -ENOENT;
}

//additional system call added mainly for testing to empty out
//the data structure without a restart
SYSCALL_DEFINE0(sbx421_shutdown){
  int i;

  //must be root to shutdown the structure
  if(current_cred()->uid.val != 0){
    //printk("shutdown: Must be root to run unblock system call\n");
    return -EACCES;
  }

  //add 1 so that loops through 0-437
  for(i = 0; i < NUM_OF_SYSCALLS + 1; i++){
    if(syscalls[i] != NULL){
      struct SkipNode *x = syscalls[i]->header->forward[1];
      struct SkipNode *temp;

      while(x != syscalls[i]->header){
	temp = x->forward[1];
	kfree(x->forward);
	x->forward = NULL;
	kfree(x);
	x = temp;
      }

      kfree(syscalls[i]->header->forward);
      syscalls[i]->header->forward = NULL;
      kfree(syscalls[i]->header);
      syscalls[i]->header = NULL;
      kfree(syscalls[i]);
      syscalls[i] = NULL;
    }
  }
  
  return 0;
}
