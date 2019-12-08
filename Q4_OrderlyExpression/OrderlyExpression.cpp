#include <iostream>
#include <string>
using namespace std;

typedef struct Node {
	char data;
	struct Node* next;
	struct Node* prev;
}node;

class OrderlyExpression {
private:
//some evil global variables
	node* first = NULL, * last = NULL;
	int LIST_SIZE = 0;
	string str; //entered string
	char* strCopy = new char[30];	//dynamic allocation for string
	int len = 0;	//lenght of the string
	int C1 = 0, C2 = 0;	//coefficients
	int quantity1 = 0, quantity2 = 0;	//quantities of a and b (aaabb -> a becomes quantity1)

public:
	//main funcs
	void GetStr() {
		cout << "Enter string: ";
		cin >> str;

		PrepareStr();
		CreateList();
		Display();
	}

	void GetCoefficients() {
		//if list starts with a, set C1 as belongs to a
		if (first->data == 'a') {
			cout << "\nC1 for a's: ";
			cin >> C1;
			cout << "\nC2 for b's: ";
			cin >> C2;
			}
		//if list starts with b, set C1 as belongs to b
		else {
			cout << "\nC1 for b's: ";
			cin >> C1;
			cout << "\nC2 for a's: ";
			cin >> C2;
			}
		}

	void Control() {
		int i;
		int step = 0;
		
		//Get the current quantities of characters
		CharQuantity();

		//then pop from the first and last respectively their coefficients
		while (first != NULL && (quantity1>=C1 && quantity2>=C2)) {

			for (i = 0; i < C1; i++) {
				PopBeg();
			}

			for (i = 0; i < C2; i++) {
				PopEnd();
			}

			DisplaySteps(&step);
		}

		//If there are any character left, it means the list is NOT ordered
		if (LIST_SIZE > 0) {
			cout << "This string is NOT ordered.\n\n" << endl;
		}

		//If there are no character left, it is ordered
		else {
			cout << "This string is ordered.\n\n" << endl;
		}

		DeleteList();

		quantity1 = 0;
		quantity2 = 0;
	}

	void Menu() {
		int option = 0;

		while (1) {
			cout << "\n\n1-Enter string\n2-Enter coefficients\n3-Control\n0-Exit\n\n";
			cin >> option;
			switch (option) {
			case 1:	GetStr();	break;
			case 2:	GetCoefficients();	break;
			case 3: Control();	break;
			case 0:	exit(0);	break;
			}
		}
	}

	//side funcs
	void PrepareStr() {
		//Get it's length and copy to a dynamic global array
		len = str.length();
		strcpy_s(strCopy, sizeof(str), str.c_str());
	}

	void CreateList() {
		int i = 0;

		//add each element of the copied array
		while (i < len) {
			Add(strCopy[i]);
			i++;
		}
	}

	void Add(char data) {
		node* temp = new node;
		temp->data = data;

		if (first == NULL) {
			first = temp;
			temp->next = NULL;
			temp->prev = NULL;
			last = first;
		}

		else {
			last->next = temp;
			temp->prev = last;
			temp->next = NULL;
			last = last->next;
		}

		LIST_SIZE++;
	}

	void Display() {
		if (first != NULL) {
			//create a walk pointer and start from first
			node* walk = first;

			//print Queue: (characters will be printed here)
			cout << "Queue: ";
			while (walk != NULL) {
				cout << walk->data;
				walk = walk->next;
			}
			cout << "\n\n" << endl;
		}

		//If there are no characters, print none
		else {
			cout << "Queue: N/A" << endl;
		}
	}

	void DisplaySteps(int* step) {
		if (first != NULL) {
			//create a walk pointer and start from first
			node* walk = first;

			//everytime control loop is executed, increase the step
			(*step)++;

			//print the new queue
			cout << "Step "<< *step <<": ";
			while (walk != NULL) {
				cout << walk->data;
				walk = walk->next;
			}
			cout << "\n\n" << endl;
		}

		//in the last step, print N/A
		else {
			(*step)++;
			cout << "Step " << *step << ": N/A\n\n" << endl;
		}
	}

	void PopBeg() {
		if (first->next == NULL) {
			free(first);
			first = NULL;
			last = first;
		}

		else {
			first = first->next;
			free(first->prev);
			first->prev = NULL;
		}

		LIST_SIZE--;
		quantity1--;
	}

	void PopEnd() {
		if (last->prev == NULL) {
			free(last);
			last = NULL;
			first = last;
		}

		else {
			last = last->prev;
			free(last->next);
			last->next = NULL;
		}
		
		LIST_SIZE--;
		quantity2--;
	}

	void DeleteList() {
		//deletes the whole list
		while (LIST_SIZE > 0) {
			PopBeg();
		}
	}

	void CharQuantity() {
		//find the quantities
		node* walk = first;

		while (walk != NULL) {

			if (walk->data == first->data) {
				quantity1++;
			}
			else {
				quantity2++;
			}

			walk = walk->next;
		}
	}

};



int main() {
	//initialise class
	OrderlyExpression Expression;

	Expression.Menu();


	return 0;
}