// 주로 client List와 client File을 관리하는 파일입니다.

#include "clients.h"

FILE *clientFile;

// 파일 불러오기
void loadClientFile(clientNode *clients) {
    // 파일 읽기 모드로 열기
    clientFile = fopen(CLIENT_FILE_PATH, "r+");

    if (clientFile == NULL) {
        printf("client 파일이 없습니다.\n");
        return;
    }

    // client 파일에서 데이터를 추출하여 clients 에 저장합니다.
    while (!feof(clientFile)) {
        clientNode* node = readClientFileLine(clientFile);
        addClient(clients, node);
    }

    fclose(clientFile);
}

// client 파일을 한 줄 읽습니다.
clientNode* readClientFileLine(FILE* clientFile) {
    clientNode* node = (clientNode *) calloc(1, sizeof(clientNode));
    fscanf(clientFile, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &(node -> client.studentId), node -> client.password, node -> client.name, node -> client.address, node -> client.phone);
    return node;
}


// clientFile 을 clientList 의 정보로 덮어 씁니다.
void overwriteClientFile(clientNode clientList) {
    clientFile = fopen(CLIENT_FILE_PATH, "w");

    while (!isEmptyClient(clientList.client)) {
        fprintf(clientFile, "%d|%s|%s|%s|%s\n",
                clientList.client.studentId,                  // 학번
                clientList.client.password,                   // 비밀번호
                clientList.client.name,                       // 이름
                clientList.client.address,                    // 첫 주소
                clientList.client.phone                       // 전화번호 1 ex) 3367-7355의 3367
        );

        if (clientList.next == NULL)
            break;
        clientList = *(clientList.next);
    }
    fclose(clientFile);
}



// client List의 맨 뒤에 client를 추가하는 함수
void addClient(clientNode *clientList, clientNode *addedClient) {
    if (clientList == NULL) {
        printf("clientList는 NULL 일 수 없습니다.\n");
        return;
    } else if (addedClient == NULL) {
        printf("addedClient는 NULL 일 수 없습니다.\n");
        return;
    }

    // List의 첫 번째 요소라면 clientList 헤더에 직접 데이터를 넣습니다.
    if (isEmptyClient(clientList -> client)) {
        clientList -> client = addedClient -> client;
    } else {
        // clientList 의 맨 마지막에 찾아가서 client를 추가합니다.
        while (clientList -> next != NULL) {
            clientList = clientList -> next;
        }

        clientList -> next = addedClient;
    }
}

// client List의 at번째 원소를 지우는 함수
void removeClient(clientNode *clientList, int at) {
    if (clientList == NULL) {
        printf("clientList는 NULL 일 수 없습니다.\n");
        return;
    }

    if (at < 0) {
        printf("음수는 불가합니다.\n");
        return;
    }

    int length = clientLength(*clientList);
    if (length <= at) {
        printf("길이 %d인 리스트에서 %d번째 요소를 제거할 수 없습니다.\n", length, at);
        return;
    }

    // 0번째 요소를 지우는 것은 리스트의 헤더를 지우는 것과 같습니다.
    if (at == 0) {
        // 리스트 크기가 1이하 라면 Header의 값 만을 초기화 시킵니다.
        if (length <= 1) {
            clientList -> client = initClient();
        }

        // 리스트 크기가 1보다 크다면 Header의 위치를 한 칸 옮겨줍니다. 리스트의 헤더가 NULL이 되면 안되기 때문입니다.
        else {
            clientNode *header = clientList;
            *clientList = *(clientList -> next);
            free(header);
        }
    }

    // 헤더가 아닌 요소를 제거한다면 이전 노드의 next를 삭제할 요소의 next로 바꿔줍니다.
    else {
        clientNode* beforeClientNode = getClientNode(clientList, at - 1);

        // 맨 마지막 원소를 제거한다면
        if (length == at + 1) {
            free(beforeClientNode -> next);
            beforeClientNode -> next = NULL;
        } else {
            clientNode* willRemoveClientNode = getClientNode(beforeClientNode, 1);
            clientNode* nextClientNode = getClientNode(beforeClientNode, 2);
            free(willRemoveClientNode);
            beforeClientNode -> next = nextClientNode;
        }
    }
}


