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
    bookNode *newBookNode = (bookNode *) calloc(1, sizeof(bookNode)), *tmpBookNode = bookList;
    newBookNode->book = initBook();
    int i = 0, maxBookId;

    printf(">> 도서 등록 <<\n");
    printf("도서명: ");
    scanf("%[^\n]", newBookNode -> book.name);
    getchar();

    printf("출판사: ");
    scanf("%[^\n]", newBookNode -> book.publisherName);
    getchar();

    printf("저자명: ");
    scanf("%[^\n]", newBookNode -> book.authorName);
    getchar();

    printf("ISBN: ");
    scanf("%lu", &(newBookNode -> book.ISBN));
    getchar();

    printf("소장처: ");
    scanf("%[^\n]", newBookNode -> book.holdingInstitution);
    putchar(getchar());

    while (!isEmptyBook(tmpBookNode->book)) {
        if (tmpBookNode->book.ISBN <= newBookNode->book.ISBN)
            i++;
        if (tmpBookNode->book.bookId > maxBookId)
            maxBookId = tmpBookNode->book.bookId;
        if (tmpBookNode->next == NULL)
            break;
        tmpBookNode = tmpBookNode->next;
    }

    printf("자동입력사항\n\n");
    printf("대여가능 여부: Y\n");
    printf("도서 번호: %d\n\n", maxBookId + 1);
    printf("등록하시겠습니까? (Y or N)");

    char c = getchar();
    if (c == 'Y' || c == 'y') {
        newBookNode -> book.bookId = maxBookId + 1;
        insertBook(bookList, newBookNode, i);
        overwriteBookFile(*bookList);
    } else {
        printf("취소되었습니다.\n\n");
    }
}

// 도서 삭제
void deleteBook(bookNode *bookList) {
    unsigned long isbn;
    int bookId, menu;
    char name[20];
    bookNode *findBookResults;

    printf(">> 도서 삭제 <<\n");
    printf("1.도서명 검색\t\t\t2.ISBN 검색\n\n");
    printf("검색 번호를 입력하세요: ");
    scanf("%d", &menu);
    putchar(getchar());

    // 도서명 검색
    if (menu == 1) {
        printf("도서명을 입력하세요: ");
        scanf("%[^\n]", name);
        putchar(getchar());
        findBookResults = findBookNodeByBookName(bookList, name);
    }

    // ISBN 검색
    else {
        printf("ISBN : ");
        scanf("%lu", &isbn);
        putchar(getchar());
        findBookResults = findBookNodeByISBN(bookList, isbn);
    }
    // TODO: 도서번호: 1468212(삭제 가능 여부 : N), 1455434(삭제 가능 여부 : Y)
    printf(">> 검색 결과 <<\n");
    printBookList(*findBookResults);

    printf("삭제할 도서의 번호를 입력하세요: ");
    scanf("%d", &bookId);
    getchar();

    bookNode *foundBookNode = findBookNodeByBookId(findBookResults, bookId);

    // 삭제 가능
    if (foundBookNode -> book.isBorrowable == 'Y') {
        int index = indexOfBookNode(findBookResults, *foundBookNode);
        if (index == -1) {
            printf("도서가 없습니다.\n");
        } else {
            removeBook(bookList, index);
            overwriteBookFile(*bookList);
        }
    }

    // 삭제 불가능
    else {
        printf("이 도서는 삭제할 수 없습니다.\n");
    }
}

