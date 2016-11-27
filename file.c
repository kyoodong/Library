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

    // client 파일 데이터 추출
    while (!feof(clientFile)) {
        clientNode* node = readClientFileLine(clientFile);
        addClient(clients, node);
    }

    // book 파일 데이터 추출
    while (!feof(bookFile)) {
        bookNode* node = readBookFileLine(bookFile);
        addBook(books, node);
    }

    // borrow 파일 데이터 추출
    while (!feof(borrowFile)) {
        borrowNode* node = readBorrowFileLine(borrowFile);
        addBorrow(borrows, node);
    }

    fflush(clientFile);
    fflush(bookFile);
    fflush(borrowFile);
}


// client 파일 한 줄 읽기
// TODO: 질문하기 clientNode* 이 clientNode였을 때 잘 안됐던 이유
clientNode* readClientFileLine(FILE* clientFile) {
    clientNode* node = (clientNode *) calloc(1, sizeof(clientNode));
    fscanf(clientFile, "%d||%[^|]||%[^|]||%[^|]||%[^\n]", &(node -> client.studentId), node -> client.password, node -> client.name, node -> client.address, node -> client.phone);
    return node;
}

// book 파일 한 줄 읽기
bookNode* readBookFileLine(FILE* bookFile) {
    bookNode* node = (bookNode *) calloc(1, sizeof(bookNode));
    fscanf(bookFile, "%d||%[^|]||%[^|]||%[^|]||%ld||%[^|]||%c\n", &(node -> book.bookId), node -> book.name, node -> book.publisherName, node -> book.authorName, &(node -> book.ISBN), node -> book.holdingInstitution, &(node -> book.isBorrowable));
    return node;
}

// borrow 파일 한 줄 읽기
borrowNode* readBorrowFileLine(FILE* borrowFile) {
    borrowNode* node = (borrowNode *) calloc(1, sizeof(borrowNode));
    fscanf(borrowFile, "%d||%d||%ld||%ld\n", &(node -> borrow.studentId), &(node -> borrow.bookId), &(node -> borrow.borrowDateSec), &(node -> borrow.returnDateSec));
    return node;
}

// 회원 추가
void overwriteClientFile(clientNode node) {
    rewind(clientFile);

    while (!isEmptyClient(node.client)) {
        fprintf(clientFile, "%d||%s||%s||%s||%s\n",
                node.client.studentId,                  // 학번
                node.client.password,                   // 비밀번호
                node.client.name,                       // 이름
                node.client.address,                    // 첫 주소
                node.client.phone                       // 전화번호 1 ex) 3367-7355의 3367
        );

        if (node.next == NULL)
            break;
        node = *(node.next);
    }
    fflush(clientFile);
}


// 책 추가
void overwriteBookFile(bookNode node) {
    rewind(bookFile);

    while (!isEmptyBook(node.book)) {
        fprintf(bookFile, "%d||%s||%s||%s||%lu||%s||%c\n",
                node.book.bookId,                         // 도서 번호
                node.book.name,                           // 책 이름
                node.book.publisherName,                  // 출판사 이름
                node.book.authorName,                     // 저자 이름
                node.book.ISBN,                           // ISBN
                node.book.holdingInstitution,             // 소장처
                node.book.isBorrowable                    // 대여 가능 여부
        );
        if (node.next == NULL)
            break;

        node = *(node.next);
    }
    fflush(bookFile);
}


// 대여목록 추가
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

void printBook(bookNode b, int bookNum, int borrowableBookNum, int mode) {
    int i;
    char isBorrowable;
    bookNode* tmpBook = &b;

    printf("도서번호: ");
    for (i = 0; i < bookNum; ++i) {
        printf("%d(삭제 가능 여부: %c), ", tmpBook->book.bookId, tmpBook->book.isBorrowable);
        tmpBook = getBookNode(tmpBook, 1);
    }
    printf("\b\b\n");
    printf("도서명: %s\n", b.book.name);
    printf("출판사: %s\n", b.book.publisherName);
    printf("저자명: %s\n", b.book.authorName);
    printf("ISBN: %lu\n", b.book.ISBN);
    printf("소장처: %s\n", b.book.holdingInstitution);
    if (borrowableBookNum)
        isBorrowable = 'Y';
    else
        isBorrowable = 'N';
    if (mode == DELETE)
        printf("삭제 가능 여부: %c(%d/%d)\n", isBorrowable, borrowableBookNum, bookNum);
    else
        printf("대여 가능 여부: %c(%d/%d)\n", isBorrowable, borrowableBookNum, bookNum);
    printf("** Y는 대여가능, N은 대여불가를 의미\n");
    printf("** (x/y) : (대여된 총 권수 / 보유하고 있는 총 권수)\n\n");
}

void printBookList(bookNode printingBook, int mode) {
    int bookNum = 0, borrowableBookNum = 0;
    bookNode tmpBook;

    printf("\n\n>> 검색 결과 <<\n");
    while (!isEmptyBook(printingBook.book)) {
        bookNum = 1;
        if (printingBook.book.isBorrowable == 'Y')
            borrowableBookNum = 1;
        else borrowableBookNum = 0;

        tmpBook = printingBook;

        // 같은 책은 묶어서 출력
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
    printf("대여일자: %ld\n", b.borrowDateSec);
    printf("반납일자: %ld\n\n", b.returnDateSec);
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


void closeFile() {
    fclose(clientFile);
    fclose(bookFile);
    fclose(borrowFile);
}
