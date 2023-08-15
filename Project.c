#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book
{
    int BookID;
    char BookName[50];
    char Studentname[20];
};

void addBook()
{
    struct Book newBook;
    printf("Enter Book ID: ");
    scanf("%d", &newBook.BookID);
    printf("Enter Book Name: ");
    scanf("%s", newBook.BookName);
    printf("Enter Student Name: ");
    scanf("%s", newBook.Studentname);

    FILE *file = fopen("books.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%d %s %s\n", newBook.BookID, newBook.BookName, newBook.Studentname);
    printf("\nBook Added Sucessfully\n");
    fclose(file);
}

void listBooks()
{
    FILE *file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("No books available.\n");
        return;
    }
    int bookavailable = 0;
    struct Book book;
    while (fscanf(file, "%d %s %s", &book.BookID, book.BookName, book.Studentname) != EOF)
    {
        printf("ID: %d, Name: %s, StudentName: %s\n", book.BookID, book.BookName, book.Studentname);
        bookavailable++;
    }
    if (bookavailable == 0)
    {
        printf("\nNo Books in the list\n");
    }
    fclose(file);
}

void deleteBook(int id)
{
    FILE *file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("No books available.\n");
        return;
    }
    int deletedbook = 0;
    FILE *tempbook = fopen("temp.txt", "w");
    struct Book book;
    while (fscanf(file, "%d %s %s", &book.BookID, book.BookName, book.Studentname) != EOF)
    {
        if (book.BookID != id)
        {
            fprintf(tempbook, "%d %s %s\n", book.BookID, book.BookName, book.Studentname);
        }
        else
        {
            deletedbook++;
        }
    }

    if (deletedbook != 0)
    {
        printf(" \nBook Deleted Sucessfully \n");
    }
    fclose(file);
    fclose(tempbook);

    remove("books.txt");
    rename("temp.txt", "books.txt");
}

void updateBook(int id)
{
    FILE *file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("No books available.\n");
        return;
    }
    int Updatedbook = 0;
    FILE *tempFile = fopen("temp.txt", "w");
    struct Book book;
    while (fscanf(file, "%d %s %s", &book.BookID, book.BookName, book.Studentname) != EOF)
    {
        if (book.BookID == id)
        {
            printf("Enter new Book Name: ");
            scanf("%s", book.BookName);
            printf("Enter new Student Name: ");
            scanf("%s", book.Studentname);
            Updatedbook++;
        }
        fprintf(tempFile, "%d %s %s\n", book.BookID, book.BookName, book.Studentname);
    }
    if (Updatedbook != 0)
    {
        printf("Book Updated Sucessfully ");
    }
    fclose(file);
    fclose(tempFile);

    remove("books.txt");
    rename("temp.txt", "books.txt");
}

int main()
{
    int choice, id;

    while (1)
    {
        printf("\nBook Management System\n");
        printf("1. Add Book\n");
        printf("2. List Books\n");
        printf("3. Delete Book\n");
        printf("4. Update Book Details\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            listBooks();
            break;
        case 3:
            printf("Enter Book ID to delete: ");
            scanf("%d", &id);
            deleteBook(id);
            break;
        case 4:
            printf("Enter Book ID to update: ");
            scanf("%d", &id);
            updateBook(id);
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}