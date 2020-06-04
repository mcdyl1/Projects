#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/ktime.h>

struct MsgNode{
  unsigned char *msg;
  long msgLen;
  struct MsgNode *next;
};

struct AclNode{
  pid_t process_id;
  struct AclNode *next;
};

struct SkipNode{
  unsigned long id;
  int hasACL;
  struct MsgNode *MsgListHead;
  struct AclNode *AclListHead;
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

static unsigned int generate_random_int(void){
  next_random = next_random * 1103515245 + 12345;
  return (next_random / 65536) % 32768;
}

static void seed_random(unsigned int seed){
  next_random = seed;
}

static int get_random_level(void){
  int level = 1;
  while(generate_random_int() < (32767 / list->LevelProb) && level < list->MaxLevel){
    level++;
  }
  return level;
}

SYSCALL_DEFINE2(mbx421_init, unsigned int, ptrs, unsigned int, prob){
  //put into helper function that checks if user is root
  if(list != NULL){
    return -EALREADY;
  }
  if(current_cred()->uid.val != 0){
    return -EPERM;
  }
  if(prob != 2 && prob != 4 && prob != 8 && prob != 16){
    return -EINVAL;
  }
  if(ptrs == 0){
    return -EINVAL;
  }

  seed_random(ktime_get_ns());
  int i;
  list = kmalloc(sizeof(struct SkipList), GFP_KERNEL);
  if(list == NULL)
    return -ENOMEM;
  
  list->MaxLevel = ptrs;
  list->LevelProb = prob;
  list->CurrentLevel = 1;

  struct SkipNode *header = kmalloc(sizeof(struct SkipNode), GFP_KERNEL);
  if(header == NULL)
    return -ENOMEM;
  
  list->header = header;
  header->id = MAX_ID;
  header->MsgListHead = NULL;
  header->AclListHead = NULL;
  header->hasACL = 0;
  header->forward = kmalloc(sizeof(struct SkipNode *) * (ptrs + 1), GFP_KERNEL);
  if(header->forward == NULL)
    return -ENOMEM;

  for(i = 0; i <= ptrs; i++){
    header->forward[i] = list->header;
  }
  
  return 0;
}

SYSCALL_DEFINE0(mbx421_shutdown){
  if(list == NULL){
    return -ENODEV;
  }
  if(current_cred()->uid.val != 0){
    return -EPERM;
  }
  
  struct SkipNode *x = list->header->forward[1];
  struct SkipNode *temp;
  
  while(x != list->header){
    struct MsgNode *n = x->MsgListHead;
    struct MsgNode *next;
    while(n != NULL){
      next = n->next;
      kfree(n->msg);
      n->msg = NULL;
      kfree(n);
      n = NULL;
      n = next;
    }
    struct AclNode *a = x->AclListHead;
    struct AclNode *nexta;
    while(a != NULL){
      nexta = a->next;
      kfree(a);
      a = NULL;
      a = nexta;
    }
    temp = x->forward[1];
    x->hasACL = 0;
    kfree(x->forward);
    x->forward = NULL;
    kfree(x);
    x = NULL;
    x = temp;
  }
  
  kfree(list->header->forward);
  list->header->forward = NULL;
  kfree(list->header);
  list->header = NULL;
  kfree(list);
  list = NULL;
  
  return 0;
}

SYSCALL_DEFINE1(mbx421_create, unsigned long, id){
  if(list == NULL){
    return -ENODEV;
  }
  if(current_cred()->uid.val != 0){
    return -EPERM;
  }
  if(id == MIN_ID || id == MAX_ID){
    return -EINVAL;
  }
  
  struct SkipNode *update[list->MaxLevel + 1];
  struct SkipNode *x = list->header;
  int i, level;

  for(i = list->CurrentLevel; i >= 1; i--){
    while(x->forward[i] != NULL && x->forward[i]->id < id){
      x = x->forward[i];
    }
    update[i] = x;
  }
  x = x->forward[1];

  if(x->id == id){
    return -EEXIST;
  }
  else{
    level = get_random_level();
    if(level > list->CurrentLevel){
      for(i = list->CurrentLevel + 1; i < level + 1; i++){
	update[i] = list->header;
      }
      list->CurrentLevel = level;
    }

    x = kmalloc(sizeof(struct SkipNode), GFP_KERNEL);
    if(x == NULL)
      return -ENOMEM;
    
    x->id = id;
    x->hasACL = 0;
    x->MsgListHead = NULL;
    x->AclListHead = NULL;
    x->forward = kmalloc(sizeof(struct SkipNode*) * (level + 1), GFP_KERNEL);
    if(x->forward == NULL)
      return -ENOMEM;
    
    for(i = 1; i <= level; i++){
      x->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = x;
    }
    return 0;
  }
}

SYSCALL_DEFINE1(mbx421_destroy, unsigned long, id){
  if(list == NULL){
    return -ENODEV;
  }
  if(current_cred()->uid.val != 0){
    return -EPERM;
  }
  
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
      kfree(n->msg);
      n->msg = NULL;
      kfree(n);
      n = NULL;
      n = tempn;
    }
    struct AclNode *a = x->AclListHead;
    struct AclNode *nexta;
    while(a != NULL){
      nexta = a->next;
      kfree(a);
      a = NULL;
      a = nexta;
    }
    
