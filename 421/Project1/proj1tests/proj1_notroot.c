#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

//basic test of creating mailbox, trying to create with same id, sending, counting, creating another instance of mailbox system, and shutting down.
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

long mbx421_recv_syscall(unsigned long id, const unsigned char *msg, long len){
  return syscall(440, id, msg, len);
}

long mbx421_length_syscall(unsigned long id){
  return syscall(441, id);
}

long mbx421_acl_add_syscall(unsigned long id, pid_t process_id){
  return syscall(442, id, process_id);
}

long mbx421_acl_remove_syscall(unsigned long id, pid_t process_id){
  return syscall(443, id, process_id);
}

int main(int argc, char *argv[]){
  long rv;

  printf("INIT SYSTEM CALL...\n");
  rv = mbx421_init_syscall(4, 2);
  if(rv < 0){
    perror("init system call failed\n");
  }
  else{
    printf("init system call was successful\n");
  }
  printf("\n");

  printf("SHUTDOWN SYSTEM CALL...\n");
  rv = mbx421_shutdown_syscall();
  if(rv < 0){
    perror("shutdown system call failed\n");
  }
  else{
    printf("shutdown system call was successful\n");
  }
  printf("\n");

  printf("CREATE SYSTEM CALL...\n");
  rv = mbx421_create_syscall(1);
  if(rv < 0){
    perror("create system call failed\n");
  }
  else{
    printf("create system call was successful\n");
  }
  printf("\n");
  
  printf("DESTROY SYSTEM CALL...\n");
  rv = mbx421_destroy_syscall(1);
  if(rv < 0){
    perror("destroy system call failed\n");
  }
  else{
    printf("destroy system call was successful\n");
  }
  printf("\n");

  printf("COUNT SYSTEM CALL...\n");
  rv = mbx421_count_syscall(1);
  if(rv < 0){
    perror("count system call failed\n");
  }
  else{
    printf("count system call was successful\n");
  }
  printf("\n");

  printf("SEND SYSTEM CALL...\n");
  rv = mbx421_send_syscall(1, "hello", 5);
  if(rv < 0){
    perror("send system call failed\n");
  }
  else{
    printf("send system call was successful\n");
  }
  printf("\n");

  printf("RECV SYSTEM CALL...\n");
  rv = mbx421_recv_syscall(1, "cat", 3);
  if(rv < 0){
    perror("recv system call failed\n");
  }
  else{
    printf("recv system call was successful\n");
  }
  printf("\n");

  printf("LENGTH SYSTEM CALL...\n");
  rv = mbx421_length_syscall(1);
  if(rv < 0){
    perror("length system call failed\n");
  }
  else{
    printf("length system call was successful\n");
  }
  printf("\n");

  printf("ACL ADD SYSTEM CALL...\n");
  rv = mbx421_acl_add_syscall(1, getpid());
  if(rv < 0){
    perror("acl add system call failed\n");
  }
  else{
    printf("acl add system call was successful\n");
  }
  printf("\n");

  printf("ACL REMOVE SYSTEM CALL...\n");
  rv = mbx421_acl_remove_syscall(1, getpid());
  if(rv < 0){
    perror("acl remove system call failed\n");
  }
  else{
    printf("acl remove system call was successful\n");
  }
  printf("\n");
  
  return 0;
}
