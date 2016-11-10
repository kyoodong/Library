#include "list.h"
#include <stdlib.h>

int main(void) {
    clientNode *clientList = calloc(1, sizeof(clientNode)), a, b;
    bookNode *bookList = calloc(1, sizeof(bookNode));
    borrowNode *borrowList = calloc(1, sizeof(borrowNode));
    loadFile(clientList, bookList, borrowList);
    return 0;
}
