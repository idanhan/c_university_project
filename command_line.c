#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include"define.h"
#include"trie.h"
#include"declerations.h"

/*in this file there are 2 functions command_line_interpeter which is the main function that counts the line number 
as a function of the translated lines and then returns the line interpeted and it takes two pointers to pointers
and sets them to the arguments of the line source and destination command_line_file takes the returned parameters destination 
and source and insert them in a vector data structure which is the data set for the instruction image. if there is an error
object file externs and entries files will not be made and the program will move to the next file. other functions like datatable 
use command_line_interpeter to count the lines as directed and return source and destination parameters*/

short int command_line_interpeter(char* a,short int *ptr1,short int *ptr2,bool *is_ptr1,bool *is_ptr2,trienode *root,int *count,int state,trienode **root_label,Vector** vec,trienode *extern_root,trienode **ex_out_root,Vector** vec_ex,char* filename)
{
    char *command = NULL;
    char *destination=NULL;
    char *source = NULL;
    int temp_count = 0;
    char *m_ptr1=NULL,*m_ptr2=NULL;
    char *str_dest=NULL,*str_source=NULL;
    bool is_oger1=false,is_oger2=false,is_num1=false,is_num2=false,is_label_dest = false,is_label_ori = false;
    bool is_one_out = false;
    bool is_lea = false;
    bool is_dest_neg = false;
    bool is_ori_neg = false;
    bool is_data_dest = false;
    bool is_data_ori = false;
    bool is_extern = false;
    short ARE=0,dest=0,opcode=0,origin=0;
    short i=0,j=0;
    int num_line_dest=0,num_line_ori = 0;
    short command_num;
    int length=0,len2=0;
    char temp[MAX_LINE] = "";
    if(strstr(a,".data")!=NULL || strstr(a,".string")!=NULL || strstr(a,".entry")!=NULL || strstr(a,".extern")!=NULL)
    {
        return 0;
    }/*data string entry and extern are handeled elsewhere*/
    command = strtok(a," \t\n\0");
    char register_list[MAX_REG][MAX_WORD] = {"@r0","@r1","@r2","@r3","@r4","@r5","@r6","@r7"};/*registr list*/
    char commands_list[MAX][MAX_WORD] = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};/*command list*/
    short int num_to_point1,num_to_point2;
    int n_dest=0,n_ori=0;   
    if (strchr(command,':'))/*labels inserted to trie*/
    {   
        if(state == 0)
        {
            strcpy(temp,command);
            length = strlen(temp);
            temp[length-1] = '\0';
            temp_count = *count;
            if (root_label!=NULL &&  temp!=NULL && findtiref(*root_label,temp)!=0)
            {
                printf("insert the same label name twice line: %d filename: %s\n",*count,filename);
                return ERROR;
            }
            if (temp!=NULL && (((int)temp[0] < 65) || ((int)temp[0]>90 && (int)temp[0]<97)))
            {
                printf("label name is not valid line: %d filename: %s \n",*count,filename);
                return ERROR;
            }
            
            trieinsert(root_label,temp,temp_count);
        }
        command = strtok(NULL," \t\n\0");/*if the first word is a label this recognizes the command after*/
        if (command == NULL)
        {
            if (state == 0)/*if there is no word after label then return a error message and the program 
            dosent */
            {
                printf("no input after label line: %d file_name: %s\n",*count,filename);
            }
            return ERROR;
        }
        
    }
    if (command!=NULL)/*strip the word from whitepaces*/
    {
        len2 = 0;
        while (!isspace(command[len2]))
        {
            if(len2 == strlen(command)){break;}
            len2++;
        }
        command[len2] = '\0';
    }
    for ( ; i < MAX; i++)/*search in the command list*/
    {
        if(strcmp(command,commands_list[i])==0)
        {
            opcode = i;
            break;
        }
    }
    if(strchr(command,':') == NULL && i >= MAX)
    /*if the first line is not a command and not a label return error in here i do not handle data so 
    .srting or .data are not relevant*/
    {
        if (state==0)
        {
           printf("undefined  variable line count: %d file_name: %s\n",*count,filename);
        }
        
        return ERROR;
    }
    source = strtok(NULL,", \t");
    destination = strtok(NULL,", \t");
    if (destination!=NULL)
    {
        len2 = 0;
        while (!isspace(destination[len2]))
        {
            if(len2 == strlen(destination)){break;}
            len2++;
        }
        destination[len2] = '\0';
    }
    if (source!=NULL)
    {
        len2 = 0;
        while (!isspace(source[len2]))
        {
            if(len2 == strlen(source)){break;}
            len2++;
        }
        source[len2] = '\0';
    }
    
    switch (opcode)/*making sure that the parameters matches the criteria in the instructions*/
        {
        case 0:
            is_one_out = true;
            break;
        case 2:
            is_one_out = true;
            break;
        case 3:
            is_one_out = true;
            break;
        case 4:
            if(destination != NULL)
            {
                if (state == 0)
                {
                printf("in this not method, there is no destinataion operand line:%d file: %s\n",*count,filename);
                }
                return ERROR;
            }
            break;
        case 5:
            if(destination != NULL)
            {
                if (state == 0)
                {
                    printf("in clr method, there is no destinataion operand line:%d file: %s\n",*count,filename);
                }
                return ERROR;
            }
            break;
        case 6:
            is_one_out = true;
            is_lea = true;
            break;
        case 7:
            if(destination != NULL)
            {
                if (state ==0)
                {
                    printf("in inc method, there is no destinataion operand line:%d file: %s\n",*count,filename);
                }
                
                return ERROR;
            }
            break;
        case 8:
            if(destination != NULL)
            {
                if (state==0)
                {
                    printf("in dec method, there is no destinataion operand line:%d file: %s\n",*count,filename);
                }
                
                return ERROR;
            }
            break;
        case 9:
            if(destination != NULL)
            {
                if (state==0)
                {
                    printf("in jmp method, there is no destinataion operand line:%d file: %s\n",*count,filename);
                }
                
                return ERROR;
            }
            break;
        case 10:
            if(destination != NULL)
            {
                if (state==0)
                {
                    printf("in bne method, there is no destinataion operand line:%d file: %s\n",*count,filename);
                }
                
                return ERROR;
            }
            break;
        case 11:
            if(destination != NULL)
            {
                if (state==0)
                {
                    printf("in red method, there is no destinataion operand line:%d file: %s\n",*count,filename);
                }
                
                return ERROR;
            }
            break;
        case 12:
            if(destination != NULL)
            {
                if (state==0)
                {
                    printf("in prn method, there is no destinataion operand line:%d file: %s\n",*count,filename);
                }
                
                return ERROR;
            }
            break;
        case 13:
            if(destination != NULL)
            {
                if (state == 0)
                {
                    printf("in prn method, there is no destinataion operand line:%d file: %s\n",*count,filename);
                }
                
                return ERROR;
            }
            break;
        case 14:
            if (destination !=NULL)
            {
                if (state == 0)
                {
                    printf("in rts method, there is no destinataion operand line:%d file: %s\n",*count,filename);
                }
                
                return ERROR;
            }
            if(source != NULL)
            {
                if (state==0)
                {
                    printf("in prn method, there is no source operand line:%d file: %s\n",*count,filename);
                }
                
                return ERROR;
            }
            break;
        case 15:
            if (destination !=NULL)
            {
                if (state ==0)
                {
                    printf("in stop method, there is no destinataion operand line:%d file: %s\n",*count,filename);
                }
                
                return ERROR;
            }
            if(source != NULL)
            {
                if (state==0)
                {
                    printf("in stop method, there is no source operand line:%d file: %s\n",*count,filename);
                }
                
                return ERROR;
            }
            break;
        default:
            break;
    }
    if(source == NULL && destination == NULL && command == NULL)
    {
        return 0;
    }
    while (j<MAX_REG)/*searching for the registers operands in the registers list*/
    {
        if (source == NULL && destination ==NULL)
        {
            break;
        }
        
        if(destination!= NULL && strcmp(destination,register_list[j])==0)
        {
            dest = 5;
            is_oger1 = true;
            n_dest = j;
        }
        if(source != NULL && strcmp(source,register_list[j])==0)
        {
            if(is_lea)/*lea cannot have a register operand*/
            {
                if (state==0)
                {
                    printf("there is no register in source operand with lea method line:%d file: %s\n",*count,filename);
                }
                return ERROR;
            }
            else
            {
                origin = 5;
                is_oger2 = true;
                n_ori = j;
            }
        }
        j++;
    }
    if(destination!=NULL && ((str_dest = strchr(destination,'-'))!=NULL || (str_dest = strchr(destination,'+'))!=NULL))
    /*if the numbers have plus or minus signs get rid of + or insert minus the right way*/
    {
        if ((strchr(destination,'-'))!=NULL)
        {
            is_dest_neg = true;
        }
        destination = str_dest +1;
    }
    if(dest!=5 && destination!=NULL && isdigit(*destination))
    {
        if (!is_one_out)
        {
            dest = 1;
            is_num1 = true;
            n_dest = (int)strtol(destination,&m_ptr1,10);
            if(is_dest_neg==true)
            {
                n_dest = -n_dest;
            }
        }
        else
        {/*in this methods there is no digit*/
            if (state==0)
            {
                printf("in this method there is no imediate addressing for the destinataion operand line:%d file: %s\n",*count,filename);
            }
            return ERROR;
        }
    }
    if(source!=NULL && ((str_source = strchr(source,'-'))!=NULL || (str_source = strchr(source,'+'))!=NULL))
    {
        if ((strchr(source,'-'))!=NULL)
        {
            is_ori_neg = true;
        }
        source = str_source +1;
    }
    if (origin != 5 && source !=NULL && isdigit(*source))
    {
        origin = 1 ;
        is_num2 = true;
        n_ori = (short int)strtol(source,&m_ptr2,10);
        if(is_ori_neg==true)
        {
            n_ori = -n_ori;
        }
    }
    if(dest != 1 && dest !=5 && destination !=NULL)
    {/*if the operands are labels or externs*/
        if((findtiref(root,destination))!=0 && (state == 0|| state == 2))
        {
            num_line_dest = findtiref(root,destination);
            dest = 3;
            is_label_dest = true;
        } 
        if ((findtiref(root,destination))!=0 && state == 1)
        {
            num_line_dest = findtiref(*root_label,destination);
            dest = 3;
            is_label_dest = true;
        }
        if ((findtiref(*root_label,destination))!=0 && state == 2)
        {
            num_line_dest = findtiref(*root_label,destination);
            dest = 3;
            is_label_dest = true;
            is_data_dest = true;
        }
    }
    if(origin != 1 && origin !=5 && source !=NULL)
    {
        if((findtiref(root,source))!=0 && (state == 0 || state == 2))
        {
            num_line_ori = findtiref(root,source);
            origin = 3;
            is_label_ori = true;
        } 
        if((findtiref(root,source))!=0 && state == 1)
        {
            num_line_ori = findtiref(*root_label,source);
            origin = 3;
            is_label_ori = true;
        } 
        if ((findtiref(*root_label,source))!=0 && state == 2)
        {
            num_line_ori = findtiref(*root_label,source);
            origin = 3;
            is_label_ori = true;
            is_data_ori = true;
        }
        if(extern_root!=NULL && findtiref(extern_root,source)!=0 )
        {
            is_extern = true;
            origin = 3;
        }
    }
    if(is_oger1 == true && is_oger2 == true)
    {
        num_to_point1 = ARE;
        num_to_point1 |= (n_dest<<2);
        num_to_point1 |= (n_ori<<7);
        *is_ptr1 = true;
        *ptr1 = num_to_point1;
    }
    if(is_oger1 == true && is_num2 == true)
    {
        num_to_point1 = ARE;
        num_to_point2 = ARE;
        num_to_point1 |= (n_dest<<2);
        num_to_point2  |= (n_ori<<2);
        *is_ptr1 = true;
        *is_ptr2 = true;        
        *ptr2 = num_to_point1;
        *ptr1 = num_to_point2;
    }
    if(is_num1 == true && is_oger2 == true)
    {
        num_to_point1 = ARE;
        num_to_point2 = ARE;
        num_to_point1 |= (n_dest<<2);
        num_to_point2 |= (n_ori<<2);
        *is_ptr1 = true;
        *is_ptr2 = true;
        *ptr2 = num_to_point1;
        *ptr1 = num_to_point2;
    }
    if(is_num1 == true && is_num2 == true)
    {
        num_to_point1 = ARE;
        num_to_point2 = ARE;
        num_to_point1 |= (n_dest<<2);
        num_to_point2 |= (n_ori<<2);
        *is_ptr1 = true;
        *is_ptr2 = true;
        *ptr2 = num_to_point1;
        *ptr1 = num_to_point2;
    }
    if(is_label_dest==true  && is_num2 == true)
    {
        num_to_point1 =  2;
        num_to_point2 = ARE;
        num_to_point1 |= (num_line_dest<<2); 
        num_to_point2 |= (n_ori<<2);
        *is_ptr1 = true;
        *is_ptr2 = true;
        *ptr2 = num_to_point1;
        *ptr1 = num_to_point2;
    }
    if(is_label_ori==true  && is_num1 == true)
    {
        num_to_point2 =  2;
        num_to_point1 = ARE;
        num_to_point2 |= (num_line_ori<<2);
        num_to_point1 |= (n_dest<<2);
        *is_ptr1 = true;
        *is_ptr2 = true;
        *ptr2 = num_to_point1;
        *ptr1 = num_to_point2;
    }
    if(is_label_ori==true  && is_oger1 == true)
    {
        num_to_point1 =  2;
        num_to_point2 = ARE;
        num_to_point1 |= (num_line_ori<<2);
        num_to_point2 |= (n_dest<<2);
        *is_ptr1 = true;
        *is_ptr2 = true;
        *ptr1 = num_to_point1;
        *ptr2 = num_to_point2;
    }
    if(is_label_dest==true  && is_oger2 == true)
    {
        num_to_point1 =  2;
        num_to_point2 = ARE;
        num_to_point1 |= (num_line_dest<<2);
        num_to_point2 |= (n_ori<<7);
        *is_ptr1 = true;
        *is_ptr2 = true;
        *ptr2 = num_to_point1;
        *ptr1 = num_to_point2;
    }
    if (is_label_ori== true && is_num1 == false && is_num2 == false && is_oger1 == false && is_oger2 == false && is_label_dest == false)
    {
        num_to_point1 = 2;
        num_to_point1 |= (num_line_ori << 2);
        *is_ptr1 = true;
        *ptr1 = num_to_point1;
        dest = origin;
        origin = 0;
    }
    if(is_num2==true && is_num1 ==false && is_label_dest == false && is_label_ori == false && is_oger1== false && is_oger2 ==false)
    {
        num_to_point1 = ARE;
        num_to_point1 |= (n_ori<<2);
        *is_ptr1 = true;
        *ptr1 = num_to_point1;
        dest = origin;
        origin = 0;
    }
    if(is_oger2 ==true && is_num2 ==false && is_label_dest == false && is_label_ori == false && is_num1 == false && is_oger1 ==false)
    {
        num_to_point1 = ARE;
        num_to_point1 |= (n_ori<<2);
        *is_ptr1 = true;
        *ptr1 = num_to_point1;
        dest = origin;
        origin = 0;
    }
    if(is_extern == true && is_oger2 == false && is_num2 ==false && is_label_dest == false && is_label_ori == false && is_num1 == false && is_oger1 ==false)
    {
        num_to_point1 = 1;
        *is_ptr1 = true;
        *ptr1 = num_to_point1;
        dest = origin;
        origin = 0;
    }
    if(state == 0 || state == 2)
    {
        if(*is_ptr1 == true && ptr1 != NULL)
        {
            if(is_data_ori==true && state == 2)
            {
                vectorSet(*vec,*count+1,(num_line_ori<<2) + 2);
            }
            if(is_extern == true && state == 2)
            {
                trieinsert(ex_out_root,source,*count+1);
                vectorPushBack(*vec_ex,*count+1); 
            }
            *count = *count + 1;
        }
        if(*is_ptr2 == true && ptr2 !=NULL){
            if(is_data_dest==true && state == 2)
            {
                vectorSet(*vec,*count+1,(num_line_dest<<2) + 2);
            }
            *count = *count + 1;
        }
        *count = *count + 1;
    }
    if (*count>1024)/*if the number of lines exceeds the limit stop and return a error*/
    {
        if (state==0 || state ==2)
        {
            printf("number of lines in file is over 1024 file: %s",filename);
        }
        return ERROR;
    }
    
    command_num = ARE;
    command_num |= (dest<<2);
    command_num |= (opcode<<5);
    command_num |= (origin<<9);
    return command_num;
}

