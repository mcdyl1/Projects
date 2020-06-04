#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

long mbx421_create_syscall(unsigned long id){
  return syscall(436, id);
}

int main(int argc, char *argv[]){
  long rv;
  
  printf("CREATING MAILBOX.....\n");
  rv = mbx421_create_syscall(1);
  if(rv < 0){
    perror("create system call failed\n");
  }
  else{
    printf("create system call was successful\n");
  }
  printf("\n");
  
  return 0;
}
