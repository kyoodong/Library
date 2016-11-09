//
//  list.c
//  Library
//
//  Created by 이동규 on 2016. 11. 9..
//  Copyright © 2016년 이동규. All rights reserved.
//

#include "list.h"


// client List의 맨 뒤에 client를 하나 추가하는 함수
void addClient(clientNode *clientList, clientNode *addedClient) {
    // List의 첫 번째 요소라면
    if (clientList -> client.studentId == 0) {
        clientList -> client = addedClient -> client;
    } else {
        // TODO - 맨뒤에 추가하는거로 수정해야함
        clientList -> next = addedClient;
    }
}

// client List의 index 번째에 client를 하나 추가하는 함수
void insertClient(clientNode *clientList, clientNode *addedClient, int at) {
    printf("66\n");
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
