#include"vector.h"
#define MAX_LENGTH 256

int findtiref(trienode *root,char *word);
trienode *createnode();
bool node_has_children(trienode* node);
bool trieinsert(trienode **root,char *signedtext,int line_n);
void printtrie_rec(trienode *node, unsigned char *prefix,int length);
void printtrie(trienode *root);
int macro_lay(FILE *ifp,char* file_name);
short int command_line_interpeter(char* a,short int *ptr1,short int *ptr2,bool *is_ptr1,bool *is_ptr2,trienode *root,int *count,int state,trienode **root_label,Vector** vec,trienode *extern_root,trienode **ex_out_root,Vector** vec_ex,char* filename);
int command_line_file(FILE* ifp,trienode *root,Vector* vector,trienode** trieroot,trienode *extern_root,char* filename);
int labels_table(FILE* ifp,trienode **label_trie_root);
void freeTrie(trienode* root);
bool deleteStr(trienode** root,char *signedText);
int vectorTotal(Vector* v);
int vectorResize(Vector* v,int capacity);
int vectorPushBack(Vector* v,short int item);
int vectorSet(Vector* v,int index,short int item);
int vectorDelete(Vector* v, int index);
int vectorFree(Vector* v);
void vector_init(Vector* v);
short int vectorGet(Vector* v, int index);
int data_table(FILE* ifp,Vector* vec,int start,trienode *root,trienode **data_root,trienode *externroot,trienode **ext_out,Vector* vec_ex,char* filename);
void entry_obj(FILE *ifp,Vector *vec,trienode *root,trienode *data_root,char* file_name,int status);
void fprinttrie(FILE* ofp,trienode *root);
int extern_obj(FILE* ifp,trienode **trie);
int extern_out(FILE *ifp,trienode *root,char* file_name,Vector* vec,int status,trienode* entry_root);
void create_obj(Vector *vec,int instruction_num,int data_num,char* name,int status);












