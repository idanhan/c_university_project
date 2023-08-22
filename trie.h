#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_LENGTH 256

typedef struct trienode
{
    int line_num;
    bool is_word;
    struct trienode* children[MAX_LENGTH];
}trienode;



