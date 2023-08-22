#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include"trie.h"
#include"define.h"
#include"declerations.h"
/*find all labels and insert them in trie */
int labels_table(FILE* ifp,trienode **label_trie_root)
{
    char *line1 = malloc(MAX_LINE*(sizeof(char)));
    if (line1==NULL)
    {
        printf("memory allocation failed\n");
        return ERROR;
    }
    
    char *label_name;
    int count = 100;
    long int position; 
    
    while ((position=ftell(ifp))!= -1 &&fgets(line1,MAX_LINE,ifp)!=NULL)
    {
        label_name = strtok(line1," \t\n\0");
        if(strchr(label_name,':')!=NULL)
        {
            label_name = strtok(label_name,":");/*get : off label_name*/
            trieinsert(label_trie_root,label_name,count);
        }
        count++;
    }
    free(line1);
    line1 = NULL;
    return 0;
}