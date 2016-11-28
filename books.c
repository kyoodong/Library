// 주로 book List와 book File을 관리하는 파일입니다.

#include "books.h"

FILE *bookFile;

// 파일 불러오기
void loadBookFile(bookNode *books) {
    // 파일 읽기 모드로 열기
    bookFile = fopen(BOOK_FILE_PATH, "r+");

    if (bookFile == NULL) {
        printf("book 파일이 없습니다.\n");
        return;
    }

    // book 파일에서 데이터를 추출하여 books 에 저장합니다.
    while (!feof(bookFile)) {
        bookNode* node = readBookFileLine(bookFile);
        addBook(books, node);
    }
    fflush(bookFile);
}


// book 파일을 한 줄 읽습니다.
bookNode* readBookFileLine(FILE* bookFile) {
    bookNode* node = (bookNode *) calloc(1, sizeof(bookNode));
    fscanf(bookFile, "%d||%[^|]||%[^|]||%[^|]||%ld||%[^|]||%c\n", &(node -> book.bookId), node -> book.name, node -> book.publisherName, node -> book.authorName, &(node -> book.ISBN), node -> book.holdingInstitution, &(node -> book.isBorrowable));
    return node;
}



// bookFile 을 bookList 의 정보로 덮어 씁니다.
void overwriteBookFile(bookNode bookList) {
    rewind(bookFile);

    while (!isEmptyBook(bookList.book)) {
        fprintf(bookFile, "%d||%s||%s||%s||%lu||%s||%c\n",
                bookList.book.bookId,                         // 도서 번호
                bookList.book.name,                           // 책 이름
                bookList.book.publisherName,                  // 출판사 이름
                bookList.book.authorName,                     // 저자 이름
                bookList.book.ISBN,                           // ISBN
                bookList.book.holdingInstitution,             // 소장처
                bookList.book.isBorrowable                    // 대여 가능 여부
        );
        if (bookList.next == NULL)
            break;

        bookList = *(bookList.next);
    }
    fflush(bookFile);
}


int isEmptyBook(book checkingBook) {
    return checkingBook.bookId == 0 && checkingBook.isBorrowable == 'Y' && checkingBook.ISBN == 0 && !strcmp(checkingBook.authorName, "") && !strcmp(checkingBook.holdingInstitution, "") && !strcmp(checkingBook.name, "") && !strcmp(checkingBook.publisherName, "");
}


// book List의 맨 뒤에 book을 하나 추가하는 함수
void addBook(bookNode *bookList, bookNode *addedBook) {
    if (bookList == NULL) {
        printf("bookList는 NULL 일 수 없습니다.\n");
        return;
    } else if (addedBook == NULL) {
        printf("addedBook은 NULL 일 수 없습니다.\n");
        return;
    }

    // List의 첫 번째 요소라면 bookList 헤더에 직접 데이터를 넣습니다.
    if (bookList -> book.bookId == 0) {
        bookList -> book = addedBook -> book;
    } else {
        // bookList 의 맨 마지막에 찾아가서 book을 추가합니다
        while (bookList -> next != NULL) {
            bookList = bookList -> next;
        }

        bookList -> next = addedBook;
    }
}

