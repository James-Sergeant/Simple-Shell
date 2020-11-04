typedef struct listStruct{
    int length;
    int** list; //array of pointers
}List;


List* setupList(List* stringList, char* string){
   stringList->list = (int**)malloc(sizeof(int*));
   stringList->length = 1;
   stringList->list[stringList->length - 1] = string;



    return stringList;
}

List* addString(List* stringList, char* string){
        stringList->list = realloc(stringList->list, sizeof(int *) * ++stringList->length);
        stringList->list[stringList->length - 1] = string;
    return stringList;
}

char* getString(List* stringList ,int x){
    return stringList->list[x];
}

void printList(List* list){
    for(int i = 0; i < list->length; i++){
        printf("%s\n", getString(list, i));
    }
}