int command_line_file(FILE* ifp,trienode *root,Vector* vector,trienode** trieroot,trienode *extern_root,char* filename)
{   
    bool is_ptr1=false;
    bool is_ptr2=false;
    short int ptr1 = 0,ptr2=0;
    int count = 100;
    short int line_interpeted = 0;
    short int line_for_check = 0;

    char* line = (char*)malloc(MAX_LENGTH * (sizeof(char)));
    if(line == NULL)
    {
        printf("MEMORY ALLOCATION FAILED line:%d file: %s\n",count,filename);
        return ERROR;
    }
    fseek(ifp,0,SEEK_SET);
    while (fgets(line,MAX_LENGTH,ifp)!=NULL)
    {
        is_ptr1 = false;
        is_ptr2 = false;
        line_for_check = command_line_interpeter(line,&ptr1,&ptr2,&is_ptr1,&is_ptr2,root,&count,0,trieroot,NULL,extern_root,NULL,NULL,filename);
        /*first try, reads the labels and updates the numbering otf the labels*/
        if (line_for_check == ERROR)
        {
            return ERROR;
        }
    }
    fseek(ifp,0,SEEK_SET);
    while (fgets(line,MAX_LENGTH,ifp)!=NULL)
    {
        is_ptr1 = false;
        is_ptr2 = false;
        line_interpeted = command_line_interpeter(line,&ptr1,&ptr2,&is_ptr1,&is_ptr2,root,&count,1,trieroot,NULL,extern_root,NULL,NULL,filename);
        /*second try, reads the operands and lines and updates the numbering of vector*/
        if (line_interpeted==ERROR)
        {
            return ERROR;
        }
        if(line_interpeted!=0)
        {
            vectorPushBack(vector,line_interpeted);
        }
        if(is_ptr1 == true)
        {
            vectorPushBack(vector,ptr1);
        }
        if(is_ptr2 == true)
        {
            vectorPushBack(vector,ptr2);
        }
    }
    free(line);
    return 0;
}