// client List의 at번째에 client를 하나 추가하는 함수
void insertClient(clientNode *clientList, clientNode *addedClient, int at) {
    if (clientList == NULL) {
        printf("clientList는 NULL 일 수 없습니다.\n");
        return;
    } else if (addedClient == NULL) {
        printf("clientList는 NULL 일 수 없습니다.\n");
        return;
    }

    if (at < 0) {
        printf("음수는 불가합니다.\n");
        return;
    }


    // 0번째에 추가하는 것은 Header를 바꾸는 것과 동일합니다.
    if (at == 0) {
        // 리스트에 아무 값도 없다면 Header 자체에 값을 넣어줍니다.
        if (isEmptyClient(clientList -> client)) {
            *clientList = *addedClient;
        }

        // 리스트에 어떠한 값이라도 들어있다면 Header를 재정의 하고 next 값으로 이전 Header를 넣어줍니다.
        // 헤더가 바뀌더라도 이전의 리스트는 유지되어야 하기 때문입니다.
        else {
            clientNode* tmpClientNode = (clientNode*) calloc(1, sizeof(clientNode));
            *tmpClientNode = *clientList;
            addedClient -> next = tmpClientNode;
            *clientList = *addedClient;
        }
    }

        // 0번째가 아닌 원소에 추가하는 것이라면 at - 1번째 원소의 next를 추가될 원소를 가리키게 하고,
        // 추가될 원소의 next는 at번째 원소를 카리킵니다.
    else {
        int length = clientLength(*clientList);
        if (length < at) {
            printf("%d는 List크기(%d)보다 큽니다.\n", at, length);
            return;
        }

        clientNode* changedClientNode;
        clientNode* pushedClientNode;

        changedClientNode = getClientNode(clientList, at - 1);
        pushedClientNode = getClientNode(changedClientNode, 1);
        changedClientNode -> next = addedClient;

        if (pushedClientNode != NULL) {
            addedClient -> next = pushedClientNode;
        }
    }
}

int isEqualClient(client leftClient, client rightClient) {
    return leftClient.studentId == rightClient.studentId &&
           !strcmp(leftClient.address, rightClient.address) &&
           !strcmp(leftClient.password, rightClient.password) &&
           !strcmp(leftClient.name, rightClient.name) &&
           !strcmp(leftClient.phone, rightClient.phone);
}


// clientNode index 번호 찾기
int indexOfClientNode(clientNode* clientList, clientNode foundClientNode) {
    if (clientList == NULL || isEmptyClient(foundClientNode.client))
        return -1;
    int count = 0;
    while (!isEmptyClient(clientList->client)) {
        if (isEqualClient(clientList->client, foundClientNode.client)) {
            return count;
        }

        if (clientList->next == NULL)
            return -1;
        clientList = clientList->next;
        count++;
    }
    return -1;
}


// at 번째 clientNode 추출
clientNode* getClientNode(clientNode* clientList, int at) {
    if (clientList == NULL) {
        printf("clientList는 NULL 일 수 없습니다.\n");
        return NULL;
    }
    int index = 0;

    while (clientList -> next != NULL) {
        // at 번째 원소에 도달하면 리턴
        if (at == index++) {
            return clientList;
        }

        if (clientList -> next == NULL) {
            break;
        }
        clientList = clientList -> next;
    }

    if (at == index) {
        return clientList;
    }

    // at보다 길이가 짧을 때 0을 리턴
    return NULL;
}

// client List의 길이를 구하는 함수
int clientLength(clientNode clientList) {
    int count = 1;

    while (clientList.next != NULL) {
        count++;
        if (clientList.next == NULL) {
            break;
        }
        clientList = *(clientList.next);
    }

    // 첫 번째 요소가 비었을 때는 길이 0
    if (count == 1 && isEmptyClient(clientList.client)) {
        return 0;
    }

    return count;
}


// name 으로 client 찾기
clientNode* findClientNodeByName(clientNode* list, char* name) {
    while (!isEmptyClient(list->client)) {
        if (!strcmp(list->client.name, name)) {
            return list;
        }

        if (list->next == NULL)
            break;
        list = list->next;
    }
    return NULL;
}


// studentId 로 client 찾기
clientNode* findClientNodeById(clientNode* list, int id) {
    while (!isEmptyClient(list->client)) {
        if (list->client.studentId == id) {
            return list;
        }

        if (list->next == NULL)
            break;
        list = list->next;
    }
    return NULL;
}


client initClient() {
    client client;
    client.studentId = 0;
    strcpy(client.name, "");
    strcpy(client.password, "");
    strcpy(client.address, "");
    strcpy(client.phone, "");
    return client;
}


int isEmptyClient(client c) {
    return c.studentId == 0 && !strcmp(c.phone, "") && !strcmp(c.address, "") && !strcmp(c.name, "") && !strcmp(c.password, "");
}


void printClient(client c) {
    printf("학번: %d\n", c.studentId);
    printf("이름: %s\n", c.name);
    printf("주소: %s\n", c.address);
    printf("전화번호: %s\n\n", c.phone);
//    printf("비밀번호: %s\n", c.password);
}

void printClientList(clientNode printingClient) {
    while (!isEmptyClient(printingClient.client)) {
        printClient(printingClient.client);
        if (printingClient.next == NULL)
            break;
        printingClient = *printingClient.next;
        printf("\n");
    }
}

void closeClientFile() {
    fclose(clientFile);
}
