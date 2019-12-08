
//I didn't wanted to use OOP for all of them so I have decided to write this one with C


#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	char data;
	struct Node* next;
	struct Node* prev;
}node;

int LIST_SIZE = 0;	//size of the list

node* first = NULL, *last = NULL;

//main functions
void Push(char data);
void Pop();
void PushBeg(char data);
void PopBeg();
void Insert(int data, int place);
void Delete(int place);
void Display();
void Control();


//side functions
void UI_Menu();
void UI_Title();
int CheckSize(int place);
void DisplaySteps(int step);
void ReadFile();


//main code
int main() {
	int place = 0;
	char data;
	int option = 0;

	UI_Title();

	ReadFile();
	Display();

	while (1) {

		UI_Menu();
		scanf_s("%d", &option);

		switch (option) {
		case 1:	printf("\nData: ");
			scanf_s(" %c", &data); //leave one blank before %c to skip over whitespace (or it will read \n automatically)
			Push(data);
			Display();	break;

		case 2:	Pop();	
			Display();	break;

		case 3:	printf("\nData: ");
			scanf_s(" %c", &data);
			PushBeg(data);
			Display();  break;

		case 4:	PopBeg();
			Display();	break;

		case 5: printf("Data: ");
			scanf_s(" %c", &data);
			printf("\nPlace: ");
			scanf_s("%d", &place);
			if (CheckSize(place)) {	//check if the place is exist. if true, then insert.
				Insert(data, place);
				Display();
			}	break;

		case 6:	printf("Delete place: ");
			scanf_s("%d", &place);
			if (CheckSize(place)) {
				Delete(place);
				Display();
			}	break;

		case 7:	Control();
			Display();	break;

		case 0:	printf("\nExiting program..\n");
			exit(0);
		}
	}
}


void Push(char data) {
	node* temp = (node*)malloc(sizeof(node));

	temp->data = data;
	temp->next = NULL;
	
	if (first == NULL) {
		temp->prev = NULL;
		first = temp;
		last = first;
	}

	else {
		last->next = temp;
		temp->prev = last;
		last = last->next;
	}

	LIST_SIZE++;
}

void Pop() {

	//if queue is empty print..
	if (first == NULL) {
		printf("\n***Queue is empty!\n");
	}

	//if there is only one, set first null
	else if (first->next == NULL) {
		free(first);
		first = NULL;
	}

	//set new last and free the other
	else {
		last = last->prev;
		free(last->next);
		last->next = NULL;
	}

	LIST_SIZE--;
}

void PushBeg(char data) {
	node* temp = (node*)malloc(sizeof(node));

	temp->data = data;
	temp->prev = NULL;

	if (first == NULL) {
		first = temp;
		temp->next = NULL;
	}
	
	else {
		temp->next = first;
		first->prev = temp;
		first = temp;
	}
	
	LIST_SIZE++;
}

void PopBeg() {
	if (first == NULL) {
		printf("\n***Queue is empty!\n");
	}

	else if (first->next == NULL) {
		free(first);
		first = NULL;
	}

	else {
		first = first->next;
		free(first->prev);
		first->prev = NULL;
	}

	LIST_SIZE--;
}

void Insert(int data, int place) {
	//Create a `temp` node to add, and a `walk` pointer to walk on the list
	node* temp = (node*)malloc(sizeof(node));
	node* walk = first;

	temp->data = data;

	if (place == 1) {
		first->prev = temp;
		temp->next = first;
		temp->prev = NULL;
		first = temp;
	}

	//I dont think I can explain this with writing, but I can show it perfectly on the paper
	else {
		for (int i = 2; i < place; i++) {
			walk = walk->next;
		}

		temp->next = walk->next;
		temp->prev = walk;
		walk->next->prev = temp;
		walk->next = temp;
	}

	LIST_SIZE++;
}

void Delete(int place) {

	if (place == 1) {
		//if there is only 1 node
		if (first->next == NULL) {
			free(first);
			first = NULL;
		}

		//if there is more than 1 node
		else {
			first = first->next;
			free(first->prev);
			first->prev = NULL;
		}
	}

	else {
		node* walk = first;

		//walk to specified node
		int i = 1;
		while (i < place) {
			walk = walk->next;
			i++;
		}

		//deleting the last node
		if (walk == last) {
			last = last->prev;
			free(last->next);
			last->next = NULL;
		}

		//deleting a node between last and first
		else {
			walk->next->prev = walk->prev;
			walk->prev->next = walk->next;
			free(walk);
		}
	}

	LIST_SIZE--;
}

void Display() {
	node* walk = first;

	printf("\n\n\n    Queue:\n");

	while (walk != NULL) {
		printf("%c", walk->data);
		walk = walk->next;
	}
	printf("\n\n");
}

void DisplaySteps(int step) {
	node* walk = first;

	printf("\nStep %d: ", step);

	while (walk != NULL) {
		printf("%c", walk->data);
		walk = walk->next;
	}
	printf("\n\n");
}
 
void Control() {

	printf("\n\n");

	//start from step 1 and each time last and first is equal, pop them out!
	int step = 1;
	while (LIST_SIZE > 1 && first->data==last->data) {
		Pop();
		PopBeg();
		DisplaySteps(step);
		step++;
	}

	//in the end, if there is no char left, or only 1 left, print palindrome
	if (first == NULL || LIST_SIZE < 3 && first->data == last->data) {
		printf("***This is a palindrome!\n");
	}

	//if there is any char left except for none or only one, print NOT palindrome
	else {
		printf("This is NOT a palindrome\n");
	}
}

void UI_Menu() {
	printf("\n\n\n                   MENU\n");
	printf("***********************************************\n1-Push\n2-Pop\n3-PushBeg\n4-PopBeg\n5-Insert\n6-Delete\n7-Control\n0-Exit\n");
}

void UI_Title(){
	printf("===============================================\n");
	printf("=             Palindrome Editor               =\n");
	printf("===============================================\n\n");
}

int CheckSize(int place) {
	if (place > LIST_SIZE) {
		printf("\n\n*****The %d. node does not exist.\n\n", place);
		return 0;
	}
	
	else {
		return 1;
	}
}

void ReadFile() {
	//open the file and initialise space for data
	FILE* fPtr = fopen("palindrome.txt", "r");
	char singleLine[3];	//`a\n`

	//read the file and push the first character `a`\n
	while (!feof(fPtr)) {
		fgets(singleLine, 3, fPtr);
		Push(*singleLine);
	}

	fclose(fPtr);
}
	