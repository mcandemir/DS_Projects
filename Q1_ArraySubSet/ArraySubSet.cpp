#include <iostream>
#include <cstring>
using namespace std;

class ArraySubnet {
private:
	int PurgedArray[50];	//A purged SubSet (purged from duplicates)
	int PurgedSize = 0;	//size of the purged SubSet

public: 
	int Array1[100];
	int Array2[100];
	int Arr1_Size = 0;
	int Arr2_Size = 0;


	//main funcs
	void AdjustMainArray() {
		int N, i;
		cout << "Number of elements: ";
		cin >> N;


		//set array size to 0 for new adjustment
		Arr1_Size = 0;

		for (i = 0; i < N; i++) {
			cin >> Array1[i];
			Arr1_Size++;
		}

		//sort the given array
		BSort(Array1, Arr1_Size);
	}


	void AdjustSubArray() {
		int N, i;
		cout << "Number of elements: ";
		cin >> N;

		//set array size to 0 for new adjustment
		Arr2_Size = 0;

		for (i = 0; i < N; i++) {
			cin >> Array2[i];
			Arr2_Size++;
		}

		//sort the given array
		BSort(Array2, Arr2_Size);
	}


	void CheckSubSet() {
		int i, j;

		//check each element of the both arrays, if an element is same, purge and continue traveling the array
		for (i = 0; i < Arr1_Size; i++) {

			for (j = 0; j < Arr2_Size; j++) {

				if (Array1[i] == Array2[j])
					Purge(Array1[i]);
			}
		}

		//if number of same elements are equal to array2's size
		if (PurgedSize == PurgedSizeOfArr2()) {
			cout << "\n\n\n\n***Array2 is a sub-set!***" << endl;
		}

		else {
			cout << "\n\n\n\n***Array 2 is NOT a subset***" << endl;
		}
	}


	void DisplayArrays() {
		int i, j;
		cout << "\n\n\n\n\n\n";
		//display array1
		cout << "Array1 = [";

		if (Arr1_Size != 0) {
			for (i = 0; i < Arr1_Size - 1; i++)
				cout << Array1[i] << ",";
			cout << Array1[i];
		}

		cout << "]\t |\t";


		//display array2
		cout << "Array2 = [";

		if (Arr2_Size != 0) {
			for (i = 0; i < Arr2_Size - 1; i++)
				cout << Array2[i] << ",";
			cout << Array2[i];
		}

		cout << "]\n\n";
	}

	void Clear() {
		Arr1_Size = 0;
		Arr2_Size = 0;
	}

	//sidefuncs
	void Menu() {
		int option = 0;
		
		DisplayArrays();

		cout << "1-Adjust main-set.\n" << "2-Adjust sub-set\n" << "3-Check SubSet\n" <<"4-Clear sets\n"<< "0-Exit\n\n\n" << endl;
		cin >> option;

		switch (option) {
		case 1:	AdjustMainArray();	break;
		case 2:	AdjustSubArray();	break;
		case 3:	CheckSubSet();	break;
		case 4:	Clear();	break;
		case 0:	exit(0);
		}
	}

	void BSort(int Arr[], int n) {
		int i, j;
		for (int i = 0; i < n - 1; i++) {

			for (j = 0; j < n - i - 1; j++) {

				if (Arr[j] > Arr[j + 1]) {
					Swap(&Arr[j], &Arr[j + 1]);
				}
			}
		}
	}

	void Swap(int *x,int *y) {
		int temp = *x;
		*x = *y;
		*y = temp;
	}

	void Purge(int x) {

		//Create a purged SubSet
		if (Arr2_Size != 0) {
			//initialise var.
			bool fit = true;
			int i = 0;

			if (PurgedSize != 0) {
				//check if fits
				while (i < PurgedSize) {
					if (PurgedArray[i] == x) {
						fit = false;
					}
					i++;
				}
			}

			//if fit is true add it and increase size
			if (fit == true) {
				PurgedArray[PurgedSize] = x;
				PurgedSize++;
			}
		}
	}

	int PurgedSizeOfArr2() {
		int i, j;
		int rem = 1;	//size of purged array

		//count the elements without duplicates
		for (i = 1; i < Arr2_Size; i++) {
			for (j = 0; j < Arr2_Size; j++) {
				if (Array2[i] == Array2[j])
					break;
			}

			if (i == j) {
				rem++;
			}
		}

		//return the size without duplicates
		return rem;
	}
};


int main() {
	ArraySubnet Sets;

	while (1) {
		Sets.Menu();
	}
}
