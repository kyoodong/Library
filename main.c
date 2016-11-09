#include "list.h"

int main(void) {
    // 파일 load
    client *clients;
    book *books;
    borrow *borrows;
    loadFile(clients, books, borrows);
    
    clientNode node = initClientNode();
    clientNode tmp = initClientNode(), tmp2 = initClientNode(), tmp3 = initClientNode();
    client c;
    
    c.studentId = 20162489;
    strcpy(c.name, "이동규");
    strcpy(c.password, "1234");
    strcpy(c.phone, "010-3367-7355");
    strcpy(c.address, "서울");
    tmp.client = c;
    c.studentId = 20157894;
    tmp2.client = c;
    printf("length %d\n", clientLength(node));
    addClient(&node, &tmp);
    printf("length %d\n", clientLength(node));
    insertClient(&node, &tmp2, 1);
    insertClient(&node, &tmp, 1);
    addClient(&node, &tmp3);
    printf("length %d\n", clientLength(node));
    
    printf("\n\n\n\n");
    for (int i = 0; i < clientLength(node); i++) {
        clientNode* tmpClient = getClientNode(&node, i);
        printf("%d\n", tmpClient -> client.studentId);
    }
    
    
    removeClient(&node, 3);
    
    printf("\n\n\n\n");
    for (int i = 0; i < clientLength(node); i++) {
        clientNode* tmpClient = getClientNode(&node, i);
        printf("%d\n", tmpClient -> client.studentId);
    }
    
    return 0;
}




