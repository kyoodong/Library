//
//  list.h
//  Library
//
//  Created by 이동규 on 2016. 11. 9..
//  Copyright © 2016년 이동규. All rights reserved.
//

#ifndef list_h
#define list_h

#endif /* list_h */

#include <stdio.h>
#include "file.h"
#include <string.h>

client initClient();
clientNode initClientNode();


void addClient(clientNode *clientList, clientNode *addedClient);
void insertClient(clientNode *clientList, clientNode *addedClient, int index);
clientNode* getClientNode(clientNode* clientList, int at);
int clientLength(clientNode clientList);
int isEmptyClient(client c);
void removeClient(clientNode *clientList, int at);
void clearClient(clientNode *);


book initBook();
bookNode initBookNode();


void addBook(bookNode *, bookNode *);
void insertBook(bookNode *, bookNode *, int);
bookNode* getBookNode(bookNode*, int);
int bookLength(bookNode);
int isEmptyBook(book);
void removeBook(bookNode *, int);
void clearBook(bookNode *);
bookNode* findBookNodeByISBN(bookNode* bookList, unsigned long isbn);
bookNode* findBookNodeByBookId(bookNode* bookList, int bookId);
bookNode* findBookNodeByBookName(bookNode* bookList, char* bookName);
int indexOfBookNode(bookNode* bookList, bookNode foundBookNode);


borrow initBorrow();
borrowNode initBorrowNode();


void addBorrow(borrowNode *, borrowNode *);
void insertBorrow(borrowNode *, borrowNode *, int);
borrowNode* getBorrowNode(borrowNode*, int);
int borrowLength(borrowNode);
int isEmptyBorrow(borrow);
void removeBorrow(borrowNode *, int);
void clearBorrow(borrowNode *);

clientNode* findClientNodeById(clientNode* list, int id);
borrowNode* findBorrowNodeByStudentId(borrowNode* borrowList, int studentId);
borrowNode* findBorrowNodeByBookId(borrowNode* borrowList, int bookId);
int indexOfBorrowNode(borrowNode* borrowList, borrowNode foundBorrowNode);
int isEqualBorrow(borrow leftBorrow, borrow rightBorrow);




