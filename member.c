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
void loadMyBorrowList() {
    
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
    getchar();

    clientNode *myInfo = findClientNodeById(clientList, studentId);
    strcpy(myInfo->client.password, password);
    strcpy(myInfo->client.address, address);
    strcpy(myInfo->client.phone, phone);

    overwriteClientFile(*clientList);
}

// 회원 탈퇴
void leaveMember() {
    
}

// 책 제목으로 검색
void findBookByTitle() {
    
}

// 출판사로 검색
void findBookByPublisher() {
    
}

// ISBN으로 검색
void findBookByISBN() {
    
}

// 저자명으로 검색
void findBookByWriter() {
    
}

// 전체 색
void findAllBook() {
    
}
