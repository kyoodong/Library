#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main() {
	char alphabet[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
	char number[] = "1234567890";

	FILE *clientFile, *bookFile, *borrowFile;
	int stdId = 20160001, alphabetLength = strlen(alphabet), numberLength = strlen(number), bookId = 1000000;
    int i, j;
    unsigned long long ISBN = 1000000000000;
    
	clientFile = fopen("client.txt", "w");
	bookFile = fopen("book.txt", "w");
	borrowFile = fopen("borrow.txt", "w");
    
    // client file
    for (i = 0; i < 1000; i++) {
        char password[5], name[7], firstAddress[8], secondAddress[4], lastAddress[4], firstPhone[5], lastPhone[5];
        
        for (j = 0; j < 4; j++)
            password[j] = alphabet[rand() % alphabetLength];
        password[j] = '\0';
        
        for (j = 0; j < 6; j++)
            name[j] = alphabet[rand() % alphabetLength];
        name[j] = '\0';
        
        for (j = 0; j < 7; j++)
            firstAddress[j] = alphabet[rand() % alphabetLength];
        firstAddress[j] = '\0';
        
        for (j = 0; j < 3; j++)
            secondAddress[j] = alphabet[rand() % alphabetLength];
        secondAddress[j] = '\0';
        
        for (j = 0; j < 3; j++)
            lastAddress[j] = alphabet[rand() % alphabetLength];
        lastAddress[j] = '\0';
        
        for (j = 0; j < 4; j++)
            firstPhone[j] = number[rand() % numberLength];
        firstPhone[j] = '\0';
        
        for (j = 0; j < 4; j++)
            lastPhone[j] = number[rand() % numberLength];
        lastPhone[j] = '\0';
        
        fprintf(clientFile, "%d||%s||%s||%s %s-%s||010-%s-%s\n",
                stdId++,                        // 학번
                password,                       // 비밀번호
                name,                           // 이름
                firstAddress,                   // 첫 주소
                secondAddress,                  // 뒷 주소 1 ex) 987-123의 987
                lastAddress,                    // 뒷 주소 2 ex) 987-123의 123
                firstPhone,                     // 전화번호 1 ex) 3367-7355의 3367
                lastPhone                       // 전화번호 2 ex) 3367-7355의 7355
                );
    }
    
    
    // book file
    for (i = 0; i < 1000; i++) {
        char bookName[10], publisherName[7], authorName[8], secondAddress[4], holdingLocation[8];
        
        for (j = 0; j < 9; j++)
            bookName[j] = alphabet[rand() % alphabetLength];
        bookName[j] = '\0';
        
        for (j = 0; j < 6; j++)
            publisherName[j] = alphabet[rand() % alphabetLength];
        publisherName[j] = '\0';
        
        for (j = 0; j < 7; j++)
            authorName[j] = alphabet[rand() % alphabetLength];
        authorName[j] = '\0';
        
        for (j = 0; j < 7; j++)
            holdingLocation[j] = alphabet[rand() % alphabetLength];
        holdingLocation[j] = '\0';
        
        fprintf(bookFile, "%d||%s||%s||%s||%lld||%s||Y\n",
                bookId++,                       // 도서 번호
                bookName,                       // 책 이름
                publisherName,                  // 출판사 이름
                authorName,                     // 저자 이름
                ISBN++,                         // ISBN
                holdingLocation                // 소장처
                );
    }
    
    
    stdId = 20160010;
    bookId = 1000000;
    
    // borrow file
    for (i = 0; i < 100; i++) {
        char bookName[10], publisherName[7], authorName[8], secondAddress[4], holdingLocation[8];
        
        for (j = 0; j < 9; j++)
            bookName[j] = alphabet[rand() % alphabetLength];
        bookName[j] = '\0';
        
        for (j = 0; j < 6; j++)
            publisherName[j] = alphabet[rand() % alphabetLength];
        publisherName[j] = '\0';
        
        for (j = 0; j < 7; j++)
            authorName[j] = alphabet[rand() % alphabetLength];
        authorName[j] = '\0';
        
        for (j = 0; j < 7; j++)
            holdingLocation[j] = alphabet[rand() % alphabetLength];
        holdingLocation[j] = '\0';
        
        int a = rand();
        time_t t;
        time(&t);
        
        if (i < 100) {
            fprintf(borrowFile, "%d||%d||%d||%d\n",
                    stdId++,                       // 학번
                    bookId++,                       // 책 번호
                    rand(),                        // 대여 일자
                    a                         // 반납 일자
                    );
        } else {
            fprintf(borrowFile, "%d||%d||%d||%ld\n",
                    stdId++,                       // 학번
                    bookId++,                      // 책 번호
                    rand(),                        // 대여 일자
                    t + rand()                     // 반납 일자
                    );
        }
    }
	return 0;
}
