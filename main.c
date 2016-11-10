#include "list.h"
#include <stdlib.h>

int main(void) {
    clientNode *clientList = calloc(1, sizeof(clientNode)), a, b;
    bookNode *bookList = calloc(1, sizeof(bookNode));
    borrowNode *borrowList = calloc(1, sizeof(borrowNode));
    loadFile(clientList, bookList, borrowList);
    
    for (int i = 0; i < clientLength(*clientList); i++) {
        printf("%d\n", getClientNode(clientList, i) -> client.studentId);
    }
    
    for (int i = 0; i < bookLength(*bookList); i++) {
        printf("%d\n", getBookNode(bookList, i) -> book.bookId);
    }
    
    for (int i = 0; i < borrowLength(*borrowList); i++) {
        printf("Book = %d\n", getBorrowNode(borrowList, i) -> borrow.bookId);
        printf("Student = %d\n", getBorrowNode(borrowList, i) -> borrow.studentId);
    }
    
    return 0;
}
