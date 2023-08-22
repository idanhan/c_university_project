#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include"define.h"
#include"trie.h"
#include"declerations.h"
/*this function take as an input file object which is the file after macros layout root which is all the labels in the file
and a vector vec which contains the labels line num as well as status which tells the function if to make the 
extern file or not(in case status equals -1) and a file name to correctly name the output file.*/
int extern_out(FILE *ifp,trienode *root,char* file_name,Vector* vec,int status,trienode* label_root)
{
    if (status == ERROR)
    {
        return ERROR;
    }
    FILE* ofp;
    char* first_name = NULL;
    char* second_name = NULL;
    int len_num = 0;
    int len = 0;
    int num = 0;
    char* line = malloc(MAX_LINE*sizeof(char));
    if (line==NULL)
    {
        printf("memory allocation failed\n");
        return ERROR;
    }
    
    if (root!=NULL)
    {
        ofp = fopen(file_name,"w");
        if (ofp==NULL)
        {
            printf("cant open file");
            return ERROR;
        }
    }
    else{return 0;}
    fseek(ifp,0,SEEK_SET);
    while (fgets(line,MAX_LINE,ifp)!=NULL)
    {
        first_name = strtok(line," \t");
        if(strchr(first_name,':')!=NULL || strstr(first_name,".entry")!=NULL || strstr(first_name,".extern")!=NULL || strstr(first_name,".data")!=NULL||strstr(first_name,".string")!=NULL)
        {
            continue;
        }
        else
        {
            second_name = strtok(NULL," \t\n");
            if (second_name!=NULL)
            { 
                len = strlen(second_name);
                if (isspace(second_name[len-1]))/*makes sure there is no whitespaces in second_name*/
                {
                    second_name[len-1] = '\0';
                }
                if ((len_num = findtiref(root,second_name))!=0)
                {
                    fprintf(ofp,"%s %hd\n",second_name,100 + vectorGet(vec,num++));
                }               
            }
            
        }
    }
    fclose(ofp);
    free(line);
    line = NULL;
    return 0;
}