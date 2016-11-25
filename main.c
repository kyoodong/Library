#include "member.h"
#include "admin.h"

// 메뉴
int selectLibraryMenu();
void selectMemberMenu();
void selectAdminMenu();
void selectSearchBookMenu(void (*beforeMenu)(void));
void mainMenu();

void signUp();
void signIn();

clientNode clientList;
bookNode bookList;
borrowNode borrowList;
int myStudentId;

int main(void) {
    loadFile(&clientList, &bookList, &borrowList);

    mainMenu();
}

void mainMenu() {
    while (1) {
        switch (selectLibraryMenu()) {
            case 1: // 회원가입
                signUp();
                break;

            case 2: // 로그인
                signIn();
                break;

            case 3: // 프로그램 종료
                closeFile();
                exit(0);
        }
    }
}


// 회원가입
void signUp() {
    clientNode* node, tmpNode = clientList;
    node = calloc(1, sizeof(clientNode));
    int i;

    printf(">> 회원가입 <<\n");
    printf("학번, 비밀번호, 이름, 주소, 전화번호를 입력하세요.\n\n");
    printf("학번 : ");
    scanf("%d", &(node->client.studentId));
    getchar();

    // studentId 중복검사
    if (findClientNodeById(&clientList, node->client.studentId) != NULL) {
        printf("\nstudentId는 중복될 수 없습니다.\n\n");
        return;
    }

    printf("비밀번호: ");
    scanf("%[^\n]", node->client.password);
    getchar();
    printf("이름: ");
    scanf("%[^\n]", node->client.name);
    getchar();
    printf("주소: ");
    scanf("%[^\n]", node->client.address);
    getchar();
    printf("전화번호: ");
    scanf("%[^\n]", node->client.phone);
    putchar(getchar());

    // 정렬하기 위해 저장할 위치 찾기
    for (i = 0; !isEmptyClient(tmpNode.client); ++i) {
        if (tmpNode.client.studentId > node->client.studentId) {
            break;
        }
        if (tmpNode.next == NULL)
            break;
        tmpNode = *(tmpNode.next);
    }

    insertClient(&clientList, node, i);
    overwriteClientFile(clientList);

    printf("회원가입이 되셨습니다.\n\n");
}

// 로그인
void signIn() {
    char id[20], password[50];

    printf(">> 로그인 <<\n");
    printf("학번 : ");
    scanf("%[^\n]", id);
    getchar();

    myStudentId = atoi(id);
    printf("비밀번호 : ");
    scanf("%[^\n]", password);
    putchar(getchar());

    // 관리자 모드
    if (!strcmp(id, "admin") && !strcmp(password, "lib_admin7")) {
        printf("\n");
        while (1) {
            selectAdminMenu();
        }
    }

    clientNode list = clientList;
    while (!isEmptyClient(list.client)) {
        // 아이디와 비밀번호가 일치하는 회원이 있다면
        if (list.client.studentId == myStudentId && !strcmp(list.client.password, password)) {
            while (1)
                selectMemberMenu();
        } else if (list.client.studentId > myStudentId)
            break;
        list = *(list.next);
    }

    // 유저정보가 없음
    printf("아이디와 비밀번호가 일치하는 회원정보가 존재하지 않습니다\n\n");
}



// 메뉴
int selectLibraryMenu() {
    int menu;
    printf(">> 도서관 서비스 <<\n");
    printf("1.회원가입\n2.로그인\n3.프로그램 종료\n\n");

    printf("번호를 입력하세요: ");
    scanf("%d", &menu);
    putchar(getchar());
    return menu;
}

