#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include"define.h"
#include"trie.h"
#include"declerations.h"

int num_char_in_line(char* word,char c)
{
    if (word == NULL)
    {
        return 0;
    }
    int i = 0;
    int len = strlen(word);
    int count = 0;
    while (i < len)
    {
        if (word[i]==c)
        {
            count++;
        }
        i++;
    }
    return count;
    
}

/*this function is for identifying and making the data image */
int data_table(FILE* ifp,Vector* vec,int start,trienode *root,trienode **data_root,trienode *externroot,trienode **ext_out,Vector* vec_ex,char* filename)
{
    char* line = malloc(MAX_LINE *sizeof(char));
    char* first_name=NULL;
    char* sec_name=NULL;
    char* num = NULL;
    char* num_ptr = NULL;
    char* temp = NULL;
    short int check = 0;
    short int ptr1;
    short int ptr2;
    bool is_neg = false;
    int num1;
    int count = 0;
    int len;
    int len2;
    bool is_ptr1;
    bool is_ptr2;
    int i = 0;
    char* rest = NULL;
    char line_cpy[MAX_LINE] = "";
    start = start + 100;
    fseek(ifp,0,SEEK_SET);
    while (fgets(line,MAX_LENGTH,ifp)!=NULL)/*go thorugh the file after macros layout*/
    {
        strcpy(line_cpy,line);   
        first_name = strtok(line," \t");
        if(strchr(first_name,':')!=NULL)/*identify the labels by : character*/
        {
            sec_name = strtok(NULL," \t");
            if (strcmp(sec_name,".data")==0 || strcmp(sec_name,".string")==0)
            {
                len = strlen(first_name);
                first_name[len-1] = '\0';
                trieinsert(data_root,first_name,start);/*insert data labels to data label trie*/
            }
            if (strcmp(sec_name,".data")==0)
            {
                while ((num = strtok(NULL," ,\t"))!=NULL)
                {
                    if((temp = strchr(num,'-'))!=NULL || (temp = strchr(num,'+'))!=NULL)
                    {
                    if (strchr(num,'-')!=NULL)
                    {
                        is_neg = true;
                    }
                        num = temp +1;
                    }
                   if(isdigit(*num))
                    {
                        num1 = (short int)strtol(num,&num_ptr,10);
                        if (is_neg)
                        {
                            num1 = -num1;
                            is_neg = false;
                        }
                        vectorPushBack(vec,num1);
                        start++;
                    }
                    else/*if not a number return error*/
                    {
                        printf("not a number in .data line: %d filename: %s\n",start,filename);
                        return ERROR;
                    }
                }
                
            }
            if (strcmp(sec_name,".string")==0)/*if the first word is just .string so the string will not be saved 
            the line count will go on*/
            {
                i = 1;
                if((strchr(line_cpy,'\"'))==NULL)
                {
                    continue;
                }
                rest = strchr(line_cpy,'\"');
                if (num_char_in_line(rest,'\"')!=2)/*if the number of parentheses isnt 2 return error
                this is also the case with no string at all*/
                {
                    printf("number of parentheses is wrong line: %d filename: %s\n",start,filename);
                    return ERROR;
                }
                
                len2 = strlen(rest);
                rest[len2] = '\0';
                while (rest[i] != '\"')
                {
                    if((rest[i]!='\"') &&  ((int)rest[i])!=0 && ((int)(rest[i])>=0))
                    {
                        vectorPushBack(vec,(short int)rest[i]);
                        start++;
                    }
                    i++;
                }
                vectorPushBack(vec,0);
                start++;
            }

        }
        else if(strcmp(first_name,".data")==0)/*if the first word is .data without label
        then the data isnt inserted into data image but the line counts continues*/
        {
             while ((num = strtok(NULL," ,\t"))!=NULL)
                {
                    if((temp = strchr(num,'-'))!=NULL || (temp = strchr(num,'+'))!=NULL)
                    {
                    if (strchr(num,'-')!=NULL)
                    {
                        is_neg = true;
                    }
                        num = temp +1;
                    }
                   if(isdigit(*num))
                    {
                        num1 = (short int)strtol(num,&num_ptr,10);
                        if (is_neg)
                        {
                            num1 = -num1;
                            is_neg = false;
                        }
                        start++;
                    }
                    else
                    {
                        printf("not a number in .data line: %d filename: %s\n",start,filename);
                        return ERROR;
                    }
                }
        }
        else if (strcmp(first_name,".string")==0)/*if the first word is .string without label
        then the data isnt inserted into data image but the line counts continues*/
        {
            if (strcmp(sec_name,".string")==0)
            {
                i = 1;
                
                if((strchr(line_cpy,'\"'))==NULL)
                {
                    continue;
                }
                rest = strchr(line_cpy,'\"');
                if (num_char_in_line(rest,'\"')!=2)
                {
                    printf("number of parentheses is wrong line: %d filename: %s\n",start,filename);
                    return ERROR;
                }
                len2 = strlen(rest);
                rest[len2] = '\0';
                while (rest[i] != '\"')
                {
                    if((rest[i]!='\"') &&  ((int)rest[i])!=0 && ((int)(rest[i])>=0))
                    {
                        start++;
                    }
                    i++;
                }
                vectorPushBack(vec,0);
                start++;
            }
        }
    }
    fseek(ifp,0,SEEK_SET);
    while (fgets(line,MAX_LENGTH,ifp)!=NULL)/*this part is for update the whole vector with the data image and istructions
     image to one part and update the externs trie*/
    {
        is_ptr1 = false;
        is_ptr2 = false;
        check = command_line_interpeter(line,&ptr1,&ptr2,&is_ptr1,&is_ptr2,root,&count,2,data_root,&vec,externroot,ext_out,&vec_ex,NULL);
        if (check == ERROR)
        {
            return ERROR;
        }
        
    }
    free(line);
    line = NULL;
    return 0;
}