// book List의 at번째 원소를 지우는 함수
void removeBook(bookNode *bookList, int at) {
    if (bookList == NULL) {
        printf("bookList는 NULL 일 수 없습니다.\n");
        return;
    }

    if (at < 0) {
        printf("음수는 불가합니다.\n");
        return;
    }

    int length = bookLength(*bookList);
    if (length <= at) {
        printf("길이 %d인 리스트에서 %d번째 요소를 제거할 수 없습니다.\n", length, at);
        return;
    }

    // 0번째 요소를 지우는 것은 리스트의 헤더를 지우는 것과 같습니다.
    if (at == 0) {
        // 리스트 크기가 1이하 라면 Header의 값 만을 초기화 시킵니다.
        if (length <= 1) {
            bookList->book = initBook();
        }

        // 리스트 크기가 1보다 크다면 Header의 위치를 한 칸 옮겨줍니다. 리스트의 헤더가 NULL이 되면 안되기 때문입니다.
        else {
            bookNode *header = bookList;
            *bookList = *(bookList -> next);
            free(header);
        }
    }

    // 헤더가 아닌 요소를 제거한다면 이전 노드의 next를 삭제할 요소의 next로 바꿔줍니다.
    else {
        bookNode* beforeBookNode = getBookNode(bookList, at - 1);

        // 맨 마지막 원소를 제거한다면
        if (length == at + 1) {
            free(beforeBookNode->next);
            beforeBookNode -> next = NULL;
        } else {
            bookNode* willRemoveBookNode = getBookNode(beforeBookNode, 1);
            free(willRemoveBookNode);
            bookNode* nextBookNode = getBookNode(beforeBookNode, 2);
            beforeBookNode -> next = nextBookNode;
        }
    }
}

// book List의 index 번째에 book를 하나 추가하는 함수
void insertBook(bookNode *bookList, bookNode *addedBook, int at) {
    if (bookList == NULL) {
        printf("bookList는 NULL 일 수 없습니다.\n");
        return;
    } else if (addedBook == NULL) {
        printf("addedBook은 NULL 일 수 없습니다.\n");
        return;
    }

    if (at < 0) {
        printf("음수는 불가합니다.\n");
        return;
    }

    // 0번째에 추가하는 것은 Header를 바꾸는 것과 동일합니다.
    if (at == 0) {
        // 리스트에 아무 값도 없다면 Header 자체에 값을 넣어줍니다.
        if (isEmptyBook(bookList -> book)) {
            *bookList = *addedBook;
        }

        // 리스트에 어떠한 값이라도 들어있다면 Header를 재정의 하고 next 값으로 이전 Header를 넣어줍니다.
        // 헤더가 바뀌더라도 이전의 리스트는 유지되어야 하기 때문입니다.
        else {
            addedBook -> next = bookList;
        }
    }

        // 0번째가 아닌 원소에 추가하는 것이라면 at - 1번째 원소의 next를 추가될 원소를 가리키게 하고,
        // 추가될 원소의 next는 at번째 원소를 카리킵니다.
    else {
        int length = bookLength(*bookList);
        if (length < at) {
            printf("%d는 List크기(%d)보다 큽니다.\n", at, length);
        }


        bookNode* willChangeBookNode;
        bookNode* willPushBookNode;

        willChangeBookNode = getBookNode(bookList, at - 1);
        willPushBookNode = getBookNode(willChangeBookNode, 1);
        willChangeBookNode -> next = addedBook;

        if (willPushBookNode != NULL) {
            addedBook -> next = willPushBookNode;
        }
    }
}

bookNode* getBookNode(bookNode* bookList, int at) {
    if (bookList == NULL) {
        printf("bookList는 NULL 일 수 없습니다.\n");
        return NULL;
    }

    int index = 0;

    while (bookList -> next != NULL) {
        // 원하는 index에 도달하면 1을 리턴하고 retbook에 book정보 assign
        if (at == index++) {
            return bookList;
        }

        if (bookList -> next == NULL) {
            break;
        }
        bookList = bookList -> next;
    }

    if (at == index) {
        return bookList;
    }

    // at보다 길이가 짧을 때 0을 리턴
    return NULL;
}


// ISBN 으로 BookNode 찾기
bookNode* findBookNodeByISBN(bookNode* bookList, unsigned long isbn) {
    bookNode *hasIsbnBookList = calloc(1, sizeof(bookNode));
    hasIsbnBookList->book = initBook();

    while (!isEmptyBook(bookList->book)) {
        // ISBN 발견 시 return
        if (bookList->book.ISBN == isbn) {
            bookNode *newBook = calloc(1, sizeof(bookNode));
            newBook -> book = bookList->book;
            addBook(hasIsbnBookList, newBook);
        }
        if (bookList->next == NULL) {
            break;
        }
        bookList = bookList->next;
    }

    if (isEmptyBook(hasIsbnBookList -> book))
        return NULL;

    return hasIsbnBookList;
}


