/*Alessandro russo
  114602274
  arusso98 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sysexits.h>
#include <unistd.h>

#define BUFFER_LEN 1024

int main(){
  char line[BUFFER_LEN];  
  char command_1[BUFFER_LEN];  
  char command_2[BUFFER_LEN];  
  char* argv[100];       
  pid_t pid;
  printf("shell_jr: ");
  fflush(stdout);
  while(fgets(line, BUFFER_LEN, stdin)){
      sscanf(line, "%s%s", command_1, command_2); 
      if(strcmp(command_1, "exit")==0){
	printf("See you\n");
	fflush(stdout);
        exit(0);
      }
      else if(strcmp(command_1, "hastalavista")==0){
	printf("See you\n");
	fflush(stdout);
        exit(0);
      }
      else if (strcmp(command_1, "cd") == 0){
	  chdir(command_2);	  
      }
      else{
	pid = fork();
	if(!pid){	
	  argv[0] = command_1;
	  argv[1] = command_2;
	  argv[2] = NULL;
	  execvp(argv[0], argv);
	  printf("Failed to execute %s\n", command_1);
	  exit(EX_OSERR);
	}else{
	  wait(NULL);
	}
      }
      printf("shell_jr: ");
      fflush(stdout);
  }
  exit(0);
}

     

      
      

      
      

	

	
