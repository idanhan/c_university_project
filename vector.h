#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include"define.h"
typedef struct Vector
{
    short int* data;
    int capacity;
    int total;
}Vector;
