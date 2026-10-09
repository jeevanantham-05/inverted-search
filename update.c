#include"header.h"

int update_database(hash_t *ht, filenames_t **f_head, char *backup_file)
{
    FILE *fp = fopen(backup_file, "r");
    if(!fp){
        printf("Error: backup file %s not found\n", backup_file);
        return failure;
    }
    char line[1000];
    while(fgets(line, sizeof(line), fp))
    {
        // line: #index, word, file_count, fname, wcount, fname, wcount..
        if(line[0]!='#') continue;
        char *token = strtok(line, "#;");
        if(!token) continue;
        int indx = atoi(token);

        token = strtok(NULL, ";");
        if(!token) continue;
        char word[WORD_SIZE]; strcpy(word, token);

        token = strtok(NULL, ";");
        if(!token) continue;
        int file_count = atoi(token);

        mainnode_t *new = malloc(sizeof(mainnode_t));
        strcpy(new->word, word);
        new->file_count = file_count;
        new->mlink = NULL;
        new->slink = NULL;

        subnode_t *prev_sub = NULL;
        for(int i=0;i<file_count;i++)
        {
            char *fname = strtok(NULL, ";");
            char *wcount = strtok(NULL, ";#\n");
            if(!fname ||!wcount) break;

            subnode_t *sub = malloc(sizeof(subnode_t));
            strcpy(sub->f_name, fname);
            sub->word_count = atoi(wcount);
            sub->link = NULL;

            if(new->slink==NULL)
                new->slink = sub;
            else
                prev_sub->link = sub;
            prev_sub = sub;

            // maintain file list
            if(!check_duplicate(*f_head, fname))
            {
                filenames_t *fn = malloc(sizeof(filenames_t));
                strcpy(fn->filename, fname);
                fn->link = NULL;
                if(*f_head==NULL) *f_head = fn;
                else{
                    filenames_t *t = *f_head;
                    while(t->link) t=t->link;
                    t->link = fn;
                }
            }
        }
        if(ht[indx].head==NULL)
            ht[indx].head = new;
        else{
            new->mlink = ht[indx].head;
            ht[indx].head = new;
        }
    }
    fclose(fp);
    return success;
}