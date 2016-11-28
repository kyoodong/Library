//
// Created by 이동규 on 2016. 11. 29..
//

#include "borrows.h"
#include <stdio.h>
#include <stdlib.h>

FILE *borrowFile;
const char wdayList[][4] = {"일", "월", "화", "수", "목", "금", "토"};


// 파일 불러오기
void loadBorrowFile(borrowNode *borrows) {
    // 파일 읽기 모드로 열기
    borrowFile = fopen(BORROW_FILE_PATH, "r+");

    if (borrowFile == NULL) {
        printf("borrow 파일이 없습니다.\n");
        return;
    }

    // borrow 파일에서 데이터를 추출 borrows에 저장합니다.
    while (!feof(borrowFile)) {
        borrowNode* node = readBorrowFileLine(borrowFile);
        addBorrow(borrows, node);
    }

    fflush(borrowFile);
}


// borrowFile 을 borrowList 의 정보로 덮어 씁니다.
void overwriteBorrowFile(borrowNode node) {
    rewind(borrowFile);

    while (!isEmptyBorrow(node.borrow)) {
        fprintf(borrowFile, "%d||%d||%d||%d\n",
                node.borrow.studentId,              // 학번
                node.borrow.bookId,                 // 책 번호
                (int) node.borrow.borrowDateSec,    // 대여 일자
                (int) node.borrow.returnDateSec     // 반납 일자
        );
        if (node.next == NULL)
            break;

        node = *(node.next);
    }
    fflush(borrowFile);
}


// borrow 파일을 한 줄 읽습니다.
borrowNode* readBorrowFileLine(FILE* borrowFile) {
    borrowNode* node = (borrowNode *) calloc(1, sizeof(borrowNode));
    fscanf(borrowFile, "%d||%d||%ld||%ld\n", &(node -> borrow.studentId), &(node -> borrow.bookId), &(node -> borrow.borrowDateSec), &(node -> borrow.returnDateSec));
    return node;
}


int isEmptyBorrow(borrow b) {
    return b.studentId == 0 && b.studentId == 0 && b.borrowDateSec == 0 && b.returnDateSec == 0;
}


// borrow List의 맨 뒤에 borrow을 하나 추가하는 함수
void addBorrow(borrowNode *borrowList, borrowNode *addedBorrow) {
    if (borrowList == NULL) {
        printf("borrowList는 NULL 일 수 없습니다.\n");
        return;
    } else if (addedBorrow == NULL) {
        printf("addedBorrow은 NULL 일 수 없습니다.\n");
        return;
    }

    // List의 첫 번째 요소라면
    if (borrowList -> borrow.studentId == 0) {
        borrowList -> borrow = addedBorrow -> borrow;
    } else {
        while (borrowList -> next != NULL) {
            borrowList = borrowList -> next;
        }

        borrowList -> next = addedBorrow;
    }
}

// borrow List의 at번째 원소를 지우는 함수
void removeBorrow(borrowNode *borrowList, int at) {
    if (borrowList == NULL) {
        printf("borrowList는 NULL 일 수 없습니다.\n");
        return;
    }

    if (at < 0) {
        printf("음수는 불가합니다.\n");
        return;
    }

    int length = borrowLength(*borrowList);
    if (length <= at) {
        printf("길이 %d인 리스트에서 %d번째 요소를 제거할 수 없습니다.\n", length, at);
        return;
    }

    if (at == 0) {
        // borrowList에 값이 없거나 하나 뿐일 때
        if (length <= 1) {
            borrowList -> borrow = initBorrow();
        } else {
            borrowNode* header = borrowList;

            // Header를 다음 것으로 이동
            *borrowList = *(borrowList -> next);
            free(header);
        }
    } else {
        borrowNode* beforeBorrowNode = getBorrowNode(borrowList, at - 1);

        // 맨 마지막 원소를 제거한다면
        if (length == at + 1) {
            free(beforeBorrowNode->next);
            beforeBorrowNode -> next = NULL;
        } else {
            borrowNode* willRemoveBorrowNode = getBorrowNode(beforeBorrowNode, 1);
            free(willRemoveBorrowNode);
            borrowNode* nextBorrowNode = getBorrowNode(beforeBorrowNode, 2);
            beforeBorrowNode -> next = nextBorrowNode;
        }
    }
}

