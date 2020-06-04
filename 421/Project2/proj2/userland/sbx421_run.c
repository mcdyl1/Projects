#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

#define __NR_sbx421_block 434

long sbx421_block_syscall(pid_t proc, unsigned long nr){
  return syscall(__NR_sbx421_block, proc, nr);
}

int main(int argc, char *argv[]){
  if(getuid() != 0){
    fprintf(stderr, "error: Must be root to run this program\n");
    exit(EXIT_FAILURE);
  }
  if(argc < 3){
    fprintf(stderr, "Not enough arguments passed\n");
    exit(EXIT_FAILURE);
  }
  
  //read in file, add to array
  FILE *file;
  int arrSize = 256;
  int *syscalls = malloc(arrSize * sizeof(char));
  
  file = fopen(argv[2], "r");
    
  if(file == NULL){
    fprintf(stderr, "Error Reading File\n");
    free(syscalls);
    exit(EXIT_FAILURE);
  }

  int nr;
  int ii = 0;
  while(!feof (file)){
    if(fscanf(file, "%d", &nr) == 1){
      syscalls[ii] = nr;
      ii++;
      printf("NR: %d\n", nr);
    }
    else{
      fprintf(stderr, "Number was not entered\n");
      exit(EXIT_FAILURE);
    }

    //based on size of file might need to increase size of array
    if(ii >= arrSize){
      arrSize += arrSize * 2;
      syscalls = realloc(syscalls, arrSize);
    }
  }
  
  //make sure user exist
  struct passwd *user;
  if(getpwnam(argv[1]) == NULL){
    fprintf(stderr, "User does not exist\n");
    exit(EXIT_FAILURE);
  }
  else{
    user = getpwnam(argv[1]);
  }

  //block the system calls read in from the file. block system file will handle
  //possible duplicates
  long rv;

  for(int j = 0; j < ii; j++){
    rv = sbx421_block_syscall(getpid(), syscalls[j]);
    if(rv < 0){
      perror("Block system call failed\n");
    }
    else{
      printf("Block system call ran successfully\n");
    }
  }

  //change userid
  setuid(user->pw_uid);

  pid_t pid;

  pid = fork();
  if(pid < 0){
    fprintf(stderr, "Fork Failed\n");
    exit(0);
  }
  else if(pid == 0){
    if(execvp(argv[3], &argv[3]) == -1)
      exit(EXIT_FAILURE);
  }
  else{
    wait(NULL);
  }
  
  return 0;
}
