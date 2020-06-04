#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

long mbx421_shutdown_syscall(void){
  return syscall(435);
}

int main(int argc, char *argv[]){
  long rv;
  
  printf("SHUTTING DOWN MAILBOX SYSTEM.....\n");
  rv = mbx421_shutdown_syscall();
  if(rv < 0){
    perror("shutdown system call failed\n");
  }
  else{
    printf("shutdown system call was successful\n");
  }
  printf("\n");
  
  return 0;
}
