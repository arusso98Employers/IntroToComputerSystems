/* 114602275 
   Alessandro Russo 
   arusso98 */

#include <stdio.h>
#include "command.h"
#include "executor.h"
#include <sysexits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE_PERMISSIONS 0664

static void print_tree(struct tree *t);

int execute_aux(struct tree *t, int input_fd, int output_fd){
  pid_t pid, child_pid_one, child_pid_two, child_pid_three;
  int fd, fd2[2], status1, status2;
  /*checks if t is NULL */
  if(t == NULL){
    return 0;
  }
  /*subshell conjunction*/
  else if(t->conjunction == SUBSHELL){
    /*determines fork error*/
    if ((child_pid_three = fork()) < 0) {
      perror("fork error");
    }
    /*child node*/
    if (child_pid_three == 0){
      /*recursive call*/
      execute_aux(t->left, input_fd, output_fd);
      exit(0);
    }else{
      wait(&status1);
    }
  }
  /*and conjunction*/
  else if (t->conjunction == AND){
    /*recursive call*/
    if(execute_aux(t->left, input_fd, output_fd) == 0){
      execute_aux(t->right, input_fd, output_fd);
    }
  }
  /*input output redirection*/
  else if (t->conjunction == PIPE){
    if(t->right->input != NULL && t->left->output != NULL){
      printf("Ambiguous output redirect.\n");
    }
    if(t->left->output == NULL && t->right->input != NULL){
      printf("Ambiguous input redirect.\n");
    }
    if(t->right->input == NULL && t->left->output != NULL){
      printf("Ambiguous output redirect.\n");
    }
    else{
      /* Before the fork, we need to create the pipe */ 
      /* (otherwise no sharing of pipe) */
      if (pipe(fd2) < 0) {
	perror("pipe error");
      }
      if ((child_pid_one = fork()) < 0) {
	perror("fork error");
      }
       /* Child 1's code  */
      if (child_pid_one == 0)  {
	close(fd2[0]); /* we don't need pipe's read end */
	/* Redirecting standard output to pipe write end */
	if (dup2(fd2[1], output_fd) < 0) {
	  perror("dup2 error");
	}
	/* Releasing resource */     
	close(fd2[1]);
	execute_aux(t->left, input_fd, output_fd);
      }
      /* parent's code */
      else { 
 
	/* Creating second child */
	if ((child_pid_two = fork()) < 0) {
	  perror("fork error");
	}
	/* Child 2's code */
	if (child_pid_two == 0)  {
	  /* we don't need pipe's write end */
	  close(fd2[1]); 
	  /* Redirecting standard input to pipe read end */
	  if (dup2(fd2[0], input_fd) < 0) {
	    perror("dup2 error");
	  }
	  /* Releasing resource */
	  close(fd2[0]);
	  execute_aux(t->right, input_fd, output_fd);    
	}
	else {
	  /* Parent has no need for the pipe */
	  close(fd2[0]);
	  close(fd2[1]);
	  /* Reaping each child */
	  wait(NULL); 
	  wait(NULL);
	}
      }
    }  
  }
  else if (t->conjunction == NONE){
    if(strcmp(t->argv[0], "exit")==0){
        exit(0);
      }
    else if (strcmp(t->argv[0], "cd") == 0){
      if(t->argv[1] != NULL){
	chdir(t->argv[1]);
      }else{
	char *p = getenv("HOME");
	chdir(p);
	}
      }
    else{
      if(t->input){
	/* If we have a second argument that represents the 
	   input file */
	if ((fd = open(t->input, FILE_PERMISSIONS)) > 0) {
	  if (dup2(fd, input_fd) < 0) {
	    perror("dup2 failed");
	  }
	  /* Releasing resource */
	  close(fd); 
	}
      }
      if(t->output){
	/* If we have a second argument that represents the
	   input file */
	if ((fd = open(t->output, FILE_PERMISSIONS)) > 0) {
	  if (dup2(fd, output_fd) < 0) {
	    perror("dup2 failed");
	  }
	  /* Releasing resource */
	  close(fd); 
	}
      }
      if((pid = fork()) < 0){
	perror("fork failed");
      }
      /*Child Process*/
      if(!pid){
	  execvp(t->argv[0], t->argv);
	  exit(1);
      }
      /*Parent process*/
      else{  
	wait(&status2);
	if(WIFEXITED(status2)){
	  if (WEXITSTATUS(status2)) {
	    fprintf(stderr, "Failed to execute %s\n",
		    t->argv[0]);
	    return -1;
	  }
	}
      }	  
    }
  }
    return 0;
}

int execute(struct tree *t) {
  execute_aux(t, STDIN_FILENO, STDOUT_FILENO);
  return 0;
}

static void print_tree(struct tree *t) {
   if (t != NULL) {
      print_tree(t->left);
      if (t->conjunction == NONE) {
         printf("NONE: %s, ", t->argv[0]);
      } else {
         printf("%s, ", conj[t->conjunction]);
      }
      printf("IR: %s, ", t->input);
      printf("OR: %s\n", t->output);
      print_tree(t->right);
   }
}