// 도서명으로 BookNode 찾기
bookNode* findBookNodeByBookName(bookNode* bookList, char* bookName) {
    bookNode *hasIsbnBookList = calloc(1, sizeof(bookNode));

    printf("%d\n", bookLength(*bookList));
    while (!isEmptyBook(bookList->book)) {
        // ISBN 발견 시 return
        if (!strcmp(bookList->book.name, bookName)) {
            bookNode *newBook = calloc(1, sizeof(bookNode));
            newBook -> book = bookList->book;
            addBook(hasIsbnBookList, newBook);
        }
        if (bookList->next == NULL) {
            break;
        }
        bookList = bookList->next;
    }

    if (isEmptyBook(hasIsbnBookList -> book))
        return NULL;

    return hasIsbnBookList;
}


// 출판사로 BookNode 찾기
bookNode* findBookNodeByPublisherName(bookNode* bookList, char* publisherName) {
    bookNode *hasIsbnBookList = calloc(1, sizeof(bookNode));

    while (!isEmptyBook(bookList->book)) {
        // ISBN 발견 시 return
        if (!strcmp(bookList->book.publisherName, publisherName)) {
            bookNode *newBook = calloc(1, sizeof(bookNode));
            newBook -> book = bookList->book;
            addBook(hasIsbnBookList, newBook);
        }
        if (bookList->next == NULL) {
            break;
        }
        bookList = bookList->next;
    }

    if (isEmptyBook(hasIsbnBookList -> book))
        return NULL;

    return hasIsbnBookList;
}


// 저자명으로 BookNode 찾기
bookNode* findBookNodeByAuthorName(bookNode* bookList, char* authorName) {
    bookNode *hasIsbnBookList = calloc(1, sizeof(bookNode));

    while (!isEmptyBook(bookList->book)) {
        // ISBN 발견 시 return
        if (!strcmp(bookList->book.authorName, authorName)) {
            bookNode *newBook = calloc(1, sizeof(bookNode));
            newBook -> book = bookList->book;
            addBook(hasIsbnBookList, newBook);
        }
        if (bookList->next == NULL) {
            break;
        }
        bookList = bookList->next;
    }

    if (isEmptyBook(hasIsbnBookList -> book))
        return NULL;

    return hasIsbnBookList;
}


int isEqualBook(book leftBook, book rightBook) {
    return leftBook.bookId == rightBook.bookId &&
           leftBook.isBorrowable == rightBook.isBorrowable &&
           !strcmp(leftBook.holdingInstitution, rightBook.holdingInstitution) &&
           !strcmp(leftBook.authorName, rightBook.authorName) &&
           !strcmp(leftBook.name, rightBook.name) &&
           !strcmp(leftBook.publisherName, rightBook.publisherName) &&
           leftBook.ISBN == rightBook.ISBN;
}



// bookNode index 번호 찾기
int indexOfBookNode(bookNode* bookList, bookNode foundBookNode) {
    int count = 0;
    while (!isEmptyBook(bookList->book)) {
        if (isEqualBook(bookList->book, foundBookNode.book)) {
            return count;
        }
        bookList = bookList->next;
        count++;
    }
    return -1;
}


// bookId 으로 BookNode 찾기
bookNode* findBookNodeByBookId(bookNode* bookList, int bookId) {
    while (!isEmptyBook(bookList->book)) {
        // ISBN 발견 시 return
        if (bookList->book.bookId == bookId) {
            return bookList;
        }
        if (bookList->next == NULL) {
            break;
        }
        bookList = bookList->next;
    }

    return NULL;
}


