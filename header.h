#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define FNAME_SIZE 100
#define WORD_SIZE 100

/*Macro for return success or failure*/
#define valid 0
#define invalid -1
#define success 0
#define failure -1

/*file name node for cmd line input files list*/
typedef struct file
{
    char filename[FNAME_SIZE];
    struct file *link;
}filenames_t;

/*sub node*/
typedef struct sub{
    char f_name[FNAME_SIZE];
    int word_count;
    struct sub *link;
}subnode_t;

/*MAIN node*/
typedef struct mainnode
{
    char word[WORD_SIZE];
    int file_count;
    struct mainnode *mlink;
    struct sub *slink;
}mainnode_t;

/*hash table link part*/
typedef struct hash{
    mainnode_t *head;
}hash_t ;

/*Prototypes*/
int is_txt(char *);
int is_file_empty(char *);
int check_duplicate(filenames_t *, char *);
int file_list_validation(int, char **, filenames_t **);
int insert(filenames_t *, hash_t *);
int validate(char);
int create(int, char [], char [], hash_t *);
int create_sub(char [], mainnode_t *, hash_t *);
void hash(hash_t *);
int display_database(hash_t *ht);
int search_database(hash_t *ht, char *word);
int save_database(hash_t *ht, char *fname);
int update_database(hash_t *ht, filenames_t **f_head, char *backup_file);