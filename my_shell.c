#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

int x[64];int fc;

/* Splits the string by space and returns the array of tokens
*
*/


void signal_handler(int sig_num){
//printf("yes");

kill(fc,SIGKILL);
waitpid(fc,NULL,0);
printf("foreground process terminated\n");

}


char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;
  
  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(tokens[tokenNo++], token);
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}


int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;int a;int l=0;int c_pid,b;int new;
	char *back_command = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));

        
	while(1) {			
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		printf("$ ");
		sleep(0.25);
		scanf("%[^\n]", line);
		getchar();
		
		//printf("%d",x[0]);
		for(int k=0;k<l;k++){
		{
		a=waitpid(x[k],NULL,WNOHANG);
		}
		if(a>0)
		printf("background process finished\n");
		//printf("%d",a);               
               }		
		

		//printf("Command entered: %s (remove this debug output later)\n", line);
		/* END: TAKING INPUT */

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);
		
		b=0;
		for(int i=0;tokens[i]!=NULL;i++)
		{ 
		//printf("%s\n",tokens[i]);
		if(!strcmp(tokens[i],"&"))
		{
	        back_command=strtok(line,"&");
               //printf("%d",*back_command);
               tokens=tokenize(back_command);
		
		b=1;
		//printf("%d new b is :",b);
		}
		}
		

               
               if(tokens[0]==NULL)
               {
               continue;
               }             
               
               else if(!strcmp(tokens[0],"exit")){
               //printf("%d",new);
               //printf("kill 1\n");
               for(int j=0;j<64;j++){
               if(j<l){
               free(tokens[i]);
               kill(x[j],SIGTERM);
               waitpid(x[j],NULL,WNOHANG);
               printf("back_ground process %d is terminated and reaped\n",j);
               }
               else
               break;
               }//printf("kill 2\n");
		//printf("line 1\n");
		break;

               }


              else if(!strcmp(tokens[0],"cd")){
               
               
               if(tokens[2]!=NULL)
               printf("Wrong command\n");
               else {
               chdir(tokens[1]);

               }
               }
               

               
               
              else if(b==1){

              new=fork();
              
              if(new<0)
               {
               fprintf(stderr,"%s\n","Unable to create child process!!\n");
               }
               else if(new==0)   //child code
               {
               
               //printf("%d",getppid());
               

               if(setpgid(getpid(),getpid())!=0)
               printf("error\n");
               
               //printf("pgid is: %d\n",getpgid(x[l]));
               //printf("pgid is: %d",getpgid(getpid()));
               //setpgid(x,y);
               execvp(tokens[0],tokens);
               printf("Unable to execute the command!! \n");
               _exit(1);
               } 
               else
               {
               
               x[l]=new;
               //printf("%d\n",x[l]);
               
               //printf("%d",x[l]);
               l++;
               //int nc= wait(NULL);
               }                            
              }
               
              else{
               
               fc=fork();
               
               if(fc<0)
               {
               fprintf(stderr,"%s\n","Unable to create child process!!\n");
               }
               else if(fc==0)   //child code
               {
               //c_pid=getpid();
               //printf("%d\n",getpid());
               //printf("%d\n",c_pid);
               //printf("%d\n",fc);
               execvp(tokens[0],tokens);
               printf("Unable to execute the command!! \n");
               _exit(1);
               }
               else
               {
               signal(SIGINT,signal_handler);
               //setpgid(0,0);
               //printf("%d",setpgid(0,0));
               int wc= waitpid(fc,NULL,0);
               //printf("%d",wc);
               if(wc>0)
               printf("foreground process finished\n");
              
               }
               }
   

       
		// Freeing the allocated memory	
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}
		free(tokens);

	}
	printf("exit from main program\n");
	return 0;
}
