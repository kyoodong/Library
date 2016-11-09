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
        clientList -> next = addedClient;
    }
}

// client List의 길이를 구하는 함수
int clientLength(clientNode clientList) {
    int count = 0;
    while (clientList.client.studentId != 0) {
        count++;
        if (clientList.next == NULL) {
            break;
        }
        clientList = *(clientList.next);
    }
    return count;
}
