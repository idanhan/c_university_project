#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include"trie.h"
#include"define.h"
#include"declerations.h"

/*main file first gets */
int main(int argc, char const *argv[])
{
    FILE *ifp1,*new2;
    trienode *root2 = NULL;
    int i=0;
    trienode *data = NULL;
    trienode *label_root1 = NULL;
    trienode *entry_root = NULL;
    trienode *extern_root = NULL;
    Vector vectorIC;
    Vector vec_ex;
    trienode *ext_out = NULL;
    char file_name[MAX_LINE] ="";
    char file_name2[MAX_LINE] ="";
    char file_name3[MAX_LINE] ="";
    char file_name4[MAX_LINE] ="";
    char file_name5[MAX_LINE] ="";
    char* temp_name;
    int temp_len=0;
    int status = 0;
    int macro_status = 0;
    int instruct_len;
    int data_len;
    for (; i < argc-1; i++)/*going through all the files*/
    {
        entry_root = NULL;
        status = 0;
        macro_status = 0;
        ext_out = NULL;
        vector_init(&vectorIC);
        vector_init(&vec_ex);
        root2 = NULL;
        data = NULL;
        label_root1 = NULL;
        extern_root = NULL;
        if((ifp1 = fopen(argv[i+1],"a+"))==NULL)/*if file cant open go to next one*/
        {
            printf("can't open file");
            continue;
        }
        if(strstr(argv[i+1],".as")==NULL)/*if file dosent have .as go to next file*/
        {
            printf("file name dosent have .as");
            continue;
        }
        if(strlen(argv[i+1])>MAX_LINE)/*if filename is too long go to next file*/
        {
            printf("error: file name is too long"); 
            continue;
        }
        strcpy(file_name,argv[i+1]);
        temp_name = strchr(argv[i+1],'.');
        temp_len = strlen(temp_name);
        temp_len = strlen(argv[i+1]) - temp_len;
        file_name[temp_len] = '\0';
        strcpy(file_name2,file_name);/*this filenames is for different ouput files*/
        strcat(file_name2,".txt");
        strcpy(file_name3,file_name);
        strcat(file_name3,".ent.txt");
        strcpy(file_name4,file_name);
        strcat(file_name4,".ext.txt");
        strcpy(file_name5,file_name);
        strcat(file_name5,".ob.txt");
        macro_status = macro_lay(ifp1,file_name2);
        if (macro_status == ERROR)
        {
            continue;
        }
        new2 = fopen(file_name2,"r");
        if(new2 == NULL)
        {
            printf("can't open file");
        }
        if(labels_table(new2,&root2)==ERROR){continue;}
        fseek(new2,0,SEEK_SET);
        if (extern_obj(new2,&extern_root) == ERROR)
        {
            continue;
        }
        status = command_line_file(new2,root2,&vectorIC,&label_root1,extern_root,file_name);
        if (status == ERROR)
        {
            continue;
        }
        
        instruct_len = vectorTotal(&vectorIC);
        if (data_table(new2,&vectorIC,vectorTotal(&vectorIC),root2,&data,extern_root,&ext_out,&vec_ex,file_name) == ERROR)
        {
            continue;
        }
        entry_obj(ifp1,&vectorIC,label_root1,data,file_name3,status);
        if (extern_out(ifp1,ext_out,file_name4,&vec_ex,status,label_root1)==ERROR)
        {
            continue;
        } 
        data_len = vectorTotal(&vectorIC) - instruct_len;    
        create_obj(&vectorIC,instruct_len,data_len,file_name5,status);/*creates object file*/
        vectorFree(&vectorIC);/*free all the tries and vectors*/
        fclose(ifp1);
        ifp1 = NULL;
        fclose(new2);
        freeTrie(root2);
        freeTrie(label_root1);
        freeTrie(data);
        freeTrie(entry_root);
        freeTrie(extern_root);
        freeTrie(ext_out);
        }
    return 0;
}
