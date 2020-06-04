#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_sbx421_shutdown 437

long sbx421_shutdown_syscall(void){
  return syscall(__NR_sbx421_shutdown);
}

int main(int argc, char *argv[]){
  long rv;

  rv = sbx421_shutdown_syscall();

  if(rv < 0){
    perror("Shutdown system call failed\n");
  }
  else{
    printf("Shutdown system call ran successfully\n");
  }

  return 0;
}
