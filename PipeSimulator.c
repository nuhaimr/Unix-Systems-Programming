#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "PipeSimulator.h"
#include <fcntl.h>
#include <regex.h>

//this function creates a filename that is stored
void storation_file(int fileno,char fname[]){
	char* filenumber = InttoChar(fileno);
	concat(fname, filenumber);
}

//this is a function for concatenation takes two strings and makes them one
void concat(char string1[], char string2[]){
	int length, j;
	length = 0;
	//we keep imcrementing length till its not empty
	while(string1[length] != '\0'){
		length++;
	}
	//again if not a null character increments j and length but this time checks other string
	for(j = 0;string2[j] != '\0';j++, length++){
		//puts them together
		string1[length] = string2[j];
	}

	string1[length] = '\0';
}

//this function is used to convert an integer to a character
char* InttoChar(int num){
	//declaring some variables
	int i = 0;
	//this will be the number of digits in the number
	int size = 0;
	int n = num;
	int right;
	//this loop will count the number of digits in the number
	while(n != 0){
		n = n/10;
		size++;
	}
	//allocating memory to store string version of the number
	char* fileno = (char*)mmap(NULL, sizeof(char)*(size+1), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0,0);
	//loop keeps running till there are digits in the number
	while(i < size){
		//get righmost digit
		right = num%10;
		//diving by 10 to get rightmost digit so that second digit from right 
		//will become right most after the loop runs again
		num = num/10;
		//storing value in string starting from right
		//so that it is stored correctly in the format I want
		fileno[size - (i + 1)] = right + '0';
		i++;

	}
	fileno[size] = '\0';
	return fileno;
	//freeing memory
	munmap(fileno, sizeof(char)*(size+1));
}

//main taking two command lines arguments
int main(int argc,char* argv[]){
	int counter = 0;
	//error checking that the file is entered
	if(argc != 2 | argc > 2){
		printf("Usage is <Program_name> <input_file>\n");
		return 0;
	}
	//if 2 arguments proceed
	else if(argc == 2){
		//declaring the LinkedList
		LinkedList* list1;
		//pointer for file
		int file_ptr;
		//opening the file entered in command line
		file_ptr = open(argv[1], O_RDONLY);
		//error checking
		if(file_ptr < 0){
			printf("Your file does not exist\n");
			close(file_ptr);
		}
		else{


			char *lines;
			int res;
			//creating a linked list
			list1 = createLinkedList();
			do{
				//allocating memory to store lines
				lines = (char*)mmap(NULL, sizeof(char)*(500), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0,0);
				//reading file
				res = read(file_ptr, lines, sizeof(char)*500);	
				//this is to store commands next line is allocating it memory to store		
				char* store_cmd;
				store_cmd = (char*)mmap(NULL, sizeof(char)*500, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0,0);
				//declaring variables to loop
				int a = 0,c = 0;
				//if file not empty proceed
				if(res != 0)
				{
					//for not end of lines
					for(a = 0;lines[a] != '\0';a++){
						//enters this loop if not a new line
						if(lines[a] != '\n'){
							//it stores whats there,loops again and keep incrementing
							store_cmd[c] = lines[a];
							c++;
						}
						else{
							//inserts the contents of store cmd in the linked list
							insertLast(list1,store_cmd);
							store_cmd = (char*)mmap(NULL, sizeof(char)*500, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0,0);
							c = 0;
						}

					}
				}
				else{
					//freeing memory
					munmap(lines, sizeof(char)*(500));
				}
				//freeing memory
				munmap(store_cmd, sizeof(char)*(500));
			}
			//terminating condition keep doing till file not empty
			while(res != 0);
			close(file_ptr);

			ListNode* node;
			node = list1->head;
			//to iterate node
			ListNode* iter_node;
			char file_input[12];
			//do this if the linked list has data
			while(node != NULL)
			{
				//12 because output1.txt and last for null character
				char file_output[12] = "output";
				iter_node = node->next;
				//to store the value that is being removed from the linked list
				char *tmp_ptr = removeFirst(list1);
				//increment the counter upon removal of value
				counter++;
				//datatype to store process id
				pid_t pid;
				//allocating memory to array1 it is made to later be used for execv system call
				char** array1 = mmap(NULL, sizeof(char*)*4, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0,0);
				array1[0] = "/bin/sh";
				array1[1] = "-c";
				array1[2] = tmp_ptr;
				//explained above
				storation_file(counter,file_output);
				//for creating a child process
				pid = fork();
				//this is the child process
				if(pid == 0){
					//if this is last element of the Linked List
					if(iter_node == NULL){
						//linked List includes elements
						if(counter == 1){
							//run execv systemcall
							execv(array1[0], array1);
						}
						else{
							//opening the input file
							int fd = open(file_input,O_RDONLY);
							//to take input from file
							dup2(fd,0);
							//to execute command
							execv(array1[0],array1);
							close(fd);
						}
					}
					else{
						//if linked list has elements
						if(counter == 1){
							//create an output file
							int fd = creat(file_output,S_IRUSR | S_IWUSR);
							//to store to output file
							dup2(fd,1);
							//to execute command
							execv(array1[0],array1);
							close(fd);
						}

						else{
							//opening input file
							int fd = open(file_input,O_RDONLY);
							//creating output file
							int fd2 = creat(file_output,S_IRUSR | S_IWUSR);
							//one is taking input from file
							//one is moving output to new file
							dup2(fd,0);
							dup2(fd2,1);
							//executing
							execv(array1[0],array1);
							close(fd);
							close(fd2);
						}
					}
				}
				//this is the parent process
				else if(pid > 0){

					//so no zombie process is created
					wait(NULL);
					node = iter_node;

				}
				else{

					printf("Failed to create a child process");

				}
				int i = 0;
				for(i = 0;i < 12;i++){
					file_input[i] = file_output[i];
				}
				//freeing the array
				munmap(array1, sizeof(char)*4);

			}
			//freeing the list we created
			freeLinkedList(list1);	
		}


	}

}



