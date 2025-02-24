//
//  file.h
//  Library
//
//  Created by 이동규 on 2016. 11. 9..
//  Copyright © 2016년 이동규. All rights reserved.
//

#ifndef file_h
#define file_h

#include <stdio.h>
#include <time.h>

typedef struct {
    int studentId;             // 학번
    char password[20];  // 비밀번호
    char name[20];      // 고객 이름
    char address[50];   // 고객 주소
    char phone[20];     // 고객 전화번호
} client;

typedef struct {
    int bookId;                             // 책 번호
    char name[20];                      // 책 이름
    char publisherName[20];             // 책 출판사
    char authorName[20];                // 책 지은이
    unsigned long ISBN;                 // ISBN
    char holdingInstitudtion[50];       // 소장처
    char isBorrowable;                  // 대여 가능 여부
} book;

typedef struct {
    int studentId;          // 빌린 학생 id
    int bookId;             // 빌려진 책 번호
    time_t borrowDateSec;   // 빌린 날짜 (1970년도부터 흐른 초 수)
    time_t returnDateSec;   // 반납 날짜 (1970년도부터 흐른 초 수)
} borrow;

typedef struct clientNode {
    client client;
    struct clientNode *next;
} clientNode;

typedef struct bookNode {
    book book;
    struct bookNode *next;
} bookNode;

typedef struct borrowNode {
    borrow borrow;
    struct borrowNode *next;
} borrowNode;

void loadFile(clientNode*, bookNode*, borrowNode*);

#endif /* file_h */
