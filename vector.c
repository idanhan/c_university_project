#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include"define.h"
/*vector data structure implementation - resizable array or dynamic array chose this data structure because it 
allows better memory managment then an array i use this datastructure to hold all of the data as whole data image 
and instruction image and then printing it. so insert is O(1) because we just insert to the end of the array search 
is O(1) because we search by index and printing is O(n) also to change some item in the array is O(1)*/

#define VECTOR_INIT_CAPACITY 12
#define UNDEFINED -1
#define SUCCESS 0

typedef struct Vector
{
    short int* data;
    int capacity;
    int total;
}Vector;

int vectorTotal(Vector* v)
{
    return (v!=NULL)? v->total:UNDEFINED;
}

int vectorResize(Vector* v,int capacity)
{
    if(v==NULL)
    {
        return UNDEFINED;
    }

    short int* new_data = (short int*)realloc(v->data,sizeof(short int*)*capacity);
    if (new_data == NULL)
    {
        return UNDEFINED;
    }
    
    v->data = new_data;
    v->capacity = capacity;
    return SUCCESS;
}

int vectorPushBack(Vector* v,short int item)/*puts the new item at the end of array*/
{
    if(v==NULL)
    {
        return UNDEFINED;
    }
    
    if(v->total == v->capacity)
    {
        if(vectorResize(v,v->capacity * 2)!=SUCCESS)/*increase vector to insert*/
        {
            return UNDEFINED;
        }
    }

    v->data[v->total++] = item;/*inserts v->total to data at the end of the list and increase total by one*/
    return SUCCESS;
}

int vectorSet(Vector* v,int index,short int item)/*sets the data at index i to item*/
{
    if(v==NULL|| index <0 || index >= v->total)
    {
        return UNDEFINED;
    }

    v->data[index] = item;
    return SUCCESS;
}

short int vectorGet(Vector* v, int index) {/*get the data item by index*/
    if (v == NULL || index < 0 || index >= v->total) {
        return 0;
    }
    return v->data[index];
}

int vectorDelete(Vector* v, int index) 
{
    int i;
    if (v == NULL || index < 0 || index >= v->total) {
        return UNDEFINED;
    }

    for (i = index; i < v->total - 1; ++i) {
        v->data[i] = v->data[i + 1];
    }

    v->total--;

    if (v->total > 0 && v->total == v->capacity / 4) {
        vectorResize(v, v->capacity / 2);
    }

    return SUCCESS;
}

int vectorFree(Vector* v)/*free the vector so there will be no memory leak*/
{
    if (v == NULL) {
        return UNDEFINED;
    }

    free(v->data);
    v->data = NULL;
    v->capacity = 0;
    v->total = 0;

    return SUCCESS;
}

void vector_init(Vector* v) {/*intilize vector*/
    v->data = (short int*)malloc(sizeof(short int) * VECTOR_INIT_CAPACITY);
    v->capacity = VECTOR_INIT_CAPACITY;
    v->total = 0;
}

