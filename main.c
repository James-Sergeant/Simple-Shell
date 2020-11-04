#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "command.c"

#define FALSE 0
#define TRUE 1

/*
 * This function is used to generate a formatted list from the users input to that which is accepted by the execv function.
 * Return type: commandList
 * */
commandList makeList(char *input){
    commandList list;

    //Takes the first argument of the command and uses it to setup the list.
    char *ptr = strtok(input," ");
    setupList(&list,ptr);

    //Loops through and adds other arguments to the list.
    ptr = strtok(NULL, " ");
    while(ptr != NULL){
        addArgs(&list, ptr);
        ptr = strtok(NULL, " ");
    }
    return list;
}
/*
 * This function reads in the users input and returns it removing the new line charter at the end.
 * Return type: char*
 * */
char* getIn(){
    char* input = (char*)malloc(256 * sizeof(char));
    fgets(input, 256, stdin);
    return strtok(input,"\n");
}

int main() {
    //Stores the current working directory.
    chdir("/Users/jamessergeant");
    char*  workingDir[256];
    getcwd(workingDir,256);
    int exit = FALSE;
    //Main while loop
    while (exit != TRUE) {
        //Main output of current directory for user input.
        printf("%s>", workingDir);
        //Creates a list of the command and arguments from the users input.
        commandList command = makeList(getIn());
        //Checks to see if the command that was called was exit or cd; if not runs the command.
        exit = checkCommand(&command);
        //Check current working directory
        getcwd(workingDir,256);

    }

    return EXIT_SUCCESS;
}
