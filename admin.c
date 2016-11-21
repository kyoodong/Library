//
//  admin.c
//  Library
//
//  Created by 이동규 on 2016. 11. 14..
//  Copyright © 2016년 이동규. All rights reserved.
//

#include "admin.h"


// 도서 등록
void registerNewBook(bookNode *bookList) {
    bookNode *newBookNode = (bookNode *) calloc(1, sizeof(bookNode));
    newBookNode->book = initBook();
    int length = bookLength(*bookList);
    bookNode *lastBookNode = getBookNode(bookList, length - 1);

    printf("도서명 : ");
    scanf("%[^\n]", newBookNode -> book.name);
    getchar();

    printf("출판사 : ");
    scanf("%[^\n]", newBookNode -> book.publisherName);
    getchar();

    printf("저자명 : ");
    scanf("%[^\n]", newBookNode -> book.authorName);
    getchar();

    printf("ISBN : ");
    scanf("%lu", &(newBookNode -> book.ISBN));
    getchar();

    printf("소장처 : ");
    scanf("%[^\n]", newBookNode -> book.holdingInstitution);
    getchar();
    lastBookNode -> next = newBookNode;

    newBookNode -> book.bookId = lastBookNode -> book.bookId + 1;

    appendBookFile(newBookNode -> book);
}

// 도서 삭제
void deleteBook(bookNode *bookList) {
    unsigned long isbn;
    int bookId;
    printf("ISBN : ");
    scanf("%lu", &isbn);
    getchar();

    bookNode *hasSameISBNBookList = findBookNodeByISBN(bookList, isbn);
    printBookList(*hasSameISBNBookList);

    printf("도서번호: ");
    scanf("%d", &bookId);
    getchar();

    bookNode *foundBookNode = findBookNodeByBookId(hasSameISBNBookList, bookId);

    // 삭제 가능
    if (foundBookNode -> book.isBorrowable == 'Y') {
        int index = indexOfBookNode(hasSameISBNBookList, *foundBookNode);
        if (index == -1) {
            printf("도서가 없습니다.\n");
        } else {
            removeBook(bookList, index);
            overwriteBookFile(*bookList);
        }
    }

    // 삭제 불가능
    else {
        printf("누군가가 대여 중입니다. 삭제할 수 없습니다.\n");
    }
}

// 도서 대여
void lendBook() {
    
}

// 도서 반납
void returnedBook() {
    
}

// 도서 검색
void searchBook() {
    
}

// 회원 목록
void loadMemberList() {
    
}
