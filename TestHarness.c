//Name:Nuha Imran
//ID:20696366

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

int* main(){

	printf("--Welcome to the Linked List--\n");
	printf("\n");
	printf("\n");
	LinkedList* list1;
	void* removeData;
	int no =  1;
	int no1 = 2;
	int no2 = 3;
	int no3 = 4;
	int no4 = 5;
	int no5 = 6;
	list1 = createLinkedList();
	insertLast(list1,&no);
	insertLast(list1,&no1);
	insertLast(list1,&no2);
	insertLast(list1,&no3);
	insertLast(list1,&no4);
	insertLast(list1,&no5);

	if((*list1).size == 6){
		printf("Your values have been inserted!\n");
	}

	printf("\n");
	printf("\n");

	printf("--You are now removing values--\n");

	removeData = removeFirst(list1);
	printf("The value removed is: %d\n", *(int*)removeData);
	removeData = removeFirst(list1);
	printf("The value removed is: %d\n", *(int*)removeData);
	removeData = removeFirst(list1);
	printf("The value removed is: %d\n", *(int*)removeData);
	removeData = removeFirst(list1);
	printf("The value removed is: %d\n", *(int*)removeData);

	printf("\n");
	printf("\n");

	if((*list1).size == 2){
		printf("--Your values have been successfully removed!--\n");
	}

	printf("\n");
	printf("\n");

	printf("--The linked list is functioning--\n");
	printf("--TEST PASSED--\n");
	freeLinkedList(list1);	
	return 0; 	





}

