//
//  file.c
//  Library
//
//  Created by 이동규 on 2016. 11. 9..
//  Copyright © 2016년 이동규. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "file.h"


void loadFile(client *clients, book *books, borrow *borrows) {
    // 파일 이름
    char clientFileName[] = "./client.txt";
    char bookFileName[] = "./book.txt";
    char borrowFileName[] = "./borrow.txt";
    
    // 파일 읽기 모드로 열기
    FILE *clientFile = fopen(clientFileName, "r");
    FILE *bookFile = fopen(bookFileName, "r");
    FILE *borrowFile = fopen(borrowFileName, "r");
    
    if (clientFile == NULL) {
        printf("client 파일이 없습니다.\n");
        return;
    }
    
    if (bookFile == NULL) {
        printf("book 파일이 없습니다.\n");
        return;
    }
    
    if (borrowFile == NULL) {
        printf("borrow 파일이 없습니다.\n");
        return;
    }
    
    // client 파일 데이터 추출 기본 단계
    int i = 0;
    
    // client 파일 데이터 추출
    while (!feof(clientFile)) {
        clients = calloc(1, sizeof(client));
        fscanf(clientFile, "%d||%[^|]||%[^|]||%[^|]||%s\n", &(clients[i].studentId), clients[i].password, clients[i].name, clients[i].address, clients[i].phone);
        i++;
    }
    
    fclose(clientFile);
    fclose(bookFile);
    fclose(borrowFile);
}
