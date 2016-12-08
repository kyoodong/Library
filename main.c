// main 파일 입니다
// 주로 메뉴 출력 및 메뉴 선택을 담당합니다.

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
void closeAllFile();

clientNode clientList;
bookNode bookList;
borrowNode borrowList;
int myStudentId;


int main(void) {
    loadClientFile(&clientList);
    loadBookFile(&bookList);
    loadBorrowFile(&borrowList);

    mainMenu();
}


// 프로그램이 처음 실행되었을 때 나타나는 메뉴입니다.
void mainMenu() {
    while (1) {
        // 도서관 메뉴를 선택할 수 있습니다.
        // 메뉴에는 회원가입, 로그인, 프로그램 종료가 있습니다.
        switch (selectLibraryMenu()) {
            case 1: // 회원가입
                signUp();
                break;

            case 2: // 로그인
                signIn();
                break;

            case 3: // 프로그램 종료
                closeAllFile();
                exit(0);
        }
    }
}


void signUp() {
    clientNode* signUpInputInfo, findClientPositionToSort = clientList;
    signUpInputInfo = calloc(1, sizeof(clientNode));
    int i;

    printf(">> 회원가입 <<\n");
    printf("학번, 비밀번호, 이름, 주소, 전화번호를 입력하세요.\n\n");
    printf("학번 : ");
    scanf("%d", &(signUpInputInfo->client.studentId));
    getchar();

    // 이미 가입 된 유저 중 동일한 studentId를 가진 유저가 있는지 확인합니다.
    if (findClientNodeById(&clientList, signUpInputInfo->client.studentId) != NULL) {
        printf("\nstudentId는 중복될 수 없습니다.\n\n");
        return;
    }

    printf("비밀번호: ");
    scanf("%[^\n]", signUpInputInfo->client.password);
    getchar();
    printf("이름: ");
    scanf("%[^\n]", signUpInputInfo->client.name);
    getchar();
    printf("주소: ");
    scanf("%[^\n]", signUpInputInfo->client.address);
    getchar();
    printf("전화번호: ");
    scanf("%[^\n]", signUpInputInfo->client.phone);
    putchar(getchar());

    // 학번을 기준으로 오름차순 정렬하기 위해 적당한 위치를 탐색합니다.
    for (i = 0; !isEmptyClient(findClientPositionToSort.client); ++i) {
        if (findClientPositionToSort.client.studentId > signUpInputInfo->client.studentId) {
            break;
        }
        if (findClientPositionToSort.next == NULL)
            break;
        findClientPositionToSort = *(findClientPositionToSort.next);
    }

    // i번째 위치가 새로 추가된 client 가 들어갈 위치 입니다
    insertClient(&clientList, signUpInputInfo, i);

    // list에 client를 추가하고, 이를 기반으로 client.txt 파일을 새로씁니다.
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

    // 관리자 모드로 로그인할 수 있습니다.
    if (!strcmp(id, "admin") && !strcmp(password, "lib_admin7")) {
        printf("\n");
        while (1) {
            selectAdminMenu();
        }
    }

    clientNode copiedClientList = clientList;

    // 아이디와 비밀번호가 일치하는 회원이 있는지 확인합니다.
    // 리스트를 모두 탐색하는 과정 중 allOfClientList = *(allOfClientList.next); 에서
    // global 변수 인 clientList의 Header 위치를 보존하기 위해 allOfClientList로 복사하여 탐색합니다.
    while (!isEmptyClient(copiedClientList.client)) {
        // 아이디와 비밀번호가 일치하는 회원을 발견한다면 멤버 메뉴를 보여줍니다.
        if (copiedClientList.client.studentId == myStudentId && !strcmp(copiedClientList.client.password, password)) {
            while (1)
                selectMemberMenu();
        } else if (copiedClientList.client.studentId > myStudentId)
            break;
        copiedClientList = *(copiedClientList.next);
    }

    // // 아이디와 비밀번호가 일치하는 회원을 발견하지 못했다면 에러 메세지를 출력합니다.
    printf("아이디와 비밀번호가 일치하는 회원정보가 존재하지 않습니다\n\n");
}



// 도서관 서비스 메뉴를 출력하고 메뉴 선택을 위한 입력을 받습니다.
// 도서관 메뉴에는 회원가입 로그인 프로그램 종료가 있습니다.
int selectLibraryMenu() {
    int menu;
    printf(">> 도서관 서비스 <<\n");
    printf("1.회원가입\n2.로그인\n3.프로그램 종료\n\n");

    printf("번호를 입력하세요: ");
    scanf("%d", &menu);
    putchar(getchar());
    return menu;
}

// 회원 메뉴를 출력하고, 선택을 위해 입력을 받습니다.
// 회원 메뉴에는 도서 검색, 내 대여 목룍, 개인정보 수정, 회원 탈퇴, 로그아웃, 프로그램 종료가 있습니다.
void selectMemberMenu() {
    int menu;
    while (1) {
        printf(">> 회원 메뉴 <<\n");
        printf("1.도서 검색\t\t\t2.내 대여 목록\n3.개인정보 수정\t\t\t4.회원 탈퇴\n5.로그아웃\t\t\t\t6.프로그램 종료\n");

        printf("\n번호를 선택하세요: ");
        scanf("%d", &menu);
        putchar(getchar());

        switch (menu) {
            case 1: // 도서 검색
                selectSearchBookMenu(selectMemberMenu);
                return;

            case 2: // 내 대여 목록
                loadMyBorrowList(&borrowList, myStudentId);
                break;

            case 3: // 개인정보 수정
                modifyPersonalInfo(&clientList, myStudentId);
                break;

            case 4: // 회원 탈퇴
                // 탈퇴 성공 시
                if (leaveMember(&clientList, &borrowList, myStudentId)) {
                    mainMenu();
                    return;
                }
                break;

            case 5: // 로그 아웃
                mainMenu();
                return;

            case 6: // 프로그램 종료
                closeAllFile();
                exit(0);
        }
    }
}

