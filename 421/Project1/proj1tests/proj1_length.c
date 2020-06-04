#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

long mbx421_length_syscall(unsigned long id){
  return syscall(441, id);
}

int main(int argc, char *argv[]){
  long rv;
  
  printf("GETTING LENGTH OF MESSAGE.....\n");
  rv = mbx421_length_syscall(1);
  if(rv < 0){
    perror("length system call failed\n");
  }
  else{
    printf("length system call was successful\n");
  }
  printf("\n");
  
  return 0;
}
