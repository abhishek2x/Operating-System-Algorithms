#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main() {
  // create fork(), and do parent before child

  pid_t child_pid = fork();

  if(child_pid > 0) {    // parent 
    printf("Parent Execution done before child");
  }
  else if(child_pid == 0) {   // child
    sleep(1);
    printf("Not Executed");
  }
  else {
    // error
  }
  return 0;
}