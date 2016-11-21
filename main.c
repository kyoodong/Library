#include "member.h"
#include "admin.h"
#include "file.h"
#include <stdlib.h>

// 메뉴
int selectLibraryMenu();
void selectMemberMenu();
void selectAdminMenu();
void selectSearchBookMenu();

void signUp();
void signIn();

clientNode clientList;
bookNode bookList;
borrowNode borrowList;

int main(void) {
    loadFile(&clientList, &bookList, &borrowList);

    while (1) {
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
    }
    
    return 0;
}

// 회원가입
void signUp() {
    client newClient;
    
    printf("학번 : ");
    scanf("%d", &(newClient.studentId));
    getchar();

    // studentId 중복검사
    if (findClientNodeById(&clientList, newClient.studentId) != NULL) {
        printf("studentId는 중복될 수 없습니다.\n");
        return;
    }

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

    clientNode node;
    node.client = newClient;
    insertClient(&clientList, &node, 0);
    overwriteClientFile(clientList);
}

// 로그인
void signIn() {
    char id[20], password[50];
    int idInt;

    printf("로그인 명 : ");
    scanf("%[^\n]", id);
    getchar();

    // 관리자 모드
    if (!strcmp(id, "admin")) {
        while (1) {
            selectAdminMenu();
        }
        return;
    }

    idInt = atoi(id);
    printf("비밀번호 : ");
    scanf("%[^\n]", password);
    getchar();

    clientNode list = clientList;
    while (!isEmptyClient(list.client)) {
        // 아이디와 비밀번호가 일치하는 회원이 있다면
        if (list.client.studentId == idInt && !strcmp(list.client.password, password)) {
            selectMemberMenu();
            return;
        } else if (list.client.studentId < idInt)
            break;
        list = *(list.next);
    }

    // 유저정보가 없음
    printf("아이디와 비밀번호가 일치하는 회원정보가 존재하지 않습니다\n");
}



// 메뉴
int selectLibraryMenu() {
    int menu;
    printf(">> 도서관 서비스 <<\n");
    printf("1.회원가입\n2.로그인\n3.프로그램 종료\n");
    scanf("%d", &menu);
    getchar();
    return menu;
}

// 회원 메뉴
void selectMemberMenu() {
    int menu;
    printf(">> 도서관 서비스 <<\n");
    printf("1. 도서 검색\n2.내 대여 목록\n3.개인정보 수정\n4.회원 탈퇴\n5.로그아웃\n6.프로그램 종료\n");
    scanf("%d", &menu);
    getchar();

    switch (menu) {
        case 1:
            selectSearchBookMenu();
            break;
    }
}

// 도서 검색 메뉴
void selectSearchBookMenu() {
    int menu;
    printf(">> 도서 검색 <<\n");
    printf("1.도서명 검색\n2.출판사 검색\n3.ISBN 검색\n4.저자명 검색\n5.전체 검색\n6.이전 메뉴\n");
    scanf("%d", &menu);
    getchar();


}

// 관리자 메뉴
void selectAdminMenu() {
    int menu;
    printf(">> 관리자 메뉴 <<\n");
    printf("1.도서 등록\n2.도서 삭제\n3.도서 대여\n4.도서 반납\n5.도서 검색\n6.회원 목록\n7.로그아웃\n8.프로그램 종료\n");
    scanf("%d", &menu);
    getchar();

    while (1) {
        switch (menu) {
            case 1:
                registerNewBook(&bookList);
                break;

            case 2:
                deleteBook(&bookList);
                break;

            case 3:
                lendBook(&bookList, &borrowList, &clientList);
                break;

            case 4:
                returnBook(&clientList, &bookList, &borrowList);
                break;

            case 6:
                if (loadMemberList(&clientList)) {
                    selectAdminMenu();
                    return;
                }
                break;

            case 8:
                exit(0);
        }
    }
}