borrowNode* getBorrowNode(borrowNode* borrowList, int at) {
    if (borrowList == NULL) {
        printf("borrowList는 NULL 일 수 없습니다.\n");
        return NULL;
    }

    int index = 0;

    while (borrowList -> next != NULL) {
        // 원하는 index에 도달하면 1을 리턴하고 retborrow에 borrow정보 assign
        if (at == index++) {
            return borrowList;
        }

        if (borrowList -> next == NULL) {
            break;
        }
        borrowList = borrowList -> next;
    }

    if (at == index++) {
        return borrowList;
    }

    // at보다 길이가 짧을 때 0을 리턴
    return NULL;
}

// borrow List의 길이를 구하는 함수
int borrowLength(borrowNode borrowList) {
    int count = 1;

    while (borrowList.next != NULL) {
        count++;
        if (borrowList.next == NULL) {
            break;
        }
        borrowList = *(borrowList.next);
    }

    // 첫 번째 요소가 비었을 때는 길이 0
    if (count == 1 && isEmptyBorrow(borrowList.borrow)) {
        return 0;
    }

    return count;
}


borrow initBorrow() {
    borrow borrow;
    borrow.studentId = 0;
    borrow.studentId = 0;

    time_t t = time(NULL);
    time_t ct = t + 60 * 60 * 24 * 30;
    struct tm *timer = localtime(&ct);

    // 일요일
    if (timer -> tm_wday == 0) {
        ct += 60 * 60 * 24;
    }

    borrow.borrowDateSec = t;
    borrow.returnDateSec = ct;
    return borrow;
}


// studentId 으로 BorrowNode 찾기
borrowNode* findBorrowNodeByStudentId(borrowNode* borrowList, int studentId) {
    borrowNode *rtnBorrowList = calloc(1, sizeof(borrowNode));
    while (!isEmptyBorrow(borrowList->borrow)) {
        if (borrowList->borrow.studentId == studentId) {
            borrowNode *tmpBorrow = calloc(1, sizeof(borrowNode));
            tmpBorrow->borrow = borrowList->borrow;
            addBorrow(rtnBorrowList, tmpBorrow);
        }
        if (borrowList->next == NULL) {
            break;
        }
        borrowList = borrowList->next;
    }

    if (isEmptyBorrow(rtnBorrowList->borrow))
        return NULL;
    return rtnBorrowList;
}


// bookId 로 BorrowNode 찾기
borrowNode* findBorrowNodeByBookId(borrowNode* borrowList, int bookId) {
    while (!isEmptyBorrow(borrowList->borrow)) {
        if (borrowList->borrow.bookId == bookId) {
            return borrowList;
        }
        if (borrowList->next == NULL) {
            break;
        }
        borrowList = borrowList->next;
    }

    if (borrowList->borrow.bookId == bookId)
        return borrowList;
    return NULL;
}



int isEqualBorrow(borrow leftBorrow, borrow rightBorrow) {
    return leftBorrow.bookId == rightBorrow.bookId &&
           leftBorrow.studentId == rightBorrow.studentId &&
           leftBorrow.borrowDateSec == rightBorrow.borrowDateSec &&
           leftBorrow.returnDateSec == rightBorrow.returnDateSec;
}


// borrowNode index 번호 찾기
int indexOfBorrowNode(borrowNode* borrowList, borrowNode foundBorrowNode) {
    int count = 0;
    while (!isEmptyBorrow(borrowList->borrow)) {
        if (isEqualBorrow(borrowList->borrow, foundBorrowNode.borrow)) {
            return count;
        }
        borrowList = borrowList->next;
        count++;
    }
    return -1;
}


void printBorrow(borrow b) {
    printf("도서번호: %d\n", b.bookId);
    printf("학번: %d\n", b.studentId);
    printf("대여일자: ");
    printDate(b.borrowDateSec);
    printf("\n");
    printf("반납일자: ");
    printDate(b.returnDateSec);
    printf("\n\n");
}

void printDate(time_t t) {
    struct tm *time = localtime(&t);

    printf("%d년 %d월 %d일 %s요일", time->tm_year + 1900, time->tm_mon + 1 , time->tm_mday, wdayList[time->tm_wday]);
}

void printBorrowList(borrowNode printingBorrow) {
    while (!isEmptyBorrow(printingBorrow.borrow)) {
        printBorrow(printingBorrow.borrow);
        if (printingBorrow.next == NULL)
            break;
        printingBorrow = *printingBorrow.next;
        printf("\n");
    }
}

void closeBorrowFile() {
    fclose(borrowFile);
}