// 회원 메뉴
void selectMemberMenu() {
    int menu;
    while (1) {
        printf(">> 회원 메뉴 <<\n");
        printf("1.도서 검색\t\t\t2.내 대여 목록\n3.개인정보 수정\t\t\t4.회원 탈퇴\n5.로그아웃\t\t\t\t6.프로그램 종료\n");

        printf("\n번호를 선택하세요: ");
        scanf("%d", &menu);
        putchar(getchar());

        switch (menu) {
            case 1:
                selectSearchBookMenu(selectMemberMenu);
                return;

            case 2:
                loadMyBorrowList(&borrowList, myStudentId);
                break;

            case 3:
                modifyPersonalInfo(&clientList, myStudentId);
                break;

            case 4:
                // 탈퇴 성공 시
                if (leaveMember(&clientList, &borrowList, myStudentId)) {
                    mainMenu();
                    return;
                }
                break;

            case 5:
                mainMenu();
                return;

            case 6:
                closeFile();
                exit(0);
        }
    }
}

// 도서 검색 메뉴
void selectSearchBookMenu(void (*beforeMenu)(void)) {
    int menu;
    unsigned long isbn;
    char keyword[20];
    bookNode *findBookResults;

    while (1) {
        printf(">> 도서 검색 <<\n");
        printf("1.도서명 검색\t\t\t2.출판사 검색\n3.ISBN 검색\t\t\t4.저자명 검색\n5.전체 검색\t\t\t6.이전 메뉴\n");

        printf("\n번호를 입력하세요: ");
        scanf("%d", &menu);
        putchar(getchar());

        switch (menu) {
            case 1:
                printf("도서명을 입력하세요: ");
                scanf("%s", keyword);
                putchar(getchar());
                findBookResults = findBookNodeByBookName(&bookList, keyword);
                if (findBookResults == NULL)
                    printf("제목이 '%s'인 도서가 존재하지 않습니다.\n", keyword);
                else {
                    // TODO: 대여가능 여부: N(2/2)
                    printf(">> 검색 결과 <<\n");
                    printBookList(*findBookResults);
                }
                break;

            case 2:
                printf("출판사를 입력하세요: ");
                scanf("%s", keyword);
                getchar();
                findBookResults = findBookNodeByPublisherName(&bookList, keyword);
                if (findBookResults == NULL)
                    printf("ISBN이 '%lu'인 도서가 존재하지 않습니다.\n", isbn);
                else
                    printBookList(*findBookResults);
                break;

            case 3:
                printf("ISBN을 입력하세요: ");
                scanf("%lu", &isbn);
                getchar();
                findBookResults = findBookNodeByISBN(&bookList, isbn);
                if (findBookResults == NULL)
                    printf("출판사가 '%s'인 도서가 존재하지 않습니다.\n", keyword);
                else
                    printBookList(*findBookResults);
                break;

            case 4:
                printf("저자명을 입력하세요: ");
                scanf("%s", keyword);
                getchar();
                findBookResults = findBookNodeByAuthorName(&bookList, keyword);
                if (findBookResults == NULL)
                    printf("저자명이 '%s'인 도서가 존재하지 않습니다.\n", keyword);
                else
                    printBookList(*findBookResults);
                break;

            case 5:
                printBookList(bookList);
                break;

            case 6:
                beforeMenu();
                return;
        }
    }
}

// 관리자 메뉴
void selectAdminMenu() {
    int menu;
    while (1) {
        printf(">> 관리자 메뉴 <<\n");
        printf("1.도서 등록\t\t\t2.도서 삭제\n3.도서 대여\t\t\t4.도서 반납\n5.도서 검색\t\t\t6.회원 목록\n7.로그아웃\t\t\t\t8.프로그램 종료\n");
        printf("\n번호를 입력하세요: ");
        scanf("%d", &menu);
        putchar(getchar());


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

            case 5:
                selectSearchBookMenu(selectAdminMenu);
                return;

            case 6:
                if (loadMemberList(&clientList)) {
                    selectAdminMenu();
                    return;
                }
                break;

            case 7:
                mainMenu();
                return;

            case 8:
                closeFile();
                exit(0);
        }
    }
}
