#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

long mbx421_count_syscall(unsigned long id){
  return syscall(438, id);
}

int main(int argc, char *argv[]){
  long rv;
  
  printf("COUNTING MAILBOX.....\n");
  rv = mbx421_count_syscall(1);
  if(rv < 0){
    perror("count system call failed\n");
  }
  else{
    printf("count system call was successful\n");
  }
  printf("\n");
  
  return 0;
}
