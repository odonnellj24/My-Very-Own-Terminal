#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



void sigint_handler(int sig){
  char msg[] = "361>SIGINT handled\n";
  write(1, msg, sizeof(msg));
 //exit(0);
}

void sigtstp_handler(int sig){
  char msg[] = "361>SIGTSTP handled\n";
  write(1, msg, sizeof(msg));
  //exit(0);
}

int main(){

  //create some space for our strings
  char line[500];
  char* args[20];






   signal(SIGINT, sigint_handler);
   signal(SIGTSTP, sigtstp_handler);

  while(1){
    printf("361>");
    //read line from terminal
    fgets(line, 500, stdin);

    //break the string up into words
    char *word = strtok(line, " \n");
    int i = 0;
    if (word == NULL){
    continue;
    }
    while (word) {
    
    //  printf("word: %s\n", word);
      //copy a word to the arg array
    
      args[i] = word;
      //get next word
      word = strtok(NULL, " \n");
      i = i + 1;	
      }
      
     if (strcmp(args[0],"exit")== 0){
        return 0;
        }
        
     	char* file = NULL;
	char* arrow = NULL;
	int p =0;
	for(p=0;p<20;p++){
	if(args[p] == NULL)
		break;
	if(strcmp(args[p],">")==0 || strcmp(args[p],">>")==0 || strcmp(args[p],"<")==0){
		file = args[p + 1];
		arrow = args[p];
		args[p+1] = NULL;
		args[p] = NULL;
		break;
	}
	
	}
	

        int result = 0;
        int pid = fork();
     if (pid == 0) {
    
     if ((arrow != NULL) && strcmp(arrow,">")==0){
        int fd = open(file, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        dup2(fd,1);
        close(fd);
        //break;
       }else if((arrow != NULL) && strcmp(arrow,">>")==0){
          int fd = open(file, O_RDWR|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
          dup2(fd,1);
          close(fd);
          //break;
            }else if((arrow != NULL) && strcmp(arrow,"<")==0){
             int fd = open(file, O_RDONLY);
             dup2(fd,0);
             close(fd);
             //break;

             }
             
        result = execvp(args[0], args);
        exit(result); 
            
         }
         
	//printf("PID: %d\n", getpid());
      else 
      {
      	printf("PID: %d\n", pid);
      // printf("I am the parent.  I am waiting for my child %d to die.\n", pid);
       int status;
       waitpid(&status);
       printf("EXIT: %d\n", WEXITSTATUS(status));
       
       }

  //print out our array
  int j=0;
 // for (;j<i;j++){
  //  printf("args[%d]: %s\n", j, args[j]);
 // }
  for (j=0;j<i;j++){
  args[j] = NULL;
  }
  
}
}
