#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "list.c"

#define FALSE 0
#define TRUE 1

void runCommand(List* list,char* currentPath){
    const char* constPath = "/bin/";
    char* commandPath = malloc(sizeof(char) * 256);
    strcpy(commandPath,constPath);
    strcat(commandPath,getString(list,0));
    addString(list,currentPath);
    //printf("%s\n", commandPath);
    pid_t pid = fork();
    if(pid == 0){
        //run code
        //execl(commandPath, "ls", "-als", "/",NULL);
        //List start with command path and ends in NULL
        execv(commandPath,list->list);
    }else{
        int status;
        waitpid(pid,&status,0);
    }
}
int checkCommand(List* list, char* currentPath){
    char* command = getString(list, 0);
    if(strcmp(command,"exit") == 0){
        return TRUE;
    }else if(strcmp(command,"cd")==0){
        strcpy(currentPath,getString(list, 1));
    }else{
        runCommand(list, currentPath);
    }
    return FALSE;
}
List getList(char *input){
    List list;
    char *ptr = strtok(input," ");
    setupList(&list,ptr);
    ptr = strtok(NULL, " ");
    while(ptr != NULL){
        addString(&list,ptr);
        ptr = strtok(NULL, " ");
    }
    return list;
}

char* getIn(){
    char* input = (char*)malloc(256 * sizeof(char));
    fgets(input, 256, stdin);
    return strtok(input,"\n");
}

int main() {
    char *currentPath = (char*) malloc(256 * sizeof(char ));
    strcpy(currentPath,"/Users/jamessergeant");
    int exit = FALSE;
    while (exit != TRUE) {
        printf("%s:", currentPath);
        List command = getList(getIn());
        exit = checkCommand(&command,currentPath);
    }

    return EXIT_SUCCESS;
}
