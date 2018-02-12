#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
//Define Zone
#define COMMAND_SIZE 100
#define MAX_LENGTH 1024
#define TRUE 1
#define FALSE 0
/*Function Precast*/
void perror(const char *str);
void shellCommand();
void bashCommand();
void displayScreen();
void currentDirectoryShow();
////////////////////////////////////

///////////////////////////////////
int main(int argc, char *argv[]){
    char cmd[COMMAND_SIZE]; 
    displayScreen(); //Clear Console to Blank
    if (argc != 2)
        shellCommand(cmd);
    else
        bashCommand(cmd, argv); 

}

void displayScreen()
{
	static int isFirstRun = TRUE; //Assuming 1 is True 0 is False
	if(isFirstRun==TRUE)
	{
		system("clear");
		isFirstRun = FALSE;
	}
}

//Showing Current Working Directory
void currentDirectoryShow()
{
	char cwd[MAX_LENGTH];
	if(getcwd(cwd,sizeof(cwd))!=NULL)
	{
		printf("Current working directory : %s\n",cwd);
	}
	else
	{
		perror("currentDirectoryShow Error");
	}
}

void shellCommand(char cmd[]) {
    while(TRUE) {
        printf("$ ");
        fgets(cmd, 100, stdin);
        //Self Create Function
        if (strcmp(cmd, "quit") == 10) break;
        else if(strcmp(cmd,"current")== 10)
        {
        	currentDirectoryShow();
        }
        else
        {
        	if(fork()!=0) // Parent Process
            	wait(NULL); // Waiting Child Process
       		else
       			system(cmd);	
    	}
        
    }
}

void bashCommand(char cmd[], char *argv[]) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        if(fork()!=0) // Parent Process
            wait(NULL); // Waiting Child Process
        else {
            system(line);
        }
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
