#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_sbx421_count 436

long sbx421_count_syscall(pid_t proc, unsigned long nr){
  return syscall(__NR_sbx421_count, proc, nr);
}

int main(int argc, char *argv[]){
  long rv;
  int proc;
  int nr;
  char *endptr;

  //must be root to run program
  if(getuid() != 0){
    fprintf(stderr, "Must be root to run this program\n");
    exit(EXIT_FAILURE);
  }
  //must be at least 3 arguments on command line
  if(argc < 3){
    fprintf(stderr, "Not enough arguments passed\n");
    exit(EXIT_FAILURE);
  }
  //PID must be a number
  proc = strtol(argv[1], &endptr, 10);
  if(endptr == argv[1] || *endptr != '\0'){
    fprintf(stderr, "A number was not entered for PID\n");
    exit(EXIT_FAILURE);
  }
  //nr must be a numer
  nr = strtol(argv[2], &endptr, 10);
  if(endptr == argv[2] || *endptr != '\0'){
    fprintf(stderr, "A number was not entered for system call number\n");
    exit(EXIT_FAILURE);
  }
  //PID passed in must be greater than 0
  if(proc <= 0){
    fprintf(stderr, "First argument value must be greater than 0\n");
    exit(EXIT_FAILURE);
  }
  //system call number must be in range
  if(nr < 0 || nr > 437){
    fprintf(stderr, "Second argument value must be between 0 and 437\n");
    exit(EXIT_FAILURE);
  }

  //all checks passed run system call
  rv = sbx421_count_syscall(proc, nr);
  
  if(rv < 0){
    perror("Count system call failed\n");
  }
  else{
    printf("Count system call ran successfully\n");
    printf("Count: %d\n", rv);
  }
  
  return 0;
}
