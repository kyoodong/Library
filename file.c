//
//  file.c
//  Library
//
//  Created by 이동규 on 2016. 11. 9..
//  Copyright © 2016년 이동규. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "list.h"

const char wdayList[][4] = {"일", "월", "화", "수", "목", "금", "토"};

FILE *clientFile;
FILE *bookFile;
FILE *borrowFile;

// 파일 불러오기
void loadFile(clientNode *clients, bookNode *books, borrowNode *borrows) {
    // 파일 읽기 모드로 열기
    clientFile = fopen(CLIENT_FILE_PATH, "r+");
    bookFile = fopen(BOOK_FILE_PATH, "r+");
    borrowFile = fopen(BORROW_FILE_PATH, "r+");

    if (clientFile == NULL) {
        printf("client 파일이 없습니다.\n");
        return;
    }

    if (bookFile == NULL) {
        printf("book 파일이 없습니다.\n");
        return;
    }

    if (borrowFile == NULL) {
        printf("borrow 파일이 없습니다.\n");
        return;
    }

    // client 파일에서 데이터를 추출하여 clients 에 저장합니다.
    while (!feof(clientFile)) {
        clientNode* node = readClientFileLine(clientFile);
        addClient(clients, node);
    }

    // book 파일에서 데이터를 추출하여 books 에 저장합니다.
    while (!feof(bookFile)) {
        bookNode* node = readBookFileLine(bookFile);
        addBook(books, node);
    }

    // borrow 파일에서 데이터를 추출 borrows에 저장합니다.
    while (!feof(borrowFile)) {
        borrowNode* node = readBorrowFileLine(borrowFile);
        addBorrow(borrows, node);
    }

    fflush(clientFile);
    fflush(bookFile);
    fflush(borrowFile);
}


// client 파일을 한 줄 읽습니다.
clientNode* readClientFileLine(FILE* clientFile) {
    clientNode* node = (clientNode *) calloc(1, sizeof(clientNode));
    fscanf(clientFile, "%d||%[^|]||%[^|]||%[^|]||%[^\n]", &(node -> client.studentId), node -> client.password, node -> client.name, node -> client.address, node -> client.phone);
    return node;
}

// book 파일을 한 줄 읽습니다.
bookNode* readBookFileLine(FILE* bookFile) {
    bookNode* node = (bookNode *) calloc(1, sizeof(bookNode));
    fscanf(bookFile, "%d||%[^|]||%[^|]||%[^|]||%ld||%[^|]||%c\n", &(node -> book.bookId), node -> book.name, node -> book.publisherName, node -> book.authorName, &(node -> book.ISBN), node -> book.holdingInstitution, &(node -> book.isBorrowable));
    return node;
}

// borrow 파일을 한 줄 읽습니다.
borrowNode* readBorrowFileLine(FILE* borrowFile) {
    borrowNode* node = (borrowNode *) calloc(1, sizeof(borrowNode));
    fscanf(borrowFile, "%d||%d||%ld||%ld\n", &(node -> borrow.studentId), &(node -> borrow.bookId), &(node -> borrow.borrowDateSec), &(node -> borrow.returnDateSec));
    return node;
}

// clientFile 을 clientList 의 정보로 덮어 씁니다.
void overwriteClientFile(clientNode clientList) {
    rewind(clientFile);

    while (!isEmptyClient(clientList.client)) {
        fprintf(clientFile, "%d||%s||%s||%s||%s\n",
                clientList.client.studentId,                  // 학번
                clientList.client.password,                   // 비밀번호
                clientList.client.name,                       // 이름
                clientList.client.address,                    // 첫 주소
                clientList.client.phone                       // 전화번호 1 ex) 3367-7355의 3367
        );

        if (clientList.next == NULL)
            break;
        clientList = *(clientList.next);
    }
    fflush(clientFile);
}


