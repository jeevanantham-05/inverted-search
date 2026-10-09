#include"header.h"

int display_database(hash_t *ht)
{
    int empty = 1; //like flagg...
    for(int i=0;i<28;i++)
    {
        mainnode_t *temp = ht[i].head;
        while(temp!=NULL)
        {
            empty = 0;
            printf("[%d] [%s] %d file(s) : file : ", i, temp->word, temp->file_count);
            subnode_t *sub = temp->slink;
            while(sub!=NULL)
            {
                printf("%s : %d time(s)", sub->f_name, sub->word_count);
                if(sub->link!=NULL) printf(" : ");
                sub = sub->link;
            }
            printf("\n");
            temp = temp->mlink;
        }
    }
    if(empty)
        printf("Database is empty\n");
    return success;
}