#include"header.h"

int insert(filenames_t *f_head, hash_t *ht) //collecting cmd line arg_vector
{
    filenames_t *f_temp = f_head;
    while(f_temp!=NULL)
    {
        FILE *fp = fopen(f_temp->filename,"r");
        if(!fp){ f_temp = f_temp->link; continue; }

        char word[WORD_SIZE];

        /*fscanf read formated inputs from file, here read str by str */
        while(fscanf(fp, "%s", word)==1)
        {
            int indx = validate(word[0]);  //pasing word 1st char for find index
            if(ht[indx].head==NULL)
            {
                create(indx, word, f_temp->filename, ht);
            }
            else
            {
                /*list not empty then compare word and filename*/
                mainnode_t *temp = ht[indx].head;
                int mflag=0;
                while(temp!=NULL)
                {
                    if(strcmp(temp->word, word)==0) //equal then it already exist
                    {
                        mflag=1; //word found

                         /*then comare file name*/
                        subnode_t *sub_temp = temp->slink;
                        int sflag=0;
                        while(sub_temp!= NULL)
                        {
                            if(strcmp(sub_temp->f_name, f_temp->filename)==0)
                            {
                                sflag=1; //file found
                                sub_temp->word_count++;
                                break;
                            }
                            sub_temp = sub_temp->link;
                        }
                        if(sflag==0)  //word found but diff file name the crate sub node
                        {
                            temp->file_count++;
                            create_sub(f_temp->filename, temp, ht);
                        }
                        break;
                    }
                    temp = temp->mlink;
                }
                if(mflag==0) //word not found then create newly
                    create(indx, word, f_temp->filename, ht);
            }
        }
        fclose(fp);
        f_temp = f_temp->link;
    }
    return success;
}