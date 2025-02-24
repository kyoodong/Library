//
//  list.c
//  Library
//
//  Created by 이동규 on 2016. 11. 9..
//  Copyright © 2016년 이동규. All rights reserved.
//

#include "list.h"
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
            addedClient -> next = clientList;
        }
    }
    
    else {
        int length = clientLength(*clientList);
        if (length < at) {
            printf("%d는 List크기(%d)보다 큽니다.\n", at, length);
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
    
    if (at == index++) {
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


int isEmptyClient(client client) {
    return client.studentId == 0 && !strcmp(client.phone, "") && !strcmp(client.address, "") && !strcmp(client.name, "") && !strcmp(client.password, "");
}


///////////////////////////// 클라이언트 ////////////////////////////////////





///////////////////////////// 책 ////////////////////////////////////

int isEmptyBook(book book) {
    return book.bookId == 0 && book.isBorrowable == 0 && book.ISBN == 0 && !strcmp(book.authorName, "") && !strcmp(book.holdingInstitudtion, "") && !strcmp(book.name, "") && !strcmp(book.publisherName, "");
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
        bookNode* changedbookNode;
        
        // 밀려날 bookNode
        bookNode* pushedbookNode;
        
        changedbookNode = getBookNode(bookList, at - 1);
        pushedbookNode = getBookNode(changedbookNode, 1);
        
        changedbookNode -> next = addedBook;
        
        // at번째 노드가 마지막 노드가 아니라면
        if (pushedbookNode != NULL) {
            addedBook -> next = pushedbookNode;
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
    
    if (at == index++) {
        return bookList;
    }
    
    // at보다 길이가 짧을 때 0을 리턴
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
    strcpy(book.holdingInstitudtion, "");
    strcpy(book.publisherName, "");
    book.ISBN = 0;
    book.isBorrowable = 0;
    return book;
}


///////////////////////////// 책 ////////////////////////////////////




///////////////////////////// Borrow ////////////////////////////////////

int isEmptyBorrow(borrow borrow) {
    return borrow.studentId == 0 && borrow.studentId == 0 && borrow.borrowDateSec == 0 && borrow.returnDateSec == 0;
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
    borrow.borrowDateSec = 0;
    borrow.returnDateSec = 0;
    return borrow;
}


///////////////////////////// Borrow ////////////////////////////////////






