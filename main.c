#include "list.h"
#include <stdlib.h>

int main(void) {
    clientNode *clientList = calloc(1, sizeof(clientNode)), a, b;
    bookNode *bookList = calloc(1, sizeof(bookNode));
    borrowNode *borrowList = calloc(1, sizeof(borrowNode));
    loadFile(clientList, bookList, borrowList);
    
    printf("%d\n", getClientNode(clientList, 0) -> client.studentId);
    printf("%s\n", getClientNode(clientList, 0) -> client.address);
    printf("%s\n", getClientNode(clientList, 0) -> client.name);
    printf("%s\n", getClientNode(clientList, 0) -> client.password);
    printf("%s\n", getClientNode(clientList, 0) -> client.phone);
    
    
    printf("\n\n\n");
    
    printf("%d\n", getBookNode(bookList, 0) -> book.bookId);
    printf("%luld\n", getBookNode(bookList, 0) -> book.ISBN);
    printf("%s\n", getBookNode(bookList, 0) -> book.authorName);
    printf("%s\n", getBookNode(bookList, 0) -> book.holdingInstitudtion);
    printf("%s\n", getBookNode(bookList, 0) -> book.name);
    printf("%s\n", getBookNode(bookList, 0) -> book.publisherName);
    printf("%c\n", getBookNode(bookList, 0) -> book.isBorrowable);
    
    printf("\n\n\n");
    
    printf("Book = %d\n", getBorrowNode(borrowList, 0) -> borrow.studentId);
    printf("Book = %d\n", getBorrowNode(borrowList, 0) -> borrow.bookId);
    printf("Book = %ld\n", getBorrowNode(borrowList, 0) -> borrow.borrowDateSec);
    printf("Book = %ld\n", getBorrowNode(borrowList, 0) -> borrow.returnDateSec);
    
    return 0;
}
