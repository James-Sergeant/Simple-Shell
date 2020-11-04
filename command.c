#define FALSE 0
#define TRUE 1

char * binPath = "/bin/";

/*
 * This is a structure that is used to store the command and its arguments.
 * */
typedef struct listStruct{
    int length;
    char* command;
    char** list; //array of pointers
}commandList;

//Functions:
commandList* setupList(commandList* comList, char* string);
commandList* addArgs(commandList* comList, char* string);
commandList* addNull(commandList* stringList);
char* getElement(commandList* comList , int x);
void printList(commandList* list);
char** getCommandList(commandList* list);
int checkCommand(commandList* list);
void runCommand(commandList* list);

/*
 * This function is used to set up a command list.
 * Return type: commandList
 * */
commandList* setupList(commandList* comList, char* string){
    //stets the command to the first input
    comList->command = string;
    //Creates a path for the command.
    char* commandPath= malloc(256*sizeof(char));
    strcpy(commandPath,binPath);
    strcat(commandPath,string);
    //printf("%s",commandPath);
   comList->list = (char**)malloc(sizeof(char*));
    comList->length = 1;
    comList->list[comList->length - 1] =commandPath;



    return comList;
}
/*
 * This function is used to add arguments to the list.
 * Return type: commandList
 * */
commandList* addArgs(commandList* comList, char* string){
    comList->list = realloc(comList->list, sizeof(int *) * ++comList->length);
    comList->list[comList->length - 1] = string;
    return comList;
}
/*
 * This function is used to add the NULL to the end of the list.
 * Return type: commandList
 * */
commandList* addNull(commandList* stringList){
    stringList->list = realloc(stringList->list, sizeof(int *) * ++stringList->length);
    stringList->list[stringList->length - 1] = NULL;
    return stringList;
}
/*
 * This function returns an element in the list.
 * Return type: char*
 * */
char* getElement(commandList* comList , int x){
    return comList->list[x];
}
/*
 * This function prints all the elements in the list, used for debugging.
 * */
void printList(commandList* list){
    for(int i = 0; i < list->length; i++){
        printf("%s\n", getElement(list, i));
    }
}
/*
 * This function returns a formatted command list with a null at the end.
 * Return type: char**
 * */
char** getCommandList(commandList* list){
    addNull(list);
    return list->list;
}
/*
 * This function is used to check for the special commands cd or exit, if nether are present it will call runCommand.
 * Also, will return a integer vale of TRUE or FALSE to tell the main loop to exit if the command is called.
 * Return type: int
 * */
int checkCommand(commandList* list) {
    if (strcmp(list->command, "exit") == 0) {
        return TRUE;
    } else if (strcmp(list->command, "cd") == 0) {
        chdir(list->list[1]);
    }
    else{
        runCommand(list);
    }
    return FALSE;
}

/*
 * This function is used to run the command using the execv function, to do this a new process is started.
 * The command is executed in the child process while the parent waits for it to finish.
 * */
void runCommand(commandList* list){
    pid_t pid = fork();
    //Child
    if(pid == 0){
        execv(getElement(list, 0), getCommandList(list));
    }
    //Parent
    else{
        int status;
        waitpid(pid,&status,0);
    }
}