    kfree(x->forward);
    x->forward = NULL;
    x->hasACL = 0;
    kfree(x);
    x = NULL;

    while(list->CurrentLevel > 1 && list->header->forward[list->CurrentLevel] == list->header){
      list->CurrentLevel--;
    }
    
    return 0;
  }

  return -ENOENT;
  
}

SYSCALL_DEFINE1(mbx421_count, unsigned long, id){
  if(list == NULL){
    return -ENODEV;
  }
  
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
    if(x->hasACL == 1 && current_cred()->uid.val != 0){
      struct AclNode *a = x->AclListHead;
      int isAllowed = 0;
      while(a != NULL){
	if(a->process_id == current->pid){
	  isAllowed = 1;
	  break;
	}
	a = a->next;
      }
      if(isAllowed != 1){
	return -EPERM;
      }
    }
    
    struct MsgNode *n = x->MsgListHead;
    while(n != NULL){
      count++;
      n = n->next;
    }
    return count;
  }
  
  return -ENOENT;
}

SYSCALL_DEFINE3(mbx421_send, unsigned long, id, const unsigned char __user *, msg, long, len){
  if(list == NULL){
    return -ENODEV;
  }
  if(msg == NULL){
    return -EFAULT;
  }
  
  struct SkipNode *x = list->header;
  int i;

  for(i = list->CurrentLevel; i >= 1; i--){
    while(x->forward[i]->id < id){
      x = x->forward[i];
    }
  }
  x = x->forward[1];

  if(x->id == id){
    if(x->hasACL == 1 && current_cred()->uid.val != 0){
      struct AclNode *a = x->AclListHead;
      int isAllowed = 0;
      while(a != NULL){
	if(a->process_id == current->pid){
	  isAllowed = 1;
	  break;
	}
	a = a->next;
      }
      if(isAllowed != 1){
	return -EPERM;
      }
    }
    
    struct MsgNode *last = x->MsgListHead;
    struct MsgNode *newNode = kmalloc(sizeof(struct MsgNode), GFP_KERNEL);
    if(newNode == NULL)
      return -ENOMEM;
    
    newNode->msg = kmalloc(sizeof(unsigned char) * len, GFP_KERNEL);
    if(newNode->msg == NULL)
      return -ENOMEM;
    
    if(copy_from_user(newNode->msg, msg, len) != 0){
      kfree(newNode->msg);
      kfree(newNode);
      return -EFAULT;
    }
    newNode->msgLen = len;
    newNode->next = NULL;
    
    if(x->MsgListHead == NULL){
      x->MsgListHead = newNode;
      return 0;
    }
    
    while(last->next != NULL){
      last = last->next;
    }
    last->next = newNode;
    
    return 0;
  }
  
  return -ENOENT;
}

