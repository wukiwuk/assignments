#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define TABLE_SIZE 100
struct Node {
    char key[100];
    struct Node *next;
};

struct HashTable {
    char key[100];
    struct Node *chain;
} ht[TABLE_SIZE];

void initializationHT() {
	for(int i = 0; i < TABLE_SIZE; i++) {
		strcpy(ht[i].key, "");
	}
}

int StoI(char key[]) {
	int sum = 0;
	for(int i = 0; key[i] != '\0'; i++) {
		sum += key[i];		
	}
	return sum;
}

int DivHash(char key[]) {
	int intKey = StoI(key);
	return intKey % TABLE_SIZE;
}

int firstchar(char key[]) {
	if(key[0] == '\0') {
		return -1;
	}
	char firstChar = key[0];
	if(!isalpha(firstChar)) {
		return -1;
	}
	return tolower(firstChar) - 'a';
}

int rotate(char key[]) {
	int a = DivHash(key);
	int rotatedNum;
	if(a == 0) {
		return a;
	} else if(a < 10) {
		return a;
	} else if(a == 10) {
		return 1;
	} else {
		int tens = a / 10;
		int ones = a % 10;
		rotatedNum = (ones * 10) + tens;
		return rotatedNum;
	}
}

void linearProbing(char key[], int index) {
    while(strcmp(ht[index].key, "") != 0) {
        index = (index + 1) % TABLE_SIZE; 
    }
    strcpy(ht[index].key, key);
    printf("Key %s dimasukkan ke index %d (Linear Probing)\n", key, index);
}

void rehash(char key[]) {
    int index = DivHash(key);
    int newIndex = (index + 17) % TABLE_SIZE; 
    while(strcmp(ht[newIndex].key, "") != 0) {
        newIndex = (newIndex + 1) % TABLE_SIZE;
    }
    strcpy(ht[newIndex].key, key);
    printf("Key %s dimasukkan ke index %d (Rehashing)\n", key, newIndex);
}

void chaining(char key[], int index) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->key, key);
    newNode->next = ht[index].chain;
    ht[index].chain = newNode;
    printf("Key %s dimasukkan ke index %d (Chaining)\n", key, index);
}

void insert(char key[], int (*hashFunction)(char[]), int colHand) {
	int index = hashFunction(key);
	
	if(strcmp(ht[index].key, "") == 0) {
		strcpy(ht[index].key, key);
		printf("Key %s dimasukan ke index %d\n", key, index);
	} else {
		printf("Collision terjadi pada index %d\n", index);
        if(colHand == 1) {
            linearProbing(key, index);
        } else if(colHand == 2) {
            rehash(key);
        } else if(colHand == 3) {
            chaining(key, index);
    	}
	}
}

void displayHT() {
    printf("\nHash Table\n");    
    for(int i = 0; i < TABLE_SIZE; i++) {
        if(strcmp(ht[i].key, "") != 0) {
            printf("Index %d: %s\n", i, ht[i].key);
        } else if (ht[i].chain != NULL) {
            printf("Index %d: ", i);
            struct Node *temp = ht[i].chain;
            while (temp) {
                printf("%s -> ", temp->key);
                temp = temp->next;
            }
            printf("NULL\n");
        } else {
            printf("Index %d: kosong\n", i);
        }
    }
}

int menu() {
    int i;

    do {
        system("cls");
        puts("1. Division");
        puts("2. First Character");
        puts("3. Rotating");
        printf("Nomor hash yang mau dipake: ");

        if (scanf("%d", &i) != 1) { 
            printf("Input harus angka!\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (i < 1 || i > 3) {
            printf("Input nomor yang ada.\n");
            getchar(); 
        }
        
    } while (i < 1 || i > 3);

    return i;
}

int menu2() {
	int i;

    do {
        system("cls");
        puts("1. Linear Probing");
        puts("2. Rehashing");
        puts("3. Chaining");
        printf("Nomor Collision Handling yang mau dipake: ");

        if (scanf("%d", &i) != 1) { 
            printf("Input harus angka!\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (i < 1 || i > 3) {
            printf("Input nomor yang ada.\n");
            getchar(); 
        }
        
    } while (i < 1 || i > 3);

    return i;
}

int main() {
	initializationHT();
	char key[100];
	
	int(*hashFunction)(char[]) = NULL;
	int input = menu();
	switch(input) {
		case 1: {
			hashFunction = DivHash;
			break;
		}
		case 2: {
			hashFunction = firstchar;
			break;
		}
		case 3: {
			hashFunction = rotate;
			break;
		}
	}
	
	int colHand = menu2();
	
	while(1) {
		printf("Masukkan key (string) atau exit untuk berhenti:");
		scanf("%s", key);
		if(strcmp(key,"exit")==0) break;
		insert(key, hashFunction, colHand);
	}
	
	displayHT();
}
