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


void loadFile(clientNode *clients, bookNode *books, borrowNode *borrows) {
    // 파일 이름
    char clientFileName[] = "./client.txt";
    char bookFileName[] = "./book.txt";
    char borrowFileName[] = "./borrow.txt";
    
    // 파일 읽기 모드로 열기
    FILE *clientFile = fopen(clientFileName, "r");
    FILE *bookFile = fopen(bookFileName, "r");
    FILE *borrowFile = fopen(borrowFileName, "r");
    
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
        // TODO - 동적 생성 수정해야함
        clientNode* node = (clientNode *) calloc(1, sizeof(clientNode));
        fscanf(clientFile, "%d||%[^|]||%[^|]||%[^|]||%s\n", &(node -> client.studentId), node -> client.password, node -> client.name, node -> client.address, node -> client.phone);
        addClient(clients, node);
        i++;
    }
    
    // book 파일 데이터 추출
    while (!feof(bookFile)) {
        // TODO - 동적 생성 수정해야함
        bookNode* node = (bookNode *) calloc(1, sizeof(bookNode));
<<<<<<< HEAD
        fscanf(bookFile, "%d||%[^|]||%[^|]||%[^|]||%ld||%[^|]||%c\n", &(node -> book.bookId), node -> book.name, node -> book.publisherName, node -> book.authorName, &(node -> book.ISBN), node -> book.holdingInstitudtion, &(node -> book.isBorrowable));
=======
        fscanf(bookFile, "%d||%[^|]||%[^|]||%[^|]||%ld||%s\n", &(node -> book.bookId), node -> book.name, node -> book.publisherName, node -> book.authorName, &(node -> book.ISBN), node -> book.holdingInstitudtion);
>>>>>>> 935ed26... File load 동적 할당
        addBook(books, node);
        i++;
    }
    
    // borrow 파일 데이터 추출
    while (!feof(borrowFile)) {
        // TODO - 동적 생성 수정해야함
        borrowNode* node = (borrowNode *) calloc(1, sizeof(borrowNode));
        fscanf(borrowFile, "%d||%d||%ld||%ld\n", &(node -> borrow.studentId), &(node -> borrow.bookId), &(node -> borrow.borrowDateSec), &(node -> borrow.returnDateSec));
        addBorrow(borrows, node);
        i++;
    }
    
    fclose(clientFile);
    fclose(bookFile);
    fclose(borrowFile);
}
