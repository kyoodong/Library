#ifndef borrows_h
#define borrows_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

#define BORROW_FILE_PATH "./borrow.txt"


typedef struct {
    int studentId;          // 빌린 학생 id
    int bookId;             // 빌려진 책 번호
    time_t borrowDateSec;   // 빌린 날짜 (1970년도부터 흐른 초 수)
    time_t returnDateSec;   // 반납 날짜 (1970년도부터 흐른 초 수)
} borrow;


typedef struct borrowNode {
    borrow borrow;
    struct borrowNode *next;
} borrowNode;


void loadBorrowFile(borrowNode *borrows);
void overwriteBorrowFile(borrowNode node);
borrowNode* readBorrowFileLine(FILE* borrowFile);
int isEmptyBorrow(borrow b);
void addBorrow(borrowNode *borrowList, borrowNode *addedBorrow);
void removeBorrow(borrowNode *borrowList, int at);
borrowNode* getBorrowNode(borrowNode* borrowList, int at);
int borrowLength(borrowNode borrowList);
borrow initBorrow();
borrowNode* findBorrowNodeByStudentId(borrowNode* borrowList, int studentId);
borrowNode* findBorrowNodeByBookId(borrowNode* borrowList, int bookId);
int isEqualBorrow(borrow leftBorrow, borrow rightBorrow);
int indexOfBorrowNode(borrowNode* borrowList, borrowNode foundBorrowNode);
void printBorrow(borrow b);
void printDate(time_t t);
void printBorrowList(borrowNode printingBorrow);
void closeBorrowFile();

#endif