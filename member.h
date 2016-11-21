//
//  member.h
//  Library
//
//  Created by 이동규 on 2016. 11. 14..
//  Copyright © 2016년 이동규. All rights reserved.
//

#ifndef member_h
#define member_h

#include <stdio.h>
#include "file.h"
#include "list.h"


void seachBook();
void loadMyBorrowList(borrowNode *borrowList, int studentId);
void modifyPersonalInfo(clientNode *clientList, int studentId);
int leaveMember(clientNode *clientList, borrowNode *borrowList, int studentId);
void findBookByTitle();
void findBookByPublisher();
void findBookByISBN();
void findBookByWriter();
void findAllBook();


#endif /* member_h */