// 도서 검색 메뉴를 출력하고 메뉴 선택을 위한 입력을 받습니다.
// 도서 검색 메뉴에는 도서명 검색, 출판사 검색, ISBN 검색, 저자명 검색, 전체 검색, 이전 메뉴로 돌아가기 기능이 있습니다.
void selectSearchBookMenu(void (*beforeMenu)(void)) {
    int menu;
    unsigned long isbn;
    char keyword[20];
    bookNode *findResults;

    // 프로그램이 종료되기 전까지는 메뉴가 무한 반복하며 계속 출력되어야 합니다.
    while (1) {
        printf(">> 도서 검색 <<\n");
        printf("1.도서명 검색\t\t\t2.출판사 검색\n3.ISBN 검색\t\t\t4.저자명 검색\n5.전체 검색\t\t\t6.이전 메뉴\n");

        printf("\n번호를 입력하세요: ");
        scanf("%d", &menu);
        putchar(getchar());

        switch (menu) {
            case 1: // 도서명 검색
                printf("도서명을 입력하세요: ");
                scanf("%s", keyword);
                putchar(getchar());
                // 도서명이 일치하는 도서를 찾아냅니다.
                findResults = findBookNodeByBookName(&bookList, keyword);

                // 도서명이 일치하는 도서를 찾지 못했다면 에러메세지를 띄워줍니다.
                if (findResults == NULL)
                    printf("제목이 '%s'인 도서가 존재하지 않습니다.\n", keyword);

                // 도서명이 일치하는 도서를 찾았다면 찾아낸 모든 책의 정보를 모두 출력합니다.
                else {
                    printBookList(*findResults, SEARCH);
                }
                break;

            case 2: // 출판사 검색
                printf("출판사를 입력하세요: ");
                scanf("%s", keyword);
                getchar();

                // 출판사가 일치하는 도서를 찾아냅니다.
                findResults = findBookNodeByPublisherName(&bookList, keyword);

                // 출판사가 일치하는 도서를 찾지 못했다면 에러메세지를 띄워줍니다.
                if (findResults == NULL)
                    printf("출판사가 '%s'인 도서가 존재하지 않습니다.\n", keyword);

                else
                    printBookList(*findResults, SEARCH);
                break;

            case 3: //ISBN 검색
                printf("ISBN을 입력하세요: ");
                scanf("%lu", &isbn);
                getchar();
                // ISBN 이 일치하는 도서를 찾아냅니다.
                findResults = findBookNodeByISBN(&bookList, isbn);

                // ISBN 이 일치하는 도서를 찾지 못했다면 에러메세지를 띄워줍니다.
                if (findResults == NULL)
                    printf("ISBN이 '%lu'인 도서가 존재하지 않습니다.\n", isbn);

                else
                    printBookList(*findResults, SEARCH);
                break;

            case 4: // 저자명 검색
                printf("저자명을 입력하세요: ");
                scanf("%s", keyword);
                getchar();

                // 저자명이 일치하는 도서를 모두 찾아냅니다.
                findResults = findBookNodeByAuthorName(&bookList, keyword);

                // 저자명이 일치하는 도서를 찾지 못했다면 에러메세지를 띄워줍니다.
                if (findResults == NULL)
                    printf("저자명이 '%s'인 도서가 존재하지 않습니다.\n", keyword);
                // 저자명이 일치하는 도서를 찾았다면 찾아낸 책의 정보를 모두 출력합니다.
                else
                    printBookList(*findResults, SEARCH);
                break;

            case 5: // 전체 검색
                // 검색 조건 없이 모든 책의 정보를 출력합니다.
                printBookList(bookList, SEARCH);
                break;

            case 6: // 이전 메뉴
                beforeMenu();
                return;
        }
    }
}

// 관리자 메뉴를 출력하고, 메뉴 선택을 위한 입력을 받습니다.
// 관리자 메뉴에는 도서등록 도서 삭제 도서 대여 도서 반납 도서 검색 회원 목록 로그아웃 기능이 있습니다.
void selectAdminMenu() {
    int menu;
    while (1) {
        printf(">> 관리자 메뉴 <<\n");
        printf("1.도서 등록\t\t\t2.도서 삭제\n3.도서 대여\t\t\t4.도서 반납\n5.도서 검색\t\t\t6.회원 목록\n7.로그아웃\t\t\t\t8.프로그램 종료\n");
        printf("\n번호를 입력하세요: ");
        scanf("%d", &menu);
        putchar(getchar());


        switch (menu) {
            case 1: // 도서 등록
                registerNewBook(&bookList);
                break;

            case 2: // 도서 삭제
                deleteBook(&bookList);
                break;

            case 3: // 도서 대여
                lendBook(&bookList, &borrowList, &clientList);
                break;

            case 4: // 도서 반납
                returnBook(&clientList, &bookList, &borrowList);
                break;

            case 5: // 도서 검색
                selectSearchBookMenu(selectAdminMenu);
                return;

            case 6: // 회원 목록
                if (loadMemberList(&clientList)) {
                    selectAdminMenu();
                    return;
                }
                break;

            case 7: // 로그 아웃
                mainMenu();
                return;

            case 8: // 프로그램 종료
                closeAllFile();
                exit(0);
        }
    }
}


void closeAllFile() {
    closeClientFile();
    closeBookFile();
    closeBorrowFile();
}