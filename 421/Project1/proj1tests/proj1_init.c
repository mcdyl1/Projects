#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

long mbx421_init_syscall(unsigned int ptrs, unsigned int prob){
  return syscall(434, ptrs, prob);
}

int main(int argc, char *argv[]){
  long rv;
  
  printf("INITIALIZING MAILBOX SYSTEM.....\n");
  rv = mbx421_init_syscall(4, 2);
  if(rv < 0){
    perror("init system call failed\n");
  }
  else{
    printf("init system call was successful\n");
  }
  printf("\n");
  
  return 0;
}
