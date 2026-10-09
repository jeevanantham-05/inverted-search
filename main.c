/*
    JEEVANANTHAM I
    26010_108
    Inverted Search Project
*/

#include"header.h"

int main(int argc, char *argstr[])
{
    if(argc<=1) //if invalid comnd then, help msg to user
    {
        printf("Usage:./a.out f1.txt f2.txt... OR ./a.out -u backup.txt\n");
        return 0;
    }

    filenames_t *f_head = NULL;
    hash_t ht[28]; // create table
    hash(ht); // calling hash function for create table and set link as null
    int db_created = 0;

    // Update mode
    if(strcmp(argstr[1], "-u")==0 || strcmp(argstr[1], "-U")==0)
    {
        if(argc < 3){
            printf("Info: Update needs backup file\n");
            return 0;
        }
        if(update_database(ht, &f_head, argstr[2])==success)
        {
            printf("Update: Database restored from %s\n", argstr[2]);
            db_created = 1;
        }
        else{
            printf("Update failed\n");
            return 0;
        }
        // validate remaining files after -u backup
        file_list_validation(argc, argstr, &f_head);
        if(f_head!=NULL)
            insert(f_head, ht);
    }
    else
    {
        if(file_list_validation(argc, argstr, &f_head)==invalid)
        {
            printf("No valid files found\n");
            return 0;
        }
        if(insert(f_head, ht)==success)
        {
            printf("Database created successfully\n");
            db_created = 1;
        }
    }

    if(!db_created){
        printf("Database not created\n");
        return 0;
    }

    /*...........MENU............*/
    int choice;
    char word[WORD_SIZE], sfile[FNAME_SIZE];
    while(1)
    {
        printf("\n1. Create Database (already done)\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Save Database\n");
        printf("5. Update Database (add more files)\n");
        printf("6. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                printf("Database already created\n"); break;
            case 2:
                display_database(ht); break;
            case 3:
                printf("Enter word to search: ");
                scanf("%s", word);
                search_database(ht, word);
                break;
            case 4:
                printf("Enter backup filename (ex: backup.txt): ");
                scanf("%s", sfile);
                save_database(ht, sfile);
                break;
            case 5:
                printf("Enter new file to add: ");
                scanf("%s", sfile);
                char *temp_argv[] = {"./a.out", sfile, NULL};
                filenames_t *new_head = NULL;
                file_list_validation(2, temp_argv, &new_head);
                if(new_head) insert(new_head, ht);
                break;
            case 6: return 0;
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}

int is_txt(char *file) // check.txt extn only
{
    char *dot = strrchr(file, '.');
    if(dot && strcmp(dot, ".txt")==0)
        return 1;
    return 0;
}

int is_file_empty(char *file)  //atleast one char should be present
{
    FILE *fp = fopen(file,"r");
    if(!fp) return 1;
    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    if(size==0) return 1;
    return 0;
}

/*check curr file is present in SLL or not*/
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

/*IF function fails shows ERRORS here.....*/
int file_list_validation(int argc, char *argv[], filenames_t **head)
{
    int valid_count=0;
    for(int i=1;i<argc;i++)
    {
        if(argv[i]==NULL) continue;
        if(strcmp(argv[i], "-u")==0 || strcmp(argv[i], "-U")==0)
        {
            i++; // skip backup filename
            continue;
        }
        if(!is_txt(argv[i]))
        {
            printf("Error: %s should have.txt extn only\n", argv[i]);
            continue;
        }
        FILE *fp = fopen(argv[i],"r");
        if(!fp)
        {
            printf("Error: %s file not present\n", argv[i]);
            continue;
        }
        fclose(fp);
        if(is_file_empty(argv[i]))
        {
            printf("Error: %s is empty file\n", argv[i]);
            continue;
        }
        if(check_duplicate(*head, argv[i]))
        {
            printf("Error: %s is duplicate file -> not adding\n", argv[i]);
            continue;
        }
        else
        {
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
    }
    if(valid_count==0 && *head==NULL)
        return invalid;
    return success;
}


/*HASH TABLE*/

void hash(hash_t *ht)
{
     //array of structure
    for(int i=0;i<28;i++)
        ht[i].head = NULL;  //initially set NULL
}