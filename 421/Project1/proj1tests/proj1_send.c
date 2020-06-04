#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

long mbx421_send_syscall(unsigned long id, const unsigned char *msg, long len){
  return syscall(439, id, msg, len);
}

int main(int argc, char *argv[]){
  long rv;
  
  printf("SENDING MESSAGE.....\n");
  rv = mbx421_send_syscall(1, "hello", 5);
  if(rv < 0){
    perror("send system call failed\n");
  }
  else{
    printf("send system call was successful\n");
  }
  printf("\n");
  
  return 0;
}