// book List의 길이를 구하는 함수
int bookLength(bookNode bookList) {
    int count = 1;

    while (bookList.next != NULL) {
        count++;
        if (bookList.next == NULL) {
            break;
        }
        bookList = *(bookList.next);
    }

    // 첫 번째 요소가 비었을 때는 길이 0
    if (count == 1 && isEmptyBook(bookList.book)) {
        return 0;
    }

    return count;
}


book initBook() {
    book book;
    book.bookId = 0;
    strcpy(book.name, "");
    strcpy(book.authorName, "");
    strcpy(book.holdingInstitution, "");
    strcpy(book.publisherName, "");
    book.ISBN = 0;
    book.isBorrowable = 'Y';
    return book;
}


// book의 정보를 출력합니다.
// 동일한 책이 여러권 있을 때는 묶음 출력을 하기 위해 bookNode 의 형태로 책 정보를 받습니다.
// bookNum: 책의 총 권 수
// borrowableBookNum: 빌릴 수 있는 책의 총 권 수
// mode: 책 삭제 모드인지, 대여 모드인지 구분하는 변수
void printBook(bookNode bookList, int bookNum, int borrowableBookNum, int mode) {
    int i;
    char isBorrowable;

    // ISBN 이 같은 여러권의 책을 묶음 출력하기 위함입니다. 반복문을 돌더라도 bookList 의 Header 정보를 보존시켜야하기 때문입니다.
    bookNode* tmpBook = &bookList;

    printf("도서번호: ");

    // ISBN 이 같은 책들의 bookId와 대여 가능 여부를 출력합니다.
    for (i = 0; i < bookNum; ++i) {
        printf("%d(삭제 가능 여부: %c), ", tmpBook->book.bookId, tmpBook->book.isBorrowable);
        tmpBook = getBookNode(tmpBook, 1);
    }
    printf("\b\b\n");
    printf("도서명: %s\n", bookList.book.name);
    printf("출판사: %s\n", bookList.book.publisherName);
    printf("저자명: %s\n", bookList.book.authorName);
    printf("ISBN: %lu\n", bookList.book.ISBN);
    printf("소장처: %s\n", bookList.book.holdingInstitution);

    // 대여 가능한 책이 단 한권이라도 존재한다면 그 책은 대여할 수 있다고 출력합니다.
    if (borrowableBookNum)
        isBorrowable = 'Y';
    else
        isBorrowable = 'N';
    if (mode == DELETE)
        printf("삭제 가능 여부: %c(%d/%d)\n", isBorrowable, borrowableBookNum, bookNum);
    else
        printf("대여 가능 여부: %c(%d/%d)\n", isBorrowable, borrowableBookNum, bookNum);

    printf("** Y는 대여가능, N은 대여불가를 의미\n");
    printf("** (x/y) : (대여할 수 있는 총 권수 / 보유하고 있는 총 권수)\n\n");
}

void printBookList(bookNode printingBook, int mode) {
    int bookNum = 0, borrowableBookNum = 0;
    bookNode tmpBook;

    printf("\n\n>> 검색 결과 <<\n");

    // 모든 책을 출력
    while (!isEmptyBook(printingBook.book)) {
        bookNum = 1;
        if (printingBook.book.isBorrowable == 'Y')
            borrowableBookNum = 1;
        else borrowableBookNum = 0;

        // 같은 책은 묶어서 출력하기 위해 반복문을 또 돌아야 합니다.
        // 반복문을 돌더라도 printingBook 의 Header 값을 보존시키기 위함입니다.
        tmpBook = printingBook;

        // 같은 책은 묶어서 출력하기 위해 ISBN 이 같은 책의 수를 구합니다. 책의 수 만큼 반복문을 돌며 묶음 출력하기 위함 입니다.
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


void closeBookFile() {
    fclose(bookFile);
}