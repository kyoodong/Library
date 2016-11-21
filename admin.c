//
//  admin.c
//  Library
//
//  Created by 이동규 on 2016. 11. 14..
//  Copyright © 2016년 이동규. All rights reserved.
//

#include "admin.h"
#include "file.h"
#include <stdlib.h>


// 도서 등록
void registBook(bookNode* bookList) {
    bookNode *newBookNode = calloc(1, sizeof(bookNode));
    newBookNode->book = initBook();
    int length = bookLength(*bookList);
    bookNode *lastBookNode = getBookNode(bookList, length - 1);

    printf("도서명 : ");
    scanf("%[^\n]", newBookNode -> book.name);

    printf("출판사 : ");
    scanf("%[^\n]", newBookNode -> book.publisherName);

    printf("저자명 : ");
    scanf("%[^\n]", newBookNode -> book.authorName);

    printf("ISBN : ");
    scanf("%lu", &(newBookNode -> book.ISBN));

    printf("소장처 : ");
    scanf("%[^\n]", newBookNode -> book.holdingInstitudtion);

    lastBookNode -> next = newBookNode;


}

// 도서 삭제
void deleteBook() {
    
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
