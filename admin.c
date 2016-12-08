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

    // 책 전체를 훑습니다. 파일이 가진 bookId 의 최대값을 알아내기 위함입니다.
    // 새로 추가될 책의 bookId 는 bookId 의 최대값 + 1 입니다. bookId 는 unique 한 값이기 때문입니다.
    // 책을 ISBN 순으로 오름차순 정렬하기 위해 i값을 통해 적절한 위치를 찾아냅니다.
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

    // 도서명을 통해 삭제할 수 있는 책이 있는지 검색 합니다.
    if (menu == 1) {
        printf("도서명을 입력하세요: ");
        scanf("%[^\n]", name);
        putchar(getchar());
        findBookResults = findBookNodeByBookName(bookList, name);
    }

    // ISBN 을 통해 삭제할 수 있는 책이 있는지 검색 합니다.
    else {
        printf("ISBN : ");
        scanf("%lu", &isbn);
        putchar(getchar());
        findBookResults = findBookNodeByISBN(bookList, isbn);
    }
    printBookList(*findBookResults, DELETE);

    printf("삭제할 도서의 번호를 입력하세요: ");
    scanf("%d", &bookId);
    getchar();

    if (findBookNodeByBookId(findBookResults, bookId)) {
        printf("해당 도서를 검색한 뒤 삭제해주세요.");
        return;
    }

    bookNode *hasBookIdResults = findBookNodeByBookId(findBookResults, bookId);

    // 책을 빌린 사람이 없다면 대여 가능하고, 대여 가능한 책은 삭제도 가능합니다.
    // 삭제 가능하다면 책을 삭제하고 결과를 파일에 반영합니다.
    if (hasBookIdResults -> book.isBorrowable == 'Y') {
        int index = indexOfBookNode(findBookResults, *hasBookIdResults);
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

    // 도서명을 통해 삭제할 수 있는 책이 있는지 검색 합니다.
    if (menu == 1) {
        printf("도서명을 입력하세요: ");
        scanf("%[^\n]", searchKeyword);
        findBookResults = findBookNodeByBookName(bookList, searchKeyword);
    }

    // ISBN 을 통해 삭제할 수 있는 책이 있는지 검색 합니다.
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

    printBookList(*findBookResults, SEARCH);

    bookNode *searchTmpBookList = findBookResults;
    while (!isEmptyBook(searchTmpBookList->book)) {
        // ISBN 발견 시 return
        if (searchTmpBookList->book.isBorrowable == 'Y') {
            break;
        }

        // 모든 책이 대여 불가일 때 에러메세지를 띄웁니다.
        if (searchTmpBookList->next == NULL) {
            printf("모든 책이 대여 불가합니다.");
            return;
        }
        searchTmpBookList = searchTmpBookList->next;
    }

    // 모든 책이 대여 불가일 때 에러메세지를 띄웁니다.
    if (searchTmpBookList->book.isBorrowable == 'N') {
        printf("모든 책이 대여 불가합니다.");
        return;
    }

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

    bookNode *willLendBook = findBookNodeByBookId(bookList, bookId);
    if (willLendBook == NULL) {
        printf("일치하는 id를 가진 책이 없습니다.\n");
        return;
    }

    if (willLendBook->book.isBorrowable == 'N') {
        printf("이 책은 대여할 수 없습니다.\n");
        return;
    }

    printf("이 도서를 대여합니까? (Y or N)");
    char c = getchar();
    putchar(getchar());
    if (c == 'Y' || c == 'y') {
        // 책을 대여했다면 다른 사람은 그 책을 대여할 수 없습니다.
        // 대여해준 뒤 대여 정보를 대여 목록에 추가하고, 그 결과를 파일에 반영합니다.
        willLendBook -> book.isBorrowable = 'N';
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

    if (findBorrowResults == NULL) {
        printf("\n대여한 책이 없습니다.\n\n");
        return;
    }

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
        // 대여 목록에서 반납된 책을 삭제하고 그 결과를 borrow 파일에 반영합니다.
        removeBorrow(borrowList, indexOfBorrowNode(borrowList, *findBorrowByBookIdResult));
        overwriteBorrowFile(*borrowList);

        // 책 정보에서 대여 가능 정보를 대여가능으로 바꾸고 그 결과를 book 파일에 반영합니다.
        findBookByBookIdResult->book.isBorrowable = 'Y';
        
        overwriteBookFile(*bookList);
        printf("도서가 반납되었습니다.\n");
    } else {
        printf("도서반납이 취소되었습니다.\n");
    }
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
            case 1: // 이름
                printf("이름: ");
                scanf("[^\n]", name);
                getchar();
                findResult = findClientNodeByName(clientList, name);
                if (findResult == NULL)
                    printf("해당되는 사용자가 존재하지 않습니다.\n");
                else
                    printClient(findResult->client);
                break;

            case 2: // 학번
                printf("학번: ");
                scanf("%d", &studentId);
                getchar();
                findResult = findClientNodeById(clientList, studentId);
                if (findResult == NULL)
                    printf("해당되는 사용자가 존재하지 않습니다.\n");
                else
                    printClient(findResult->client);
                break;

            case 3: // 전체 검색
                printClientList(*clientList);
                break;

            case 4: // 이전 메뉴
                return 1;
        }
    }
}