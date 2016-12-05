//
//  member.c
//  Library
//
//  Created by 이동규 on 2016. 11. 14..
//  Copyright © 2016년 이동규. All rights reserved.
//

#include "member.h"

// 책 검색
void seachBook() {
    
}

// 내 대여 목록
void loadMyBorrowList(borrowNode *borrowList, int studentId) {
    borrowNode *findBorrowResult = findBorrowNodeByStudentId(borrowList, studentId);
    if (findBorrowResult == NULL) {
        printf("대여목록이 없습니다.\n\n");
        return;
    }

    printf(">> 내 대여 목록 <<\n");
    printBorrow(findBorrowResult->borrow);
}

// 개인정보 수정
void modifyPersonalInfo(clientNode *clientList, int studentId) {
    char password[20], address[20], phone[20];
    printf("비밀번호: ");
    scanf("%[^\n]", password);
    getchar();

    printf("주소: ");
    scanf("%[^\n]", address);
    getchar();

    printf("전화번호: ");
    scanf("%[^\n]", phone);
    putchar(getchar());

    clientNode *myInfo = findClientNodeById(clientList, studentId);
    strcpy(myInfo->client.password, password);
    strcpy(myInfo->client.address, address);
    strcpy(myInfo->client.phone, phone);

    overwriteClientFile(*clientList);
}

// 회원 탈퇴
int leaveMember(clientNode *clientList, borrowNode *borrowList, int studentId) {
    clientNode *myInfo = findClientNodeById(clientList, studentId);
    borrowNode *findBorrowResults = findBorrowNodeByStudentId(borrowList, studentId);

    // 대여 목록이 있을 때
    if (findBorrowResults != NULL) {
        printf("대여목록이 있으므로 회원탈퇴가 불가능합니다.\n");
        printBorrowList(*findBorrowResults);
        return 0;
    }
    removeClient(clientList, indexOfClientNode(clientList, *myInfo));
    overwriteClientFile(*clientList);
    return 1;
}