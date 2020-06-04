#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

void start_shell();
char* read_input();
char** parse_input(char *input);
int execute(char **args);
void clean_up(char **args, char *input);

int main(){
  start_shell();
  return 0;
}

void start_shell(){
  char *input = NULL;
  char **args = NULL;
  int result;

  while(1){
    printf("$");//prompt
    
    input = read_input();

    //checks edge case of user pressing "ENTER" key
    if(input[0] != '\0'){
      args = parse_input(input);

      result = execute(args);
      if(result == -1){//something went wrong in execute function
	printf("Command was not found\n");
      }
      else if(result == 0){//user wants to exit
	clean_up(args, input);//free memory before exiting
	exit(0);
      }
    }
    //finished with users input can go ahead and free
    clean_up(args, input);
  }
}

char* read_input(){
  int buffer_size = 256;//2^8(random starting length
  char *buffer = malloc(buffer_size * sizeof(char));
  int ii = 0;
  int c;

  while(1){
    c = fgetc(stdin);

    //reach end of a line, put null character
    if(c == '\n'){
      buffer[ii] = '\0';
      return buffer;
    }
    else{
      buffer[ii] = c;
    }
    ii++;

    //taken up all allocated memory, allocate for more
    if(ii >= buffer_size){
      buffer_size += buffer_size * 2;
      buffer = realloc(buffer, buffer_size);
    }
  }
}

//mostly the same concept as read_input()
char** parse_input(char *input){
  int buffer_size = 256;
  int ii = 0;
  //array of the individual tokens
  char **tokens = malloc(buffer_size * sizeof(char*));
  char *token;
  char *delim = " ";

  token = strtok(input, delim);

  //read until encounter end of input
  while(token != NULL){
    tokens[ii] = token;
    if(ii >= buffer_size){
      buffer_size += buffer_size * 2;
      tokens = realloc(tokens, buffer_size);
    }

    token = strtok(NULL, delim);
    ii++;
  }
  tokens[ii] = NULL; //put null terminator at end

  return tokens;
}

int execute(char **args){
  if(strcmp(args[0], "exit") == 0){
    return 0;
  }
  else{
    pid_t pid;

    pid = fork();

    if(pid < 0){
      printf("Fork Failed");
      return -1;
    }
    else if(pid == 0){
      if(execvp(*args, args) == -1){
	return -1;
      }
    }
    else{
      wait(NULL);
    }

    return 1;
  }
}

void clean_up(char **args, char *input){
  free(input);
  input = NULL;
  free(args);
  args = NULL;
}
