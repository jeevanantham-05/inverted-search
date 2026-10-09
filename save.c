#include"header.h"

int save_database(hash_t *ht, char *fname)
{
    FILE *fp = fopen(fname, "w");
    if(!fp) return failure;
    for(int i=0;i<28;i++)
    {
        mainnode_t *temp = ht[i].head;
        while(temp!=NULL)
        {
            fprintf(fp, "#%d;%s;%d;", i, temp->word, temp->file_count);
            subnode_t *sub = temp->slink;
            while(sub!=NULL)
            {
                fprintf(fp, "%s;%d", sub->f_name, sub->word_count);
                if(sub->link!=NULL) fprintf(fp, ";");
                sub = sub->link;
            }
            fprintf(fp, "#\n");
            temp = temp->mlink;
        }
    }
    fclose(fp);
    printf("Database saved to %s\n", fname);
    return success;
}