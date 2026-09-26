#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Book {
    char title[50];
    char author[40];
    int year;
    char genre[30];
    int copies;
    bool available;
};

void VerifyInteger(int *opt, int min, int max, char text[]) {
    while(*opt < min || *opt > max) {
        printf("\nPlease, enter a valid %s: ", text);
        scanf("%d", opt);
    }
}

void ClearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to show a book info
void ShowBook(struct Book lib) {
    printf("\nTitle: %s  |  Author: %s  |  Year: %d", lib.title, lib.author, lib.year);
    printf("\nGenre: %s  |  Copies: %d  |  Available: %s\n", lib.genre, lib.copies, lib.available ? "Yes" : "No");
}

// Searchs a book by a title (can be partial) 
void SearchByTitle(struct Book library[], int total, char searchTitle[]) {
    int found = 0;

    printf("\n-- Results for '%s' --\n", searchTitle);

    for(int i = 0; i < total; i++) {

        if(strstr(library[i].title, searchTitle) != NULL) {
            ShowBook(library[i]);
            found++;
        }
    }

    if(found == 0) {
        printf("\nNo book with that title was found.\n");
    }
}

/*Don't uses pointers because in C, when passing an array the function modifies the actual array, not just a copy
Function that manages the process to lend a book*/
void LendBook(struct Book library[], int total, char title[]) {
    int index = -1;

    for(int i = 0; i < total; i++) {

        if(strstr(library[i].title, title) != NULL) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("\nNo book with that title was found.\n");
        return;
    }

    if(library[index].copies <= 0) {
        printf("\nWe are sorry, '%s' does not have available copies.\n", library[index].title);
        return;
    }

    library[index].copies--;

    if(library[index].copies == 0) {
        library[index].available = false;
    }

    printf("\nThe book '%s' has been lent. Copies left: %d\n", library[index].title, library[index].copies);
}

// Processes the return of books
void ReturnBook(struct Book library[], int total, char title[]) {
    int index = -1;

    for(int i = 0; i < total; i++) {

        if(strstr(library[i].title, title) != NULL) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("\nNo book with that title was found.\n");
        return;
    }

    library[index].copies++;
    library[index].available = true;

    printf("\nThe book '%s' has been returned. Current copies: %d\n", library[index].title, library[index].copies);
}

// Searchs and shows a list by a entered genre by the user
void ShowByGenre(struct Book library[], int total, char genre[]) {
    int found = 0;

    printf("\n-- Books in the '%s' Genre --\n", genre);

    for(int i = 0; i < total; i++) {

        // This makes a partial search, in case of needing an exact one this must be changed.
        if(strstr(library[i].genre, genre) != NULL) {
            ShowBook(library[i]);
            found++;
        }
    }

    if(found == 0) {
        printf("\nNo book in the genre was found.\n");
    }
}

// Shows all the available books according to the 'available' field of the struct 'Book'
void AvailableBooks(struct Book library[], int total) {
    int found = 0;

    printf("\n-- Available Books --\n");

    for(int i = 0; i < total; i++) {

        if(library[i].copies > 0) {
            ShowBook(library[i]);
            found++;
        }
    }

    if(found == 0) {
        printf("\nThere's no available books at the moment.\n");
    }
}

int main(void) {
    struct Book library[100] = {
        {"Harry Potter and the Philosopher's Stone", "J.K. Rowling", 1997, "Fantasy", 3, true},
        {"One Hundred Years of Solitude", "Gabriel Garcia Marquez", 1967, "Magical Realism", 2, true},
        {"1984", "George Orwell", 1949, "Dystopia", 0, false},
        {"The Little Prince", "Antoine de Saint-Exupery", 1943, "Fable", 5, true},
        {"Hopscotch", "Julio Cortazar", 1963, "Novel", 1, true}
    };

    int total_books = 5;
    int option = 0;
    char input[50];

    printf("\n-- Welcome to the Ultimate Library Manager --\n");

    do{
        printf("\nChoose an option from below:\n");
        printf("1. Search Book by Title.\n");
        printf("2. Lend a Book.\n");
        printf("3. Return a Book.\n");
        printf("4. Show Books by Genre.\n");
        printf("5. Show Available Books.\n");
        printf("6. Show all Books.\n");
        printf("7. Exit\n");
        scanf("%d", &option);
        VerifyInteger(&option, 1, 7, "option");

        switch(option) {
            case 1:
                ClearInputBuffer();
                printf("\n*The search is case-sensitive*");
                printf("\nPlease, enter the title (or part of it) you want to search: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';

                SearchByTitle(library, total_books, input);
                break;

            case 2:
                ClearInputBuffer();
                printf("\nPlease, enter the title of the book you want to borrow: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';

                LendBook(library, total_books, input);
                break;

            case 3:
                ClearInputBuffer();
                printf("\nPlease, enter the title of the book you want to return: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';

                ReturnBook(library, total_books, input);
                break;

            case 4:
                ClearInputBuffer();
                printf("\nPlease, enter the genre you want to look up: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';

                ShowByGenre(library, total_books, input);
                break;

            case 5:
                AvailableBooks(library, total_books);
                break;

            case 6:
                printf("\n-- LIST OF BOOKS --\n");

                for(int i = 0; i < total_books; i++) {
                    ShowBook(library[i]);
                }
                break;

            case 7:
                printf("\nBye bye, you sir");
                break;
        }

    }while(option != 7);

    return 0;
}