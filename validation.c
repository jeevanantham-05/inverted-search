

#include"header.h"
/*find & returnng index position*/
int validate(char ch)
{
    int index;
    if(ch >= 'A' && ch <= 'Z') //upper case
    {
        index = ch - 'A';
        return index;
    }
    else if(ch >= 'a' && ch <= 'z') //lower case
    {
        index = ch - 'a';
        return index;
    }
    else if(ch >= '0' && ch <= '9') //digit
    {
        return 26;
    }
    else             //special char
    {
        return 27;
    }
}

/*creating new node....*/
int create(int indx, char word[], char file[], hash_t *ht)
{
    /*creating main node as well as sub node*/
    mainnode_t *new = malloc(sizeof(mainnode_t));
    if(!new) return failure;

    strcpy(new->word, word);
    new->file_count = 1;
    new->mlink = NULL;

     //sub node
    subnode_t *subn = malloc(sizeof(subnode_t));
    if(!subn) return failure;

    subn->word_count = 1;
    strcpy(subn->f_name, file);
    subn->link =NULL;

    new->slink = subn; //mainnode sub link linking with sub node

     /*insert first operation....*/
    if(ht[indx].head==NULL)
    {
        ht[indx].head = new;
        return success;
    }
    else{
        new->mlink = ht[indx].head;
        ht[indx].head = new;
        return success;
    }
}

/*Only sub node linking*/
int create_sub(char file[], mainnode_t *link, hash_t *ht)
{
    subnode_t *subn = malloc(sizeof(subnode_t));
    if(!subn) return failure;

    subn->word_count = 1;
    strcpy(subn->f_name, file);
    subn->link = link->slink;

    link->slink = subn; //linking
    return success;
}







