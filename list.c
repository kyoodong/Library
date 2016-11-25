//
//  list.c
//  Library
//
//  Created by 이동규 on 2016. 11. 9..
//  Copyright © 2016년 이동규. All rights reserved.
//

#include "list.h"
#include "file.h"
#include <stdlib.h>



///////////////////////////// 클라이언트 ////////////////////////////////////


// client List의 맨 뒤에 client를 하나 추가하는 함수
void addClient(clientNode *clientList, clientNode *addedClient) {
    if (clientList == NULL) {
        printf("clientList는 NULL 일 수 없습니다.\n");
        return;
    } else if (addedClient == NULL) {
        printf("addedClient는 NULL 일 수 없습니다.\n");
        return;
    }
    
    // List의 첫 번째 요소라면
    if (isEmptyClient(clientList -> client)) {
        clientList -> client = addedClient -> client;
    } else {
        while (clientList -> next != NULL) {
            clientList = clientList -> next;
        }
        
        clientList -> next = addedClient;
    }
}

// client List의 at번째 원소를 지우는 함수
void removeClient(clientNode *clientList, int at) {
    if (clientList == NULL) {
        printf("clientList는 NULL 일 수 없습니다.\n");
        return;
    }
    
    if (at < 0) {
        printf("음수는 불가합니다.\n");
        return;
    }
    
    int length = clientLength(*clientList);
    if (length <= at) {
        printf("길이 %d인 리스트에서 %d번째 요소를 제거할 수 없습니다.\n", length, at);
        return;
    }
    
    if (at == 0) {
        // clientList에 값이 없거나 하나 뿐일 때
        if (length <= 1) {
            clientList -> client = initClient();
        } else {
            // Header를 다음 것으로 이동
            *clientList = *(clientList -> next);
        }
    } else {
        clientNode* beforeClientNode = getClientNode(clientList, at - 1);
        
        // 맨 마지막 원소를 제거한다면
        if (length == at + 1) {
            beforeClientNode -> next = NULL;
        } else {
            clientNode* nextClientNode = getClientNode(beforeClientNode, 2);
            beforeClientNode -> next = nextClientNode;
        }
    }
}

// client List를 비워버리는 함수
void clearClient(clientNode *clientList) {
    if (clientList == NULL) {
        printf("clientList는 NULL 일 수 없습니다.\n");
        return;
    }
    
    clientList -> client = initClient();
    clientList -> next = NULL;
}

// client List의 index 번째에 client를 하나 추가하는 함수
void insertClient(clientNode *clientList, clientNode *addedClient, int at) {
    if (clientList == NULL) {
        printf("clientList는 NULL 일 수 없습니다.\n");
        return;
    } else if (addedClient == NULL) {
        printf("clientList는 NULL 일 수 없습니다.\n");
        return;
    }
    
    if (at < 0) {
        printf("음수는 불가합니다.\n");
        return;
    }
    
    // 0번째에 추가 일 때
    if (at == 0) {
        // 추가될 리스트에 아무 값도 없다면
        if (isEmptyClient(clientList -> client)) {
            *clientList = *addedClient;
        } else {
            clientNode* tmpClientNode = (clientNode*) calloc(1, sizeof(clientNode));
            *tmpClientNode = *clientList;
            addedClient -> next = tmpClientNode;
            *clientList = *addedClient;
        }
    }
    
    else {
        int length = clientLength(*clientList);
        if (length < at) {
            printf("%d는 List크기(%d)보다 큽니다.\n", at, length);
            return;
        }
        
        
        // next값이 바뀔 clientNode
        clientNode* changedClientNode;
        
        // 밀려날 clientNode
        clientNode* pushedClientNode;
        
        changedClientNode = getClientNode(clientList, at - 1);
        pushedClientNode = getClientNode(changedClientNode, 1);
        
        changedClientNode -> next = addedClient;
        
        // at번째 노드가 마지막 노드가 아니라면
        if (pushedClientNode != NULL) {
            addedClient -> next = pushedClientNode;
        }
    }
}

int isEqualClient(client leftClient, client rightClient) {
    return leftClient.studentId == rightClient.studentId &&
           !strcmp(leftClient.address, rightClient.address) &&
           !strcmp(leftClient.password, rightClient.password) &&
           !strcmp(leftClient.name, rightClient.name) &&
           !strcmp(leftClient.phone, rightClient.phone);
}


