#include "member.h"
#include "admin.h"
#include <stdlib.h>

// 메뉴
int selectLibraryMenu();
int selectMemberMenu();

void signUp();
void signIn();

int main(void) {
    clientNode *clientList = calloc(1, sizeof(clientNode));
    bookNode *bookList = calloc(1, sizeof(bookNode));
    borrowNode *borrowList = calloc(1, sizeof(borrowNode));
    loadFile(clientList, bookList, borrowList);
    
    printf("%s\n", clientList -> client.name);
    
    switch (selectLibraryMenu()) {
        case 1: // 회원가입
            signUp();
            break;
            
        case 2: // 로그인
            signIn();
            break;
            
        case 3: // 프로그램 종료
            return 0;
    }
    
    return 0;
}

// 회원가입
void signUp() {
    client newClient;
    
    printf("학번 : ");
    scanf("%d", &(newClient.studentId));
    getchar();
    printf("비밀번호 : ");
    scanf("%[^\n]", newClient.password);
    getchar();
    printf("이름 : ");
    scanf("%[^\n]", newClient.name);
    getchar();
    printf("주소 : ");
    scanf("%[^\n]", newClient.address);
    getchar();
    printf("전화번호 : ");
    scanf("%[^\n]", newClient.phone);
    getchar();
    
    
}

// 로그인
void signIn() {
    
}



// 메뉴
int selectLibraryMenu() {
    int menu;
    printf(">> 도서관 서비스 <<\n");
    printf("1. 회원가입\n2.로그인\n3.프로그램 종료\n");
    scanf("%d", &menu);
    return menu;
}

// 회원 메뉴
int selectMemberMenu() {
    int menu;
    printf(">> 도서관 서비스 <<\n");
    printf("1. 도서 검색\n2.내 대여 목록\n3.개인정보 수정\n4.회원 탈퇴\n5.로그아웃\n6.프로그램 종료\n");
    scanf("%d", &menu);
    return menu;
}

// 도서 검색 메뉴
int selectSearchBookMenu() {
    int menu;
    printf(">> 도서 검색 <<\n");
    printf("1. 도서명 검색\n2.출판사 검색\n3.ISBN 검색\n4.저자명 검색\n5.전체 검색\n6.이전 메뉴\n");
    scanf("%d", &menu);
    return menu;
}

// 관리자 메뉴
int selectAdminMenu() {
    int menu;
    printf(">> 관리자 메뉴 <<\n");
    printf("1. 도서 등록\n2.도서 삭제\n3.도서 대여\n4.도서 반납\n5.도서 검색\n6.회원 목록\n7.로그아웃\n8.프로그램 종료\n");
    scanf("%d", &menu);
    return menu;
}
