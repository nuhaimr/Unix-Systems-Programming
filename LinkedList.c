/*Nuha Imran*/
/*16/04/2022*/
/*ID:20696366*/
#include <stdio.h>
#include "LinkedList.h"
#include <sys/mman.h>

//function to create a linked list
LinkedList* createLinkedList()
{
	//pointer that returns the value of mmap
	int *mmap_return;
	mmap_return = mmap(NULL, sizeof(LinkedList), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,0,0);
	if(mmap_return == MAP_FAILED){
		printf("Mapping Failed\n");
	}

	LinkedList *list = (LinkedList*)mmap_return;
	//initially head is null,size is zero
	list->head = NULL;
	list->size = 0;

	return list;
}

//insert last of a linked list taking in list and value to store
void insertLast( LinkedList* list, void* inData )
{
	//using mmap system call 
	int *mmap_return1;
	mmap_return1 = mmap(NULL, sizeof(ListNode), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0,0);
	if(mmap_return1 == MAP_FAILED){
		printf("Mapping Failed\n");
	}

	ListNode* newNode = (ListNode*)mmap_return1;
	newNode->data = inData;
	newNode->next = NULL;

	//empty list indicating the new node is the head
	if( list->head == NULL )
	{
		list->head = newNode;
	}
	//if it has one value tell the new head normal linked list insertFirst logic used
	else
	{
		ListNode* nextNode = list->head;
		while(nextNode->next != NULL){
			nextNode = nextNode->next;

		}
		nextNode->next = newNode;
	}
	//increment size on each node
	list->size++;

}

//function to remove first takes in a list
void* removeFirst( LinkedList* list )
{
	if(list->size != 0){
		void* removedData;
		ListNode* temp = list->head;
		removedData = temp->data;
		list->head = list->head->next;
		//freeing the temp 
		munmap(temp, sizeof(ListNode));
		list->size--;
		return removedData;
	}
	else{
		printf("Linked List is empty");
	}
}

//freeing the linked list
void freeLinkedList(LinkedList* list)
{
	ListNode *node, *nextNode;
	node = list->head;
	while (node != NULL)
	{
		nextNode = node->next;
		munmap(node, sizeof(ListNode));
		node = nextNode;
	}
	munmap(list, sizeof(LinkedList));
}










