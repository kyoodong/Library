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


// 파일 불러오기
void loadFile(clientNode *clients, bookNode *books, borrowNode *borrows) {
    // 파일 읽기 모드로 열기
    FILE *clientFile = fopen(CLIENT_FILE_PATH, "r");
    FILE *bookFile = fopen(BOOK_FILE_PATH, "r");
    FILE *borrowFile = fopen(BORROW_FILE_PATH, "r");

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
    
    fclose(clientFile);
    fclose(bookFile);
    fclose(borrowFile);
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
    fscanf(bookFile, "%d||%[^|]||%[^|]||%[^|]||%ld||%[^|]||%c\n", &(node -> book.bookId), node -> book.name, node -> book.publisherName, node -> book.authorName, &(node -> book.ISBN), node -> book.holdingInstitudtion, &(node -> book.isBorrowable));
    return node;
}

// borrow 파일 한 줄 읽기
borrowNode* readBorrowFileLine(FILE* borrowFile) {
    borrowNode* node = (borrowNode *) calloc(1, sizeof(borrowNode));
    fscanf(borrowFile, "%d||%d||%ld||%ld\n", &(node -> borrow.studentId), &(node -> borrow.bookId), &(node -> borrow.borrowDateSec), &(node -> borrow.returnDateSec));
    return node;
}

// client 파일 한 줄 읽고 버리기
void popClientFileLine(FILE* clientFile) {
    fscanf(clientFile, "%*d||%*[^|]||%*[^|]||%*[^|]||%*s\n");
}

// book 파일 한 줄 읽고 버리기
void popBookFileLine(FILE* bookFile) {
    fscanf(bookFile, "%*d||%*[^|]||%*[^|]||%*[^|]||%*ld||%*[^|]||%*c\n");
}

// borrow 파일 한 줄 읽고 버리기
void popBorrowFileLine(FILE* borrowFile) {
    fscanf(borrowFile, "%*d||%*d||%*ld||%*ld\n");
}


// 회원 추가
void rewriteClientFile(clientNode node) {
    FILE *clientFile = fopen(CLIENT_FILE_PATH, "w");
    if (clientFile == NULL) {
        printf("파일 열기 실패\n");
        return;
    }

    while (!isEmptyClient(node.client)) {
        fprintf(clientFile, "%d||%s||%s||%s||%s\n",
                                    node.client.studentId,                        // 학번
                                    node.client.password,                       // 비밀번호
                                    node.client.name,                           // 이름
                                    node.client.address,                   // 첫 주소
                                    node.client.phone                     // 전화번호 1 ex) 3367-7355의 3367
        );

        node = *(node.next);
    }
    fclose(clientFile);
}


// 책 추가
void rewriteBookFile(bookNode node) {
    FILE *bookFile = fopen(BOOK_FILE_PATH, "w");
    if (bookFile == NULL) {
        printf("파일 열기 실패\n");
        return;
    }

    while (!isEmptyBook(node.book)) {
        fprintf(bookFile, "%d||%s||%s||%s||%lld||%s||Y\n",
                node.book.bookId++,                       // 도서 번호
                node.book.bookName,                       // 책 이름
                node.book.publisherName,                  // 출판사 이름
                node.book.authorName,                     // 저자 이름
                node.book.ISBN++,                         // ISBN
                node.book.holdingLocation                 // 소장처
        );

        node = *(node.next);
    }
    fclose(bookFile);
}


void printClient(client c) {
    printf("%d\n", c.studentId);
    printf("%s\n", c.name);
    printf("%s\n", c.address);
    printf("%s\n", c.phone);
    printf("%s\n", c.password);
}






































