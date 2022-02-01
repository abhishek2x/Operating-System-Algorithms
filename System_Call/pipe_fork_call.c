#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main() {
  int fd1[2];
  int fd2[2];

  char fixed_string[10] = "Lets Study";
  char input_string[100];
  pid_t p;

  if(pipe(fd1) == -1) {
    fprintf(stderr, "pipe failed");
    return 1;
  }
  if(pipe(fd2) == -1) {
    fprintf(stderr, "pipe failed");
    return 1;
  }

  scanf("%s", input_string);
  p = fork();;

  if(p < 0) {
    fprintf(stderr, "fork() failed");
    return 1;
  }
  else if(p > 0) { // Parent Process
    char concat_string[100];
    
    // * PIPE 1
    close(fd1[0]); // closed reading end of pipe 1

    // write input str to pipe 1 and close writing end

    write(fd1[1], input_string, strlen(input_string));
    close(fd1[1]);

    // * PIPE 2

    wait(NULL); // wait for child to send a string
    close(fd2[1]);

    // read string from child, print it and close the end
    read(fd2[0], concat_string, 100);
    printf("Concatenated String: %s \n", concat_string);
    
    close(fd1[1]);
  }
  else { // Child Process
    // first it will read from the parent

    close(fd1[1]);

    char concat_string[100];
    read(fd1[0], concat_string, 100);

    int i, k=strlen(concat_string);
    for(i=0; i<strlen(fixed_string); i++) {
      concat_string[k++] = fixed_string[i];
    }
    concat_string[k] = '\0';

    // close both reading ends
    close(fd1[0]);
    close(fd2[0]);

    // write concatenated string and close the writing end
    write(fd2[1], concat_string, strlen(concat_string));
    close(fd2[1]);

    exit(0);
  }
}