// clientNode index 번호 찾기
int indexOfClientNode(clientNode* clientList, clientNode foundClientNode) {
    int count = 0;
    while (!isEmptyClient(clientList->client)) {
        if (isEqualClient(clientList->client, foundClientNode.client)) {
            return count;
        }
        clientList = clientList->next;
        count++;
    }
    return -1;
}


// at 번째 clientNode 추출
clientNode* getClientNode(clientNode* clientList, int at) {
    if (clientList == NULL) {
        printf("clientList는 NULL 일 수 없습니다.\n");
        return NULL;
    }
    int index = 0;
    
    while (clientList -> next != NULL) {
        // 원하는 index에 도달하면 1을 리턴하고 retClient에 client정보 assign
        if (at == index++) {
            return clientList;
        }
        
        if (clientList -> next == NULL) {
            break;
        }
        clientList = clientList -> next;
    }
    
    if (at == index) {
        return clientList;
    }
    
    // at보다 길이가 짧을 때 0을 리턴
    return NULL;
}

// client List의 길이를 구하는 함수
int clientLength(clientNode clientList) {
    int count = 1;
    
    while (clientList.next != NULL) {
        count++;
        if (clientList.next == NULL) {
            break;
        }
        clientList = *(clientList.next);
    }
    
    // 첫 번째 요소가 비었을 때는 길이 0
    if (count == 1 && isEmptyClient(clientList.client)) {
        return 0;
    }
    
    return count;
}


// name 으로 client 찾기
clientNode* findClientNodeByName(clientNode* list, char* name) {
    while (!isEmptyClient(list->client)) {
        if (!strcmp(list->client.name, name)) {
            return list;
        }

        if (list->next == NULL)
            break;
        list = list->next;
    }
    return NULL;
}


// studentId 로 client 찾기
clientNode* findClientNodeById(clientNode* list, int id) {
    while (!isEmptyClient(list->client)) {
        if (list->client.studentId == id) {
            return list;
        }

        if (list->next == NULL)
            break;
        list = list->next;
    }
    return NULL;
}


// ClientNode 생성
clientNode initClientNode() {
    clientNode node;
    node.client = initClient();
    node.next = NULL;
    return node;
}


client initClient() {
    client client;
    client.studentId = 0;
    strcpy(client.name, "");
    strcpy(client.password, "");
    strcpy(client.address, "");
    strcpy(client.phone, "");
    return client;
}


int isEmptyClient(client c) {
    return c.studentId == 0 && !strcmp(c.phone, "") && !strcmp(c.address, "") && !strcmp(c.name, "") && !strcmp(c.password, "");
}


///////////////////////////// 클라이언트 ////////////////////////////////////





///////////////////////////// 책 ////////////////////////////////////

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
    
    // List의 첫 번째 요소라면
    if (bookList -> book.bookId == 0) {
        bookList -> book = addedBook -> book;
    } else {
        // TODO - 맨뒤에 추가하는거로 수정해야함
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
    
    if (at == 0) {
        // bookList에 값이 없거나 하나 뿐일 때
        if (length <= 1) {
            bookList -> book = initBook();
        } else {
            // Header를 다음 것으로 이동
            *bookList = *(bookList -> next);
        }
    } else {
        bookNode* beforeBookNode = getBookNode(bookList, at - 1);
        
        // 맨 마지막 원소를 제거한다면
        if (length == at + 1) {
            beforeBookNode -> next = NULL;
        } else {
            bookNode* nextBookNode = getBookNode(beforeBookNode, 2);
            beforeBookNode -> next = nextBookNode;
        }
    }
}

