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
#include "clients.h"
#include "books.h"
#include "borrows.h"


void loadMyBorrowList(borrowNode *borrowList, int studentId);
void modifyPersonalInfo(clientNode *clientList, int studentId);
int leaveMember(clientNode *clientList, borrowNode *borrowList, int studentId);


#endif /* member_h */
