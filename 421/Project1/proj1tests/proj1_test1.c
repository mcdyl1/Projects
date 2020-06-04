#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

//#define __NR_mbx421_init 434

long mbx421_init_syscall(unsigned int ptrs, unsigned int prob){
  return syscall(434, ptrs, prob);
}

long mbx421_shutdown_syscall(void){
  return syscall(435);
}

long mbx421_create_syscall(unsigned long id){
  return syscall(436, id);
}

long mbx421_destroy_syscall(unsigned long id){
  return syscall(437, id);
}

long mbx421_count_syscall(unsigned long id){
  return syscall(438, id);
}

long mbx421_send_syscall(unsigned long id, const unsigned char *msg, long len){
  return syscall(439, id, msg, len);
}

int main(int argc, char *argv[]){
  long rv;

  printf("INITIALIZING MAILBOX SYSTEM\n");
  rv = mbx421_init_syscall(1, 2);
  if(rv < 0){
    perror("init system call failed\n");
  }
  else{
    printf("init system call was successful\n");
  }
  printf("\n");

  printf("CREATING MAILBOX WITH ID 1\n");
  rv = mbx421_create_syscall(1);
  if(rv < 0){
    perror("create system call failed\n");
  }
  else{
    printf("create system call was successful\n");
  }
  printf("\n");

  printf("ATTEMPTING TO CREATE MAILBOX WITH ID 1 AGAIN\n");
  rv = mbx421_create_syscall(1);
  if(rv < 0){
    perror("create system call failed\n");
  }
  else{
    printf("create system call was successful\n");
  }
  printf("\n");
  
  printf("SENDING MESSAGE HELLO TO MAILBOX 1\n");
  rv = mbx421_send_syscall(1, "hello\0", 6);
  if(rv < 0)
    perror("send system call failed\n");
  else{
    printf("send system call was successful\n");
  }
  printf("\n");

    printf("SENDING MESSAGE CAT TO MAILBOX 1\n");
  rv = mbx421_send_syscall(1, "cat", 3);
  if(rv < 0)
    perror("send system call failed\n");
  else{
    printf("send system call was successful\n");
  }
  printf("\n");

  printf("COUNT NUMBER OF MESSAGES IN MAILBOX 1\n");
  rv = mbx421_count_syscall(1);
  if(rv < 0)
    perror("send system call failed\n");
  else{
    printf("Count of messages in mailbox: %ld\n", rv);
  }
  
  printf("ATTEMPTING TO MAKE ANOTHER MAILBOX SYSTEM\n");
  rv = mbx421_init_syscall(1, 2);
  if(rv < 0){
    perror("System call failed\n");
  }
  else{
    printf("init system call was successful\n");
  }
  printf("\n");

  printf("SHUTTING DOWN MAILBOX SYSTEM\n");
  rv = mbx421_shutdown_syscall();
  if(rv < 0){
    perror("shutdown system call failed\n");
  }
  else{
    printf("shutdown system call was successful\n");
  }
  
  return 0;
}
