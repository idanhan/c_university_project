#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include"define.h"
#include"trie.h"
#include"declerations.h"
/*function that recives combined vector of data and instructions and the size of instructions and size of data
the file name if status equals -1 the function will not make an object file because there is some prolem with the input*/
void create_obj(Vector *vec,int instruction_num,int data_num,char* name,int status)
{
    int line_num = 0;
    int len;
    FILE* ofp;
    short int ori_num;
    short int num1;
    short int num2;

    char list_64[64] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'};
    if (status==ERROR)
    {
        return;
    }
    
    if(vec != NULL)
    {
        len = vectorTotal(vec);
        ofp = fopen(name,"w");
        fprintf(ofp,"%d %d\n",instruction_num,data_num);
        while (line_num < len)
        {
            ori_num = vectorGet(vec,line_num);
            num1 = (ori_num & 63);/*this and the next line code the lines in 64 base*/
            num2 = (ori_num >> 6)&63;
            fprintf(ofp,"%c %c\n",list_64[num2],list_64[num1]);
            line_num++;
        }
        fclose(ofp);
    }
}