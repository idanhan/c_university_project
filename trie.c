#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_LENGTH 256
/*this is a trie data structure tieh some functions related to trie is_word signels end of a complete word
and children is the letters of all the words chose this data structure because in insert and find its O(m) 
m is the length of the word were inserting or lookin for*/
typedef struct trienode
{
    int line_num;  
    bool is_word;
    struct trienode *children[MAX_LENGTH];
}trienode;

trienode *createnode()/*helps the function insert node in the way that its making room for allocation*/
{
    int i;
    trienode *newnode = malloc(sizeof(*newnode));
    for (i = 0; i < MAX_LENGTH; i++)
    {
        newnode->children[i]=NULL;
    }
    newnode->is_word = false;/*is not the end of the word*/
    return newnode;
}

bool trieinsert(trienode **root,char *signedtext,int line_n)/*insert a character to the right place in a word
if a word is inserted twice or more it will only be saved once*/
{
    int i;
    if(*root==NULL)
    {
        *root = createnode();
    }
    unsigned char *text =(unsigned char *)signedtext;
    trienode *tmp = *root;
    int length = strlen(signedtext);
    for(i =0; i < length;i++)
    {   
        if (isspace(text[i]))
        {
            i++;
            continue;
        }
        if(tmp->children[text[i]]==NULL)
        {
            tmp->children[text[i]] = createnode(); 
        }
        tmp = tmp->children[text[i]]; 
    }
    if (tmp->is_word)
    {
        return false; 
    }
    else
    {
        tmp->line_num = line_n;
        tmp->is_word = true;
        return true;
    }

}

void printtrie_rec(trienode *node, unsigned char *prefix,int length)
{
    int j;
    unsigned char newprefix[length+2];
    memcpy(newprefix,prefix,length);
    newprefix[length+1] = 0;
    if (node->is_word)
    {
        printf("word: %s line_num: %d \n",prefix,node->line_num);
    }
    for(j=0;j<MAX_LENGTH;j++)
    {
        if (node->children[j] != NULL)
        {
            newprefix[length] = j;
            printtrie_rec(node->children[j],newprefix,length+1); 
        }
        
    }
}

void printtrie(trienode *root)
{
    if(root == NULL)
    {
        printf("no labels were added!\n");
        return;
    }
    printtrie_rec(root,NULL,0);
}


int findtiref(trienode *root,char *word)/*function to find words if exists in the trie, if the word 
is in trie return its num line else return 0*/
{
    if (root == NULL)
    {
        return 0;
    }
    int i =0;
    int len = strlen(word);
    unsigned char* text = (unsigned char*)word;
    for (i = 0; i < len; i++)
    {
        if(root->children[text[i]]==NULL)
        {
            break;
        }
        else
        {
            root = root->children[text[i]];
        }
    }
    if(i == len){return root->line_num;}
    else{return 0;}
}

bool node_has_children(trienode* node)
{
    int i;
    if (node == NULL)
    {
        false;
    }

    for(i=0;i<MAX_LENGTH;i++)
    {
        if(node->children[i] != NULL)
        {
            return true;
        }
    }
    return false;
}

trienode* deleteStr_rec(trienode* node,unsigned char* text,bool *deleted)
{
    if(node == NULL) return NULL;

    if(*text == '\0')
    {
        if(node->is_word)
        {
            node->is_word = false;
            *deleted = true;

            if(node_has_children(node) == false)
            {
                free(node);
                node = NULL;
            }
        }
        return node;
    }
    node->children[text[0]] =deleteStr_rec(node->children[text[0]],text+1,deleted);
    if(*deleted && node_has_children(node)==false&&node->is_word ==false)
    {
        free(node);
        node = NULL;
    }
    return node;
    
}


bool deleteStr(trienode** root,char *signedText)
{
    unsigned char* text = (unsigned char *)signedText;
    bool result = false;

    if(root == NULL){return false;}
    *root = deleteStr_rec(*root,text,&result);
    return result;
}

void freeTrie(trienode* root)/*free the trie*/
{
    int i;
    if(root==NULL)
    {
        return;
    }
    for (i = 0; i < MAX_LENGTH; i++)
    {
        freeTrie(root->children[i]);  
        root->children[i] = NULL; 
    }
    free(root);
    
}

void fprinttrie_rec(FILE *ofp,trienode *node, unsigned char *prefix,int length)
/*a recursive method to print all trie words used this alot to debug the program */
{
    int j;
    unsigned char newprefix[length+2];
    memcpy(newprefix,prefix,length);
    newprefix[length+1] = 0;
    if (node->is_word)
    {
        fprintf(ofp,"%s %d \n",prefix,node->line_num);
    }
    for(j=0;j<MAX_LENGTH;j++)
    {
        if (node->children[j] != NULL)
        {
            newprefix[length] = j;
            fprinttrie_rec(ofp,node->children[j],newprefix,length+1); 
        }
        
    }
}

void fprinttrie(FILE* ofp,trienode *root)/*this method is to print all the words in the trie*/
{/*this uses the printtrierec method to print the trie entirely, mostly for debuging purposes*/
    if(root == NULL)
    {
        printf("no labels were added!\n");
        return;
    }
    fprinttrie_rec(ofp,root,NULL,0);
}