SYSCALL_DEFINE3(mbx421_recv, unsigned long, id, unsigned char __user *, msg, long, len){
  if(list == NULL){
    return -ENODEV;
  }
  
  struct SkipNode *x = list->header;
  int i;

  for(i = list->CurrentLevel; i >= 1; i--){
    while(x->forward[i]->id < id){
      x = x->forward[i];
    }
  }
  
  x = x->forward[1];

  if(x->id == id){
    if(x->hasACL == 1 && current_cred()->uid.val != 0){
      struct AclNode *a = x->AclListHead;
      int isAllowed = 0;
      while(a != NULL){
	if(a->process_id == current->pid){
	  isAllowed = 1;
	  break;
	}
	a = a->next;
      }
      if(isAllowed != 1){
	return -EPERM;
      }
    }
    if(x->MsgListHead == NULL){
      return -ESRCH;
    }
    
    if(x->MsgListHead->msgLen < len){
      len = x->MsgListHead->msgLen;
    }
    
    if(copy_to_user(msg, x->MsgListHead->msg, len) != 0){
      return -EFAULT;
    }
    
    struct MsgNode *temp = x->MsgListHead;
    x->MsgListHead = x->MsgListHead->next;

    kfree(temp->msg);
    temp->msg = NULL;
    kfree(temp);
    temp = NULL;
    
    return len;
  }

  return -ENOENT;
}

SYSCALL_DEFINE1(mbx421_length, unsigned long, id){
  if(list == NULL){
    return -ENODEV;
  }

  struct SkipNode *x = list->header;
  int i;

  for(i = list->CurrentLevel; i >= 1; i--){
    while(x->forward[i]->id < id){
      x = x->forward[i];
    }
  }
  x = x->forward[1];

  if(x->id == id){
    if(x->hasACL == 1 && current_cred()->uid.val != 0){
      struct AclNode *a = x->AclListHead;
      int isAllowed = 0;
      while(a != NULL){
	if(a->process_id == current->pid){
	  isAllowed = 1;
	  break;
	}
	a = a->next;
      }
      if(isAllowed != 1){
	return -EPERM;
      }
    }
    
    if(x->MsgListHead == NULL){
      return -ESRCH;
    }
    return x->MsgListHead->msgLen;
  }
  
  return -ENOENT;
}

SYSCALL_DEFINE2(mbx421_acl_add, unsigned long, id, pid_t, process_id){
  if(list == NULL){
    return -ENODEV;
  }
  if(current_cred()->uid.val != 0){
    return -EPERM;
  }
  
  struct SkipNode *x = list->header;
  int i;

  for(i = list->CurrentLevel; i >= 1; i--){
    while(x->forward[i]->id < id){
      x = x->forward[i];
    }
  }
  x = x->forward[1];

  if(x->id == id){
    struct AclNode *last = x->AclListHead;
    struct AclNode *newNode = kmalloc(sizeof(struct AclNode), GFP_KERNEL);
    if(newNode == NULL)
      return -ENOMEM;
    
    newNode->process_id = process_id;
    newNode->next = NULL;
    
    if(x->AclListHead == NULL){
      x->hasACL = 1;
      x->AclListHead = newNode;
      return 0;
    }
    
    while(last->next != NULL){
      if(last->process_id == process_id){
	return -EEXIST;
      }
      last = last->next;
    }
    last->next = newNode;

    return 0;
  }
  return -1;
}

SYSCALL_DEFINE2(mbx421_acl_remove, unsigned long, id, pid_t, process_id){
  if(list == NULL){
    return -ENODEV;
  }
  if(current_cred()->uid.val != 0){
    return -EPERM;
  }
  
  struct SkipNode *x = list->header;
  int i;

  for(i = list->CurrentLevel; i >= 1; i--){
    while(x->forward[i]->id < id){
      x = x->forward[i];
    }
  }
  
  x = x->forward[1];

  if(x->id == id){
    struct AclNode *temp = x->AclListHead;
    struct AclNode *prev;

    if(temp != NULL && temp->process_id == process_id){
      x->AclListHead = temp->next;
      kfree(temp);
      temp = NULL;
      return 0;
    }

    while(temp != NULL && temp->process_id != process_id){
      prev = temp;
      temp = temp->next;
    }
    if(temp == NULL){
      return -ENOENT;
    }

    prev->next = temp->next;
    kfree(temp);
    temp = NULL;

    return 0;
  }

  return -ENOENT;
}

