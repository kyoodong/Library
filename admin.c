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
    book *newBook = calloc(1, sizeof(book));
    printf("도서명 : ");
    scanf("%[^\n]", newBook -> name);

    printf("출판사 : ");
    scanf("%[^\n]", newBook -> publisherName);

    printf("저자명 : ");
    scanf("%[^\n]", newBook -> authorName);

    printf("ISBN : ");
    scanf("%lu", &(newBook -> ISBN));

    printf("소장처 : ");
    scanf("%[^\n]", newBook -> holdingInstitudtion);

    
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
