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
    
    // client 파일 데이터 추출 기본 단계
    int i = 0;
    
    // client 파일 데이터 추출
    while (!feof(clientFile)) {
        clientNode node = readClientFileLine(clientFile);
        addClient(clients, &node);
        i++;
    }
    
    // book 파일 데이터 추출
    while (!feof(bookFile)) {
        bookNode node = readBookFileLine(bookFile);
        addBook(books, &node);
        i++;
    }
    
    // borrow 파일 데이터 추출
    while (!feof(borrowFile)) {
        borrowNode node = readBorrowFileLine(borrowFile);
        addBorrow(borrows, &node);
        i++;
    }
    
    fclose(clientFile);
    fclose(bookFile);
    fclose(borrowFile);
}


// client파일 한 줄 읽기
clientNode readClientFileLine(FILE* clientFile) {
    clientNode* node = (clientNode *) calloc(1, sizeof(clientNode));
    fscanf(clientFile, "%d||%[^|]||%[^|]||%[^|]||%[^\n]", &(node -> client.studentId), node -> client.password, node -> client.name, node -> client.address, node -> client.phone);
    return *node;
}

// book파일 한 줄 읽기
bookNode readBookFileLine(FILE* bookFile) {
    bookNode* node = (bookNode *) calloc(1, sizeof(bookNode));
    fscanf(bookFile, "%d||%[^|]||%[^|]||%[^|]||%ld||%[^|]||%c\n", &(node -> book.bookId), node -> book.name, node -> book.publisherName, node -> book.authorName, &(node -> book.ISBN), node -> book.holdingInstitudtion, &(node -> book.isBorrowable));
    return *node;
}

// borrow파일 한 줄 읽기
borrowNode readBorrowFileLine(FILE* borrowFile) {
    borrowNode* node = (borrowNode *) calloc(1, sizeof(borrowNode));
    fscanf(borrowFile, "%d||%d||%ld||%ld\n", &(node -> borrow.studentId), &(node -> borrow.bookId), &(node -> borrow.borrowDateSec), &(node -> borrow.returnDateSec));
    return *node;
}

// client파일 한 줄 읽고 버리기
void popClientFileLine(FILE* clientFile) {
    fscanf(clientFile, "%*d||%*[^|]||%*[^|]||%*[^|]||%*s\n");
}

// book파일 한 줄 읽고 버리기
void popBookFileLine(FILE* bookFile) {
    fscanf(bookFile, "%*d||%*[^|]||%*[^|]||%*[^|]||%*ld||%*[^|]||%*c\n");
}

// borrow파일 한 줄 읽고 버리기
void popBorrowFileLine(FILE* borrowFile) {
    fscanf(borrowFile, "%*d||%*d||%*ld||%*ld\n");
}


// 회원 추가
void insertClientToFile(client newClient, int lineNum) {
    FILE *clientFile = fopen(CLIENT_FILE_PATH, "r+");
    int i;
    for (i = 0; i < lineNum; i++) {
        popClientFileLine(clientFile);
    }
    
    while (!feof(clientFile)) {
        clientNode tmpClient = readClientFileLine(clientFile);
        if (isEmptyClient(tmpClient.client)) {
            break;
        }
        fprintf(clientFile, "%d||%s||%s||%s||%s\n",
                newClient.studentId,                        // 학번
                newClient.password,                       // 비밀번호
                newClient.name,                           // 이름
                newClient.address,                   // 첫 주소
                newClient.phone                     // 전화번호 1 ex) 3367-7355의 3367
                );
        newClient = tmpClient.client;
    }
    
    fprintf(clientFile, "%d||%s||%s||%s||%s\n",
            newClient.studentId,                        // 학번
            newClient.password,                       // 비밀번호
            newClient.name,                           // 이름
            newClient.address,                   // 첫 주소
            newClient.phone                     // 전화번호 1 ex) 3367-7355의 3367
            );
}






































