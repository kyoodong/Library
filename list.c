//
//  list.c
//  Library
//
//  Created by 이동규 on 2016. 11. 9..
//  Copyright © 2016년 이동규. All rights reserved.
//

#include "list.h"





///////////////////////////// 클라이언트 ////////////////////////////////////


// client List의 맨 뒤에 client를 하나 추가하는 함수
void addClient(clientNode *clientList, clientNode *addedClient) {
    // List의 첫 번째 요소라면
    if (clientList -> client.studentId == 0) {
        clientList -> client = addedClient -> client;
    } else {
        // TODO - 맨뒤에 추가하는거로 수정해야함
        while (clientList -> next != NULL) {
            clientList = clientList -> next;
        }
        
        clientList -> next = addedClient;
    }
}

// client List의 at번째 원소를 지우는 함수
void removeClient(clientNode *clientList, int at) {
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
    clientList -> client = initClient();
    clientList -> next = NULL;
}

// client List의 index 번째에 client를 하나 추가하는 함수
void insertClient(clientNode *clientList, clientNode *addedClient, int at) {
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
    return client.studentId == 0;
}


///////////////////////////// 클라이언트 ////////////////////////////////////





///////////////////////////// 책 ////////////////////////////////////

int isEmptyBook(book book) {
    return book.bookId == 0;
}


// book List의 맨 뒤에 book을 하나 추가하는 함수
void addBook(bookNode *bookList, bookNode *addedBook) {
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
    bookList -> book = initBook();
    bookList -> next = NULL;
}

// book List의 index 번째에 book를 하나 추가하는 함수
void insertBook(bookNode *bookList, bookNode *addedbook, int at) {
    if (at < 0) {
        printf("음수는 불가합니다.\n");
        return;
    }
    
    // 0번째에 추가 일 때
    if (at == 0) {
        // 추가될 리스트에 아무 값도 없다면
        if (isEmptyBook(bookList -> book)) {
            *bookList = *addedbook;
        } else {
            addedbook -> next = bookList;
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
        
        changedbookNode -> next = addedbook;
        
        // at번째 노드가 마지막 노드가 아니라면
        if (pushedbookNode != NULL) {
            addedbook -> next = pushedbookNode;
        }
    }
}

bookNode* getBookNode(bookNode* bookList, int at) {
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
    book.isBorrowable = 'Y';
    return book;
}


///////////////////////////// 책 ////////////////////////////////////






