/*Nuha Imran*/
/*16/04/2022*/
/*ID:20696366*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
 
 typedef struct ListNode
    {
        void* data;
        struct ListNode* next;
    } ListNode;
    
      typedef struct LinkedList
    {
        ListNode* head;
        int size;
    } LinkedList;

LinkedList *createLinkedList();
void insertLast( LinkedList* list, void* inData );
void* removeFirst( LinkedList* list );
void freeLinkedList( LinkedList* list);
#endif

