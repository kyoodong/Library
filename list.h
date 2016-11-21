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


void addBook(bookNode *bookList, bookNode *addedbook);
void insertBook(bookNode *bookList, bookNode *addedbook, int index);
bookNode* getBookNode(bookNode* bookList, int at);
int bookLength(bookNode bookList);
int isEmptyBook(book checkingBook);
void removeBook(bookNode *bookList, int at);
void clearBook(bookNode *);


borrow initBorrow();
borrowNode initBorrowNode();


void addBorrow(borrowNode *borrowList, borrowNode *addedBorrow);
void insertBorrow(borrowNode *borrowList, borrowNode *addedBorrow, int index);
borrowNode* getBorrowNode(borrowNode* borrowList, int at);
int borrowLength(borrowNode borrowList);
int isEmptyBorrow(borrow borrow);
void removeBorrow(borrowNode *borrowList, int at);
void clearBorrow(borrowNode *);

clientNode findClientById(clientNode list, int id);




