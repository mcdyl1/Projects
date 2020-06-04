#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

long mbx421_recv_syscall(unsigned long id, const unsigned char *msg, long len){
  return syscall(440, id, msg, len);
}

int main(int argc, char *argv[]){
  long rv;
  
  printf("READING MESSAGE.....\n");
  rv = mbx421_recv_syscall(1, "", 3);
  if(rv < 0){
    perror("recv system call failed\n");
  }
  else{
    printf("recv system call was successful\n");
  }
  printf("\n");
  
  return 0;
}