// bookFile 을 bookList 의 정보로 덮어 씁니다.
void overwriteBookFile(bookNode bookList) {
    rewind(bookFile);

    while (!isEmptyBook(bookList.book)) {
        fprintf(bookFile, "%d||%s||%s||%s||%lu||%s||%c\n",
                bookList.book.bookId,                         // 도서 번호
                bookList.book.name,                           // 책 이름
                bookList.book.publisherName,                  // 출판사 이름
                bookList.book.authorName,                     // 저자 이름
                bookList.book.ISBN,                           // ISBN
                bookList.book.holdingInstitution,             // 소장처
                bookList.book.isBorrowable                    // 대여 가능 여부
        );
        if (bookList.next == NULL)
            break;

        bookList = *(bookList.next);
    }
    fflush(bookFile);
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


void printClient(client c) {
    printf("학번: %d\n", c.studentId);
    printf("이름: %s\n", c.name);
    printf("주소: %s\n", c.address);
    printf("전화번호: %s\n\n", c.phone);
//    printf("비밀번호: %s\n", c.password);
}

void printClientList(clientNode printingClient) {
    while (!isEmptyClient(printingClient.client)) {
        printClient(printingClient.client);
        if (printingClient.next == NULL)
            break;
        printingClient = *printingClient.next;
        printf("\n");
    }
}

// book의 정보를 출력합니다.
// 동일한 책이 여러권 있을 때는 묶음 출력을 하기 위해 bookNode 의 형태로 책 정보를 받습니다.
// bookNum: 책의 총 권 수
// borrowableBookNum: 빌릴 수 있는 책의 총 권 수
// mode: 책 삭제 모드인지, 대여 모드인지 구분하는 변수
void printBook(bookNode bookList, int bookNum, int borrowableBookNum, int mode) {
    int i;
    char isBorrowable;

    // ISBN 이 같은 여러권의 책을 묶음 출력하기 위함입니다. 반복문을 돌더라도 bookList 의 Header 정보를 보존시켜야하기 때문입니다.
    bookNode* tmpBook = &bookList;

    printf("도서번호: ");

    // ISBN 이 같은 책들의 bookId와 대여 가능 여부를 출력합니다.
    for (i = 0; i < bookNum; ++i) {
        printf("%d(삭제 가능 여부: %c), ", tmpBook->book.bookId, tmpBook->book.isBorrowable);
        tmpBook = getBookNode(tmpBook, 1);
    }
    printf("\b\b\n");
    printf("도서명: %s\n", bookList.book.name);
    printf("출판사: %s\n", bookList.book.publisherName);
    printf("저자명: %s\n", bookList.book.authorName);
    printf("ISBN: %lu\n", bookList.book.ISBN);
    printf("소장처: %s\n", bookList.book.holdingInstitution);

    // 대여 가능한 책이 단 한권이라도 존재한다면 그 책은 대여할 수 있다고 출력합니다.
    if (borrowableBookNum)
        isBorrowable = 'Y';
    else
        isBorrowable = 'N';
    if (mode == DELETE)
        printf("삭제 가능 여부: %c(%d/%d)\n", isBorrowable, borrowableBookNum, bookNum);
    else
        printf("대여 가능 여부: %c(%d/%d)\n", isBorrowable, borrowableBookNum, bookNum);

    printf("** Y는 대여가능, N은 대여불가를 의미\n");
    printf("** (x/y) : (대여할 수 있는 총 권수 / 보유하고 있는 총 권수)\n\n");
}

void printBookList(bookNode printingBook, int mode) {
    int bookNum = 0, borrowableBookNum = 0;
    bookNode tmpBook;

    printf("\n\n>> 검색 결과 <<\n");

    // 모든 책을 출력
    while (!isEmptyBook(printingBook.book)) {
        bookNum = 1;
        if (printingBook.book.isBorrowable == 'Y')
            borrowableBookNum = 1;
        else borrowableBookNum = 0;

        // 같은 책은 묶어서 출력하기 위해 반복문을 또 돌아야 합니다.
        // 반복문을 돌더라도 printingBook 의 Header 값을 보존시키기 위함입니다.
        tmpBook = printingBook;

        // 같은 책은 묶어서 출력하기 위해 ISBN 이 같은 책의 수를 구합니다. 책의 수 만큼 반복문을 돌며 묶음 출력하기 위함 입니다.
        while (tmpBook.next != NULL) {
            if (tmpBook.next->book.ISBN == tmpBook.book.ISBN) {
                bookNum++;
                if (tmpBook.next->book.isBorrowable == 'Y')
                    borrowableBookNum++;
                tmpBook = *tmpBook.next;
            } else
                break;
        }
        printBook(printingBook, bookNum, borrowableBookNum, mode);
        printingBook = tmpBook;
        if (printingBook.next == NULL)
            break;
        printingBook = *printingBook.next;
        printf("\n");
    }
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


void closeAllFilePointer() {
    fclose(clientFile);
    fclose(bookFile);
    fclose(borrowFile);
}
