//
//  admin.h
//  Library
//
//  Created by 이동규 on 2016. 11. 14..
//  Copyright © 2016년 이동규. All rights reserved.
//

#ifndef admin_h
#define admin_h

#include <stdio.h>
#include "list.h"
#include "file.h"
#include <stdlib.h>


void registerNewBook(bookNode *);
void deleteBook(bookNode *bookList);
void lendBook(bookNode *bookList, borrowNode *borrowList, clientNode *clientList);
void returnBook(clientNode *clientList, bookNode *bookList, borrowNode *borrowList);
void searchBook();
void loadMemberList(clientNode *clientList);


#endif /* admin_h */