// book List를 비워버리는 함수
void clearBook(bookNode *bookList) {
    if (bookList == NULL) {
        printf("bookList는 NULL 일 수 없습니다.\n");
        return;
    }
    
    bookList -> book = initBook();
    bookList -> next = NULL;
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
    
    // 0번째에 추가 일 때
    if (at == 0) {
        // 추가될 리스트에 아무 값도 없다면
        if (isEmptyBook(bookList -> book)) {
            *bookList = *addedBook;
        } else {
            addedBook -> next = bookList;
        }
    }
    
    else {
        int length = bookLength(*bookList);
        if (length < at) {
            printf("%d는 List크기(%d)보다 큽니다.\n", at, length);
        }
        
        
        // next값이 바뀔 bookNode
        bookNode* willChangeBookNode;
        
        // 밀려날 bookNode
        bookNode* willPushBookNode;
        
        willChangeBookNode = getBookNode(bookList, at - 1);
        willPushBookNode = getBookNode(willChangeBookNode, 1);
        
        willChangeBookNode -> next = addedBook;
        
        // at번째 노드가 마지막 노드가 아니라면
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


bookNode initBookNode() {
    bookNode node;
    node.book = initBook();
    node.next = NULL;
    return node;
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


///////////////////////////// 책 ////////////////////////////////////




///////////////////////////// Borrow ////////////////////////////////////

int isEmptyBorrow(borrow b) {
    return b.studentId == 0 && b.studentId == 0 && b.borrowDateSec == 0 && b.returnDateSec == 0;
}


// borrow List의 맨 뒤에 borrow을 하나 추가하는 함수
void addBorrow(borrowNode *borrowList, borrowNode *addedBorrow) {
    if (borrowList == NULL) {
        printf("borrowList는 NULL 일 수 없습니다.\n");
        return;
    } else if (addedBorrow == NULL) {
        printf("addedBorrow은 NULL 일 수 없습니다.\n");
        return;
    }
    
    // List의 첫 번째 요소라면
    if (borrowList -> borrow.studentId == 0) {
        borrowList -> borrow = addedBorrow -> borrow;
    } else {
        // TODO - 맨뒤에 추가하는거로 수정해야함
        while (borrowList -> next != NULL) {
            borrowList = borrowList -> next;
        }
        
        borrowList -> next = addedBorrow;
    }
}

// borrow List의 at번째 원소를 지우는 함수
void removeBorrow(borrowNode *borrowList, int at) {
    if (borrowList == NULL) {
        printf("borrowList는 NULL 일 수 없습니다.\n");
        return;
    }
    
    if (at < 0) {
        printf("음수는 불가합니다.\n");
        return;
    }
    
    int length = borrowLength(*borrowList);
    if (length <= at) {
        printf("길이 %d인 리스트에서 %d번째 요소를 제거할 수 없습니다.\n", length, at);
        return;
    }
    
    if (at == 0) {
        // borrowList에 값이 없거나 하나 뿐일 때
        if (length <= 1) {
            borrowList -> borrow = initBorrow();
        } else {
            // Header를 다음 것으로 이동
            *borrowList = *(borrowList -> next);
        }
    } else {
        borrowNode* beforeBorrowNode = getBorrowNode(borrowList, at - 1);
        
        // 맨 마지막 원소를 제거한다면
        if (length == at + 1) {
            beforeBorrowNode -> next = NULL;
        } else {
            borrowNode* nextborrowNode = getBorrowNode(beforeBorrowNode, 2);
            beforeBorrowNode -> next = nextborrowNode;
        }
    }
}

// borrow List를 비워버리는 함수
void clearBorrow(borrowNode *borrowList) {
    if (borrowList == NULL) {
        printf("borrowList는 NULL 일 수 없습니다.\n");
        return;
    }
    
    borrowList -> borrow = initBorrow();
    borrowList -> next = NULL;
}

// borrow List의 index 번째에 borrow를 하나 추가하는 함수
void insertBorrow(borrowNode *borrowList, borrowNode *addedBorrow, int at) {
    if (borrowList == NULL) {
        printf("borrowList는 NULL 일 수 없습니다.\n");
        return;
    }
    
    if (at < 0) {
        printf("음수는 불가합니다.\n");
        return;
    }
    
    // 0번째에 추가 일 때
    if (at == 0) {
        // 추가될 리스트에 아무 값도 없다면
        if (isEmptyBorrow(borrowList -> borrow)) {
            *borrowList = *addedBorrow;
        } else {
            addedBorrow -> next = borrowList;
        }
    }
    
    else {
        int length = borrowLength(*borrowList);
        if (length < at) {
            printf("%d는 List크기(%d)보다 큽니다.\n", at, length);
        }
        
        
        // next값이 바뀔 borrowNode
        borrowNode* changedBorrowNode;
        
        // 밀려날 borrowNode
        borrowNode* pushedBorrowNode;
        
        changedBorrowNode = getBorrowNode(borrowList, at - 1);
        pushedBorrowNode = getBorrowNode(changedBorrowNode, 1);
        
        changedBorrowNode -> next = addedBorrow;
        
        // at번째 노드가 마지막 노드가 아니라면
        if (pushedBorrowNode != NULL) {
            addedBorrow -> next = pushedBorrowNode;
        }
    }
}

borrowNode* getBorrowNode(borrowNode* borrowList, int at) {
    if (borrowList == NULL) {
        printf("borrowList는 NULL 일 수 없습니다.\n");
        return NULL;
    }
    
    int index = 0;
    
    while (borrowList -> next != NULL) {
        // 원하는 index에 도달하면 1을 리턴하고 retborrow에 borrow정보 assign
        if (at == index++) {
            return borrowList;
        }
        
        if (borrowList -> next == NULL) {
            break;
        }
        borrowList = borrowList -> next;
    }
    
    if (at == index++) {
        return borrowList;
    }
    
    // at보다 길이가 짧을 때 0을 리턴
    return NULL;
}

// borrow List의 길이를 구하는 함수
int borrowLength(borrowNode borrowList) {
    int count = 1;
    
    while (borrowList.next != NULL) {
        count++;
        if (borrowList.next == NULL) {
            break;
        }
        borrowList = *(borrowList.next);
    }
    
    // 첫 번째 요소가 비었을 때는 길이 0
    if (count == 1 && isEmptyBorrow(borrowList.borrow)) {
        return 0;
    }
    
    return count;
}


borrowNode initBorrowNode() {
    borrowNode node;
    node.borrow = initBorrow();
    node.next = NULL;
    return node;
}


borrow initBorrow() {
    borrow borrow;
    borrow.studentId = 0;
    borrow.studentId = 0;

    time_t t = time(NULL);
    time_t ct = t + 60 * 60 * 24 * 30;
    struct tm *timer = localtime(&ct);

    // 일요일
    if (timer -> tm_wday == 0) {
        ct += 60 * 60 * 24;
    }

    borrow.borrowDateSec = t;
    borrow.returnDateSec = ct;
    return borrow;
}


// studentId 으로 BorrowNode 찾기
borrowNode* findBorrowNodeByStudentId(borrowNode* borrowList, int studentId) {
    borrowNode *rtnBorrowList = calloc(1, sizeof(borrowNode));
    while (!isEmptyBorrow(borrowList->borrow)) {
        if (borrowList->borrow.studentId == studentId) {
            borrowNode *tmpBorrow = calloc(1, sizeof(borrowNode));
            tmpBorrow->borrow = borrowList->borrow;
            addBorrow(rtnBorrowList, tmpBorrow);
        }
        if (borrowList->next == NULL) {
            break;
        }
        borrowList = borrowList->next;
    }

    if (isEmptyBorrow(rtnBorrowList->borrow))
        return NULL;
    return rtnBorrowList;
}


// bookId 로 BorrowNode 찾기
borrowNode* findBorrowNodeByBookId(borrowNode* borrowList, int bookId) {
    while (!isEmptyBorrow(borrowList->borrow)) {
        if (borrowList->borrow.bookId == bookId) {
            return borrowList;
        }
        if (borrowList->next == NULL) {
            break;
        }
        borrowList = borrowList->next;
    }

    if (borrowList->borrow.bookId == bookId)
        return borrowList;
    return NULL;
}



int isEqualBorrow(borrow leftBorrow, borrow rightBorrow) {
    return leftBorrow.bookId == rightBorrow.bookId &&
           leftBorrow.studentId == rightBorrow.studentId &&
           leftBorrow.borrowDateSec == rightBorrow.borrowDateSec &&
           leftBorrow.returnDateSec == rightBorrow.returnDateSec;
}


// borrowNode index 번호 찾기
int indexOfBorrowNode(borrowNode* borrowList, borrowNode foundBorrowNode) {
    int count = 0;
    while (!isEmptyBorrow(borrowList->borrow)) {
        if (isEqualBorrow(borrowList->borrow, foundBorrowNode.borrow)) {
            return count;
        }
        borrowList = borrowList->next;
        count++;
    }
    return -1;
}


///////////////////////////// Borrow ////////////////////////////////////






