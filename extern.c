#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include"define.h"
#include"trie.h"
#include"declerations.h"
/*get all externs names for use in extern_out*/
int extern_obj(FILE* ifp,trienode **trie)
{
    char *line = malloc(MAX_LINE * sizeof(char));
    if (line == NULL)
    {
        printf("error in memory allocation\n");
        return ERROR;
    }
    
    char *first = NULL,*second = NULL;

    while (fgets(line,MAX_LINE,ifp)!=NULL)
    {
        first = strtok(line," \t");
        if(strcmp(first,".extern")==0)
        {
            second = strtok(NULL," \t");
            trieinsert(trie,second,1);                
        }
    }
    free(line);
    return 0;
}