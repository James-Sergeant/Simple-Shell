typedef struct listStruct{
    int length;
    int** list; //array of pointers
}List;


List* setupList(List* stringList, char* string){
    char * binPath = "/bin/";
    char* commandPath= malloc(256*sizeof(char));
    strcpy(commandPath,binPath);
    strcat(commandPath,string);
    //printf("%s",commandPath);
   stringList->list = (int**)malloc(sizeof(int*));
   stringList->length = 1;
   stringList->list[stringList->length - 1] =commandPath;



    return stringList;
}
char* chekArgs(char* args, char* workingDir){
    if(args[0] == '-'||args[0]=='/'){
        return args;
    }
    else{
        char* dirAndArgs = malloc(256*sizeof(char));
        strcpy(dirAndArgs,workingDir);
        strcat(dirAndArgs,"/");
        strcat(dirAndArgs,args);
        return dirAndArgs;

    }
}

List* addArgs(List* stringList, char* string, char* workingDir){
        stringList->list = realloc(stringList->list, sizeof(int *) * ++stringList->length);
        stringList->list[stringList->length - 1] = chekArgs(string,workingDir);
    return stringList;
}
List* addNull(List* stringList){
    stringList->list = realloc(stringList->list, sizeof(int *) * ++stringList->length);
    stringList->list[stringList->length - 1] = NULL;
    return stringList;
}
char* getElement(List* stringList , int x){
    return stringList->list[x];
}
void printList(List* list){
    for(int i = 0; i < list->length; i++){
        printf("%s\n", getElement(list, i));
    }
}
int** getCommandList(List* list, char* workingDir){
    addNull(list);
    //addArgs(list, NULL,workingDir);
    //printList(list);
    return list->list;
}



