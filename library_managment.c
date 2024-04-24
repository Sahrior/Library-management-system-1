#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct books{
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
}b;

FILE *fp;

int main(){

    int ch;

    while(1){
        system("cls");

        printf("##################################\n");
        printf("#                                #\n");
        printf("# -->LIBRARY MANAGEMENT SYSTEM<--#\n");
        printf("#________________________________#\n");
        printf("#                                #\n");
        printf("#                                #\n");
        printf("#      Press 1 to add books      #\n");
        printf("#                                #\n");
        printf("#   Press 2 to view books list   #\n");
        printf("#                                #\n");
        printf("#     Press 3 to remove books    #\n");
        printf("#                                #\n");
        printf("#         Press 0 to EXIT        #\n");
        printf("#                                #\n");
        printf("##################################\n");
        printf("\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);


        switch(ch){
        case 0:
            exit(0);

        case 1:
            addBook();
            break;

        case 2:
            booksList();
            break;

        case 3:
            del();
            break;

        default:
            printf("Invalid Choice...\n\n");

        }
        printf("Press Any Key To Continue...");
        getch();
    }

    return 0;
}


void addBook(){
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    fp = fopen("books.txt", "ab");

    printf("Enter book id: ");
    scanf("%d", &b.id);

    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bookName);

    printf("Enter author name: ");
    fflush(stdin);
    gets(b.authorName);

    printf("Book Added Successfully");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}


void booksList(){

    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");

    fp = fopen("books.txt", "rb");
    while(fread(&b, sizeof(b), 1, fp) == 1){
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);
}

void del(){
    int id, f=0;
    system("cls");
    printf("<== Remove Books ==>\n\n");
    printf("Enter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(id == b.id){
            f=1;
        }else{
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if(f==1){
        printf("\n\nDeleted Successfully.");
    }else{
        printf("\n\nRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("temp.txt", "books.txt");

}


