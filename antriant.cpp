#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char id[10];
	struct node *next;
}node;

typedef struct SLL {
	node *head;
}SLL;

node *newNode(const char id[]) {
	node *newNode = (node*)malloc(sizeof(node));
	strcpy(newNode->id, id);
	newNode->next = NULL;
	
	return newNode;
}

SLL *newSLL() {
	SLL *newSLL = (SLL*)malloc(sizeof(SLL));
	newSLL->head = NULL;
	
	return newSLL;
}

void pushb(SLL *list, const char id[]) {
	node *n = newNode(id);
	if(list->head == NULL) {
		list->head = n;
		n->next = NULL;
		return;
	}
	
	node *curr = list->head;
	while(curr->next != NULL) {
		curr = curr->next;
	}
	
	curr->next = n;
}

void pushasc(SLL *list, const char id[]) {
	node *n = newNode(id);
	if(list->head == NULL || (strcmp(id, list->head->id) < 0)) {
		n->next = list->head;
		list->head = n;
		return;
	}
	
	node *curr = list->head;
	while(curr->next!=NULL && strcmp(curr->next->id, id) < 0) {
		curr = curr->next;
	}
	
	n->next = curr->next;
	curr->next = n;
}

void printList(SLL *list) {
	node *curr = list->head;
	while(curr!=NULL) {
		printf("%s ", curr->id);
		curr = curr->next;
	}
	printf("\n");
}

void pop(SLL *list, const char id[]) {
	node *curr = list->head;
	node *prev = NULL;
	
	while(curr!=NULL && (strcmp(curr->id,id) != 0)) {
		prev = curr;
		curr = curr->next;
	}
	
	if(curr == NULL) return;
	
	if(prev == NULL) {
		list->head = curr->next;
	} else {
		prev->next = curr->next;
	}
	free(curr);
}

int main() {
	SLL *listV = newSLL(); //listVIP
	SLL *listR = newSLL(); //listReg
	SLL *listA = newSLL(); //ListAtrian
	
	int jmlhVIP, jmlhREG;
	scanf("%d %d", &jmlhVIP, &jmlhREG);
	char idVIP[10], idREG[10];
	for(int i = 0; i < jmlhVIP; i++) {
		scanf("%s", idVIP);
		pushasc(listV, idVIP);
	}
	for(int i = 0; i < jmlhREG; i++) {
		scanf("%s", idREG);
		pushasc(listR, idREG);
	}
	
	int c;
	scanf("%d", &c);
	char idC[10];
	for(int i = 0; i < c; i++) {
		scanf("%s", idC);
		pop(listV, idC);
		pop(listR, idC); 
	}
	
//	printList(listV);
//	printList(listR);
	int i = 0, j = 0;
	node *curr1 = listV->head;
	node *curr2 = listR->head;
	while(i < jmlhVIP || j < jmlhREG) {
		if(curr1 == NULL && j < jmlhREG) {
			while(j < jmlhREG && curr2 != NULL) {
				pushb(listA, curr2->id);
				curr2 = curr2->next;
				j++;
			}
			break;
		} else if (curr2 == NULL && i < jmlhVIP) {
			while(i < jmlhVIP && curr1 != NULL) {
				pushb(listA, curr1->id);
				curr1 = curr1->next;
				i++;
			}
			break;
		}
		pushb(listA, curr1->id);
		pushb(listA, curr2->id);
		
		curr1 = curr1->next;
		curr2 = curr2->next;
		i++;
		j++;
	}
	printList(listA);
}
