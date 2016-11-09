#include "list.h"

int main(void) {
    // 파일 load
    client *clients;
    book *books;
    borrow *borrows;
    loadFile(clients, books, borrows);
    
    clientNode node;
    clientNode tmp;
    client c;
    
    c.studentId = 20162489;
    strcpy(c.name, "이동규");
    strcpy(c.password, "1234");
    strcpy(c.phone, "010-3367-7355");
    strcpy(c.address, "서울");
    tmp.client = c;
    printf("length %d\n", clientLength(node));
    addClient(&node, &tmp);
    printf("length %d\n", clientLength(node));
    return 0;
}




