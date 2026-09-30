#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

/*Macro for return success or failure*/
#define valid 0
#define invalid -1
#define success 0
#define failure -1

/*file name node for cmd line input files list*/
typedef struct file
{
    char filename[100];
    struct file *link;
}filenames_t;

/*sub node*/
typedef struct sub{
    char f_name[100];
    int word_count;
    struct sub *link;
}subnode_t;

/*MAIN node*/
typedef struct mainnode
{
    char word[100];
    int file_count;
    struct mainnode *mlink;
    struct sub *slink;
}mainnode_t;

/*hash table link part*/
typedef struct hash{
    mainnode_t *head;
}hash_t ;


/*Prototypes.....*/
int is_txt(char *);
int is_file_empty(char *);
int check_duplicate(filenames_t *, char *);
int file_list_validation(int, char **, filenames_t **);
int insert(char **, hash_t *);
int validate(char);
int create(int, char [], char [], hash_t *);
int create_sub(char [], mainnode_t *, hash_t *);
void hash(hash_t *);