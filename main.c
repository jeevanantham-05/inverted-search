#include"header.h"


int main(int argc, char *argstr[])
{
    if(argc<=1)
    {
        printf("Usage:./a.out f1.txt f2.txt...\n");
        return 0;
    }

    filenames_t *f_head = NULL;
    hash_t ht[28];
    hash(ht);

    if(file_list_validation(argc, argstr, &f_head)==invalid)
    {
        printf("No valid files found\n");
        return 0;
    }

    // now create SLL array for insert
    if(insert(argstr,ht)!=invalid)
    {
        printf("successfully done....\n");
    }
    else{
        printf("error\n");
    }
    return 0;
}


/*COMMAND LINE Validations..........*/

int is_txt(char *file) /*.txt extension checks*/
{
    char *dot = strrchr(file, '.'); 
    if(dot && strcmp(dot, ".txt")==0)
        return 1;
    return 0;
}

int is_file_empty(char *file)
{
    FILE *fp = fopen(file,"r");
    if(!fp) return 1;
    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    if(size==0) return 1;
    return 0;
}

int check_duplicate(filenames_t *head, char *file)
{
    filenames_t *temp = head;
    while(temp!=NULL)
    {
        if(strcmp(temp->filename,file)==0)
            return 1;
        temp = temp->link;
    }
    return 0;
}

int file_list_validation(int argc, char *argv[], filenames_t **head)
{
    int i=1;
    int valid_count=0;
    while(argv[i]!=NULL)
    {
        // 1. check.txt extn only
        if(!is_txt(argv[i]))
        {
            printf("Error: %s should have.txt extn only\n", argv[i]);
            i++;
            continue;
        }

        // 2. check file is valid (present in curr dir)
        FILE *fp = fopen(argv[i],"r");
        if(!fp)
        {
            printf("Error: %s file not present\n", argv[i]);
            i++;
            continue;
        }
        fclose(fp);

        // 3. atleast one char should be present
        if(is_file_empty(argv[i]))
        {
            printf("Error: %s is empty file\n", argv[i]);
            i++;
            continue;
        }

        // 4. check curr file is present in SLL or not
        if(check_duplicate(*head, argv[i]))
        {
            printf("Error: %s is duplicate file -> not adding\n", argv[i]);
            i++;
            continue;
        }
        else
        {
            // not present -> insert the curr filename into SLL
            filenames_t *new = malloc(sizeof(filenames_t));
            strcpy(new->filename, argv[i]);
            new->link = NULL;

            if(*head==NULL)
                *head = new;
            else
            {
                filenames_t *temp = *head;
                while(temp->link!=NULL)
                    temp = temp->link;
                temp->link = new;
            }
            valid_count++;
        }
        i++;
    }

    if(valid_count==0)
        return invalid;

    return success;
}