#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

long mbx421_acl_remove_syscall(unsigned long id, pid_t process_id){
  return syscall(443, id, process_id);
}

int main(int argc, char *argv[]){
  long rv;
  
  printf("REMOVING FROM MAILBOXES ACL.....\n");
  rv = mbx421_acl_remove_syscall(1, getpid());
  if(rv < 0){
    perror("init system call failed\n");
  }
  else{
    printf("init system call was successful\n");
  }
  printf("\n");
  
  return 0;
}
