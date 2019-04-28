/*happpyJsL happpy_shell*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_LEN 100 /* The maximum length command */

int main(void) {
	char *args[MAX_LEN / 2 + 1]; /* command line arguments */
  	int should_run =1;	 
	/* flag todetermine when to exit program */
  	
	int background = 0;
	while (should_run){
		
		/* reset args */
		char * rst = NULL;
		for (int i=0;i<7;i++){
			args[i]=rst;
		}
  		
	
		printf("HAPPPY_shell> ");
    	fflush(stdout);
		char *str = (char*)malloc(MAX_LEN*sizeof(char));
		char *input = (char*)malloc(MAX_LEN*sizeof(char));
		fgets(input, MAX_LEN, stdin);
		strcpy(str,input); 
		
		
		if (strlen(input)==1){
			free(input);
			goto come_here;
		}
		/*check input =="exit" , quit shell*/
		
		else if (strncmp(input,"exit",4)==0){
			should_run =0;
			printf("bye~bye~  :) \n");
			return 0;
		}
		
		
		int break_while = 0;
		
		
		//test = strtok(input, "&"
		
		
		/* check letter '&' */
		if (strcmp(str,strtok(input,"&"))==0){
		//	printf("no found & \n");
		}
		else {
			printf("INPUT include '&' -> background occur.\n");
			background = 1;	
			return 99;
		}

		/*devide input string, set args argument*/
		int i = 0;
		char * tmp;
		tmp = strtok(str, " 	\n'$'");
		while (tmp != NULL){											
			
			args[i]=tmp;
			
//			printf("in data %s\n", tmp);
//			printf("%s\n",args[i]);	
			tmp = strtok(NULL," 	\n'$'");
			break_while ++;
			if (break_while > 15){
				break;
			}
		i++;
		}	
		if (strcmp(args[0],"cd") == 0){
		    if (chdir(args[1])==0)
			    printf("move to %s\n",args[1]);
			else{
			    printf("wrong directory! \n");
			}
			goto come_here;
		}
		/*do fork*/
		int pid = fork();
		
		//fork error
		if (pid < 0){
			fprintf(stderr, "Fork failed");
			return 1;
		}

		//child part
		else if(pid == 0){ 
		//	printf("\n");
			printf("'%s' commanded\n",args[0]);
		//	char *example[]={"ls","-l",0};
		//	printf("%s\n",example[0]);
			
			
			execvp(args[0],args);
//			execvp()
			return 99;
		}
		
		else{
			if (background == 1){
			//	printf("--------------------\n");
			//	printf("background == 1 \n");
			//	printf("--------------------\n");
				goto come_here;
			}
			wait(NULL);
			//printf("----------------------\n");
			//printf("(PID = %d)Complete\n",pid);
			//printf("----------------------\n\n");	
			
		}
  		come_here:;
		/* 
		args include "&" or 
		no input string or
		get "cd" command
		*/
	}
	return 0;
	
}

/*happpy happpy*/
