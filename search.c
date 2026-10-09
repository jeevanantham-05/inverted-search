#include"header.h"

int search_database(hash_t *ht, char *word)
{
    int indx = validate(word[0]);
    mainnode_t *temp = ht[indx].head;
    while(temp!=NULL)
    {
        if(strcmp(temp->word, word)==0)
        {
            printf("Word [%s] is present in %d file(s)\n", word, temp->file_count);
            subnode_t *sub = temp->slink;
            while(sub!=NULL)
            {
                printf("In file : %s : %d time(s)\n", sub->f_name, sub->word_count);
                sub = sub->link;
            }
            return success;
        }
        temp = temp->mlink;
    }
    printf("Word [%s] not found\n", word);
    return failure;
}