// 도서 대여
void lendBook(bookNode *bookList, borrowNode *borrowList, clientNode *clientList) {
    char searchKeyword[20];
    unsigned long isbn;
    int studentId, bookId, menu;
    bookNode *findBookResults;

    printf(">>도서 대여<<\n");
    printf("1.도서명 검색\t\t\t2.ISBN 검색\n");
    printf("검색 번호를 입력하세요: ");
    scanf("%d", &menu);
    putchar(getchar());

    // 도서명 검색
    if (menu == 1) {
        printf("도서명을 입력하세요: ");
        scanf("%[^\n]", searchKeyword);
        findBookResults = findBookNodeByBookName(bookList, searchKeyword);
    }

    // ISBN 검색
    else {
        printf("ISBN을 입력하세요: ");
        scanf("%lu", &isbn);
        findBookResults = findBookNodeByISBN(bookList, isbn);
    }
    putchar(getchar());

    if (findBookResults == NULL) {
        printf("해당 책이 없습니다.\n");
        return;
    }

    printf(">> 검색 결과 <<\n");
    printBookList(*findBookResults);

    printf("\n학번을 입력하세요: ");
    scanf("%d", &studentId);
    getchar();

    if (findClientNodeById(clientList, studentId) == NULL) {
        printf("일치하는 학번을 가진 학생이 없습니다.\n");
        return;
    }

    printf("도서번호를 입력하세요: ");
    scanf("%d", &bookId);
    putchar(getchar());

    bookNode *lentBook = findBookNodeByBookId(bookList, bookId);
    if (lentBook == NULL) {
        printf("일치하는 id를 가진 책이 없습니다.\n");
        return;
    }

    if (lentBook->book.isBorrowable == 'N') {
        printf("이 책은 대여할 수 없습니다.\n");
        return;
    }

    printf("이 도서를 대여합니까? (Y or N)");
    char c = getchar();
    putchar(getchar());
    if (c == 'Y' || c == 'y') {
        lentBook -> book.isBorrowable = 'N';
        borrowNode *newBorrow = calloc(1, sizeof(borrowNode));

        // 대여일자, 반납일자 생성
        newBorrow->borrow = initBorrow();

        newBorrow->borrow.studentId = studentId;
        newBorrow->borrow.bookId = bookId;
        addBorrow(borrowList, newBorrow);

        overwriteBookFile(*bookList);
        overwriteBorrowFile(*borrowList);
        printf("도서가 대여되었습니다.\n");
    } else {
        printf("도서 대여가 취소되었습니다.\n");
    }
}

// 도서 반납
void returnBook(clientNode *clientList, bookNode *bookList, borrowNode *borrowList) {
    int studentId, bookId;
    printf("학번을 입력하세요: ");
    scanf("%d", &studentId);
    putchar(getchar());

    clientNode *findClientResult = findClientNodeById(clientList, studentId);
    if (findClientResult == NULL) {
        printf("해당 학번을 가진 학생이 존재하지 않습니다.\n");
        return;
    }

    printf(">> 회원의 대여목록 <<\n");
    borrowNode *findBorrowResults = findBorrowNodeByStudentId(borrowList, studentId);
    printBorrowList(*findBorrowResults);

    printf("반납할 도서를 입력하세요: ");
    scanf("%d", &bookId);
    putchar(getchar());

    borrowNode *findBorrowByBookIdResult = findBorrowNodeByBookId(findBorrowResults, bookId);
    bookNode *findBookByBookIdResult = findBookNodeByBookId(bookList, bookId);
    if (findBorrowByBookIdResult == NULL || findBookByBookIdResult == NULL) {
        printf("해당 도서번호를 가진 책이 존재하지 않습니다.\n");
        return;
    }

    printf("도서를 반납처리 할까요? (Y or N)");
    char c = getchar();
    putchar(getchar());
    if (c == 'Y' || c == 'y') {
        // borrow 파일 수정
        removeBorrow(borrowList, indexOfBorrowNode(borrowList, *findBorrowByBookIdResult));
        printBorrowList(*borrowList);
        overwriteBorrowFile(*borrowList);

        // book 파일 수정
        findBookByBookIdResult->book.isBorrowable = 'Y';
        overwriteBookFile(*bookList);
        printf("도서가 반납되었습니다.\n");
    } else {
        printf("도서반납이 취소되었습니다.\n");
    }
}

// 도서 검색
void searchBook() {
    
}

// 회원 목록
int loadMemberList(clientNode *clientList) {
    int menu, studentId;
    char name[20];
    clientNode *findResult;

    while (1) {
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
                return 1;
        }
    }
    return 0;
}
