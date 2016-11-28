#ifndef clients_h
#define clients_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLIENT_FILE_PATH "./client.txt"

typedef struct {
    int studentId;             // 학번
    char password[20];  // 비밀번호
    char name[20];      // 고객 이름
    char address[50];   // 고객 주소
    char phone[20];     // 고객 전화번호
} client;

typedef struct clientNode {
    client client;
    struct clientNode *next;
} clientNode;


void loadClientFile(clientNode *clients);
clientNode* readClientFileLine(FILE* clientFile);
void overwriteClientFile(clientNode clientList);
void addClient(clientNode *clientList, clientNode *addedClient);
void removeClient(clientNode *clientList, int at);
void insertClient(clientNode *clientList, clientNode *addedClient, int at);
int isEqualClient(client leftClient, client rightClient);
int indexOfClientNode(clientNode* clientList, clientNode foundClientNode);
clientNode* getClientNode(clientNode* clientList, int at);
int clientLength(clientNode clientList);
clientNode* findClientNodeByName(clientNode* list, char* name);
clientNode* findClientNodeById(clientNode* list, int id);
clientNode initClientNode();
client initClient();
int isEmptyClient(client c);
void printClient(client c);
void printClientList(clientNode printingClient);
void closeClientFile();

#endif