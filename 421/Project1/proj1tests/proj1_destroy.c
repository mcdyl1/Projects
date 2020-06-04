#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

long mbx421_destroy_syscall(unsigned long id){
  return syscall(437, id);
}

int main(int argc, char *argv[]){
  long rv;
  
  printf("DELETING MAILBOX.....\n");
  rv = mbx421_destroy_syscall(1);
  if(rv < 0){
    perror("destroy system call failed\n");
  }
  else{
    printf("destroy system call was successful\n");
  }
  printf("\n");
  
  return 0;
}
