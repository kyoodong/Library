#ifndef books_h
#define books_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOK_FILE_PATH "./book.txt"

#define DELETE 0
#define SEARCH 1

typedef struct {
    int bookId;                             // 책 번호
    char name[20];                      // 책 이름
    char publisherName[20];             // 책 출판사
    char authorName[20];                // 책 지은이
    unsigned long ISBN;                 // ISBN
    char holdingInstitution[50];       // 소장처
    char isBorrowable;                  // 대여 가능 여부
} book;

typedef struct bookNode {
    book book;
    struct bookNode *next;
} bookNode;


void loadBookFile(bookNode *books);
bookNode* readBookFileLine(FILE* bookFile);
void overwriteBookFile(bookNode bookList);
int isEmptyBook(book checkingBook);
void addBook(bookNode *bookList, bookNode *addedBook);
void removeBook(bookNode *bookList, int at);
void clearBook(bookNode *bookList);
void insertBook(bookNode *bookList, bookNode *addedBook, int at);
bookNode* getBookNode(bookNode* bookList, int at);
bookNode* findBookNodeByISBN(bookNode* bookList, unsigned long isbn);
bookNode* findBookNodeByBookName(bookNode* bookList, char* bookName);
bookNode* findBookNodeByPublisherName(bookNode* bookList, char* publisherName);
bookNode* findBookNodeByAuthorName(bookNode* bookList, char* authorName);
int isEqualBook(book leftBook, book rightBook);
int indexOfBookNode(bookNode* bookList, bookNode foundBookNode);
bookNode* findBookNodeByBookId(bookNode* bookList, int bookId);
int bookLength(bookNode bookList);
bookNode initBookNode();
book initBook();
void printBook(bookNode bookList, int bookNum, int borrowableBookNum, int mode);
void printBookList(bookNode printingBook, int mode);
void closeBookFile();

#endif