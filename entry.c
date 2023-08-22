#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include"define.h"
#include"trie.h"
#include"declerations.h"
/*in this function if there isnt an error in the first or second transition the object file is made. i used strtok 
and in made sure there is no whitespaces when finding the word in trienode*/
void entry_obj(FILE *ifp,Vector *vec,trienode *root,trienode *data_root,char* file_name,int status)
{
    char* line = malloc(MAX_LINE*sizeof(char));
    char* first = NULL;
    char* second= NULL;
    char* third = (char*)malloc(MAX_LINE * sizeof(char));
    int line_num = 0;
    int len = 0;
    FILE* ofp;
    trienode *entry_root =NULL;
    if (status == ERROR)
    {
        return;
    }
    
    fseek(ifp,0,SEEK_SET);
    while (fgets(line,MAX_LINE,ifp)!=NULL)
    {
        first = strtok(line," \t");
        if (strcmp(first,".entry") == 0)
        {
            second = strtok(NULL," \t\n");
            len = strlen(second);
            if (isspace(second[len-1]))
            {
                second[len-1] = '\0';/*this is to maked sure there is no whitespace after the word ends*/
            }
            if((line_num = findtiref(root,second))!=0)
            {             
                trieinsert(&entry_root,second,line_num);
            }
            else if((line_num = findtiref(data_root,second))!=0)
            {            
                trieinsert(&entry_root,second,line_num);
            }   
        }
        else
        {
            continue;
        }
        
    }
    if (entry_root !=NULL)
    {
        ofp = fopen(file_name,"w");
        fprinttrie(ofp,entry_root);
        fclose(ofp);
    }
    freeTrie(entry_root);
    free(line);
    line = NULL;
    free(third);
    third = NULL;
}