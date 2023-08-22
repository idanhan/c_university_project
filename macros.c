#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include"define.h"
/*is blank finds blank lines and if the line is blank macro_lay will ignore it*/
bool is_blank(char* str)
{
    bool is_word = false;
    int i = 0;
    if(str == NULL)
    {
        return true;
    }
    while (str[i] != '\n' && str[i] != EOF)
    {
        if (str[i] == ';')
        {
            return is_word;
        }
        
        if(isspace(str[i])==0)
        {
            is_word = true;
            break;
        }
        i++;
    }
    return is_word;
}
/*this function takes as input file pointer and file name and creates a file without blank lines and replace
the macros*/
int macro_lay(FILE *ifp,char* file_name)
{
    long int pos,pos2,pos4=0;
    int c;
    struct macs
    {
        char name[MAX_LINE];
        long int start_line;
        long int end_line;
        struct macs *next;
    };
    typedef struct macs Macs; 
    char *line = malloc(MAX_LINE*(sizeof(char)));
    if (line == NULL)
    {
        printf("memory allocation failed\n");
        return ERROR;
    }
    short int is_mac = 0;
    FILE *ofp;
    char word[MAX_LINE];
    Macs *curr= NULL,*head = NULL,*temp2= NULL,*temp1 = NULL;
    short int mac_in=0;
    fseek(ifp,0,SEEK_SET);
    while((pos4=ftell(ifp))!= -1 && fgets(line,MAX_LINE,ifp)!=NULL)
    {
        if(is_mac == 1)
        {
            if(strstr(line,"endmcro")!=NULL)/*close the macro definition*/
            {
                curr->end_line = pos4 - 1 ;
                is_mac = 0;
            }
        }
        if (strstr(line,"mcro")!=NULL && strstr(line,"endmcro")==NULL)/*start of macro*/
        {
            pos = ftell(ifp);
            curr = (Macs*)(malloc(sizeof(Macs)));
            curr->next = head;
            head = curr;
            strtok(line," \t");
            strcpy(word,strtok(NULL," \t"));
            pos2 = ftell(ifp);
            curr->start_line = pos2;
            strcpy(curr->name,word);
            is_mac = 1;
            fseek(ifp,pos,SEEK_SET);
        }
    }
    fseek(ifp,33,SEEK_SET);
    ofp = fopen(file_name,"w+");
    if(ofp == NULL)
    {
        printf("can't open file\n");
        return ERROR;
    }
    fseek(ifp,0,SEEK_END);
    fprintf(ifp,"\n");
    fseek(ifp,0,SEEK_SET);
    while ((pos4=ftell(ifp))!= -1 && fgets(line,MAX_LINE,ifp)!=NULL)
    {
        if (strlen(line)>MAX_LINE)
        {
            continue;
        }
        
        if(!is_blank(line))
        {
            continue;
        }
        temp2 = head;
        while (temp2)
        {
            if (strstr(line,temp2->name)!=NULL && strstr(line,"mcro")==NULL)/*line without macros*/
            {
                fseek(ifp,temp2->start_line,SEEK_SET);
                while ((c=getc(ifp))!=EOF && ftell(ifp) <= (temp2->end_line))
                {
                    fputc(c,ofp);
                }
                fprintf(ofp,"\n");
                mac_in = 1;
                fseek(ifp,pos4,SEEK_SET);
                fgets(line,MAX_LINE,ifp);
                break;
            }
            if(strstr(line,"mcro")!=NULL && strchr(line,':')==NULL && strstr(line,temp2->name)!=NULL)
            /*if there is mcro in line and its not some label then denotes as begging of a*/
            {
                fseek(ifp,temp2->end_line,SEEK_SET);
                if(fgets(line,MAX_LINE,ifp)==NULL)
                {
                    fseek(ifp,pos4,SEEK_SET);
                }
                mac_in = 1;
                break;
            }
            temp2 = temp2->next;
        }
        if(strstr(line,"mcro")==NULL && mac_in == 0)
        {
            fprintf(ofp,"%s",line);
        }
        mac_in = 0;
    }
    while (curr)/*free linked list*/
    {
        temp1 = curr;
        curr = curr->next;
        free(temp1);
    }
    fclose(ofp);
    free(line);
    return 0;
}