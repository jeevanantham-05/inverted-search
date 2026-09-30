
#include"header.h"

int insert(char **file, hash_t *ht)//collecting cmd line arg_vector
{
    int i=1;
    while(file[i]!=NULL)
    {
        FILE *fp;
        fp = fopen(file[i],"r");
        if(!fp) return invalid;

        char word[200];
        /*fscanf read formated inputs from file, here read str by str */
        while(fscanf(fp, "%s", word)!= EOF)
        {
            int indx = validate(word[0]); //pasing word 1st char for find index

            if(ht[indx].head==NULL)
            {
                create(indx,word,file[i], ht);
            }
            else
            {
                 /*list not empty then compare word and filename*/
                mainnode_t *temp = ht[indx].head;
                int mflag=0, sflag=0;

                while(temp!=NULL)
                {
                    /*comparing word, incase already present or not!*/
                    if(strcmp(temp->word,word)==0) //equal then it already exist
                    {
                        mflag=1; //word found
                        /*then comare file name*/
                        subnode_t *sub_temp = temp->slink;
                        while(sub_temp!= NULL)
                        {
                            if(strcmp(sub_temp->f_name,file[i])==0)
                            {
                                sflag=1;  //file found
                                sub_temp->word_count++;
                                break;
                            }
                            sub_temp = sub_temp->link;
                        }

                        if(sflag==0) //word found but diff file name the crate sub node
                        {
                            temp->file_count++;
                            create_sub(file[i],temp,ht);
                        }
                        break;
                    }
                    temp = temp->mlink;
                }

                if(mflag==0) //word not found then create newly
                {
                    create(indx,word,file[i],ht);
                }
            }
        }
        fclose(fp);
        i++;
    }
    return success;
}