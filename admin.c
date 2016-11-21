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
void lendBook(bookNode *bookList, borrowNode *borrowList, clientNode *clientList) {
    char searchKeyword[20];
    unsigned long isbn;
    int studentId, bookId;

    printf("도서명 또는 ISBN 입력하세요 : ");
    scanf("%[^\n]", searchKeyword);
    getchar();
    isbn = atoll(searchKeyword);

    bookNode *findBookResults = findBookNodeByBookName(bookList, searchKeyword);
    if (isbn) {
        bookNode *findBookByISBNResults = findBookNodeByISBN(bookList, isbn);
        addBook(findBookResults, findBookByISBNResults);
    }

    if (findBookResults == NULL) {
        printf("해당 책이 없습니다.\n");
        return;
    }

    printBookList(*findBookResults);

    printf("\n학번: ");
    scanf("%d", &studentId);
    getchar();

    if (findClientNodeById(clientList, studentId) == NULL) {
        printf("일치하는 학번을 가진 학생이 없습니다.\n");
        return;
    }

    printf("책 번호: ");
    scanf("%d", &bookId);
    getchar();

    bookNode *lentBook = findBookNodeByBookId(bookList, bookId);
    if (lentBook == NULL) {
        printf("일치하는 id를 가진 책이 없습니다.\n");
        return;
    }

    if (lentBook->book.isBorrowable == 'N') {
        printf("이미 대여된 책입니다.\n");
        return;
    }

    lentBook -> book.isBorrowable = 'N';
    borrowNode *newBorrow = calloc(1, sizeof(borrowNode));

    // 대여일자, 반납일자 생성
    newBorrow->borrow = initBorrow();

    newBorrow->borrow.studentId = studentId;
    newBorrow->borrow.bookId = bookId;
    addBorrow(borrowList, newBorrow);

    overwriteBookFile(*bookList);
    overwriteBorrowFile(*borrowList);
}

// 도서 반납
void returnBook(clientNode *clientList, bookNode *bookList, borrowNode *borrowList) {
    int studentId, bookId;
    printf("학번: ");
    scanf("%d", &studentId);
    getchar();

    clientNode *findClientResult = findClientNodeById(clientList, studentId);
    if (findClientResult == NULL) {
        printf("해당 학번을 가진 학생이 존재하지 않습니다.\n");
        return;
    }

    borrowNode *findBorrowResults = findBorrowNodeByStudentId(borrowList, studentId);
    printBorrowList(*findBorrowResults);

    printf("도서 번호: ");
    scanf("%d", &bookId);
    getchar();

    borrowNode *findBorrowByBookIdResult = findBorrowNodeByBookId(findBorrowResults, bookId);
    bookNode *findBookByBookIdResult = findBookNodeByBookId(bookList, bookId);
    if (findBorrowByBookIdResult == NULL || findBookByBookIdResult == NULL) {
        printf("해당 도서번호를 가진 책이 존재하지 않습니다.\n");
        return;
    }

    // borrow 파일 수정
    removeBorrow(borrowList, indexOfBorrowNode(borrowList, *findBorrowByBookIdResult));
    overwriteBorrowFile(*borrowList);

    // book 파일 수정
    findBookByBookIdResult->book.isBorrowable = 'Y';
    overwriteBookFile(*bookList);
}

// 도서 검색
void searchBook() {
    
}

// 회원 목록
void loadMemberList(clientNode *clientList) {
    int menu, studentId;
    char name[20];
    clientNode *findResult;

    printf("1.이름 검색\n");
    printf("2.학번 검색\n");
    printf("3.전체 검색\n");
    printf("4.이전 메뉴\n");

    scanf("%d", &menu);
    getchar();

    switch (menu) {
        // 이름
        case 1:
            printf("이름: ");
            scanf("%s", name);
            getchar();
            findResult = findClientNodeByName(clientList, name);
            if (findResult == NULL)
                printf("해당되는 사용자가 존재하지 않습니다.\n");
            else
                printClient(findResult->client);
            break;

        // 학번
        case 2:
            printf("학번: ");
            scanf("%d", &studentId);
            getchar();
            findResult = findClientNodeById(clientList, studentId);
            if (findResult == NULL)
                printf("해당되는 사용자가 존재하지 않습니다.\n");
            else
                printClient(findResult->client);
            break;

        case 3:
            printClientList(*clientList);
            break;

        case 4:
            break;
    }
}
