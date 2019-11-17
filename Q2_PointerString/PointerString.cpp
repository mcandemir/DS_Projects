#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class StringReverse {
private:
	int i, len;	//len is for size of allocated array for copied string
	string str;	//our entered string
	char* strCopy;	//first pointer of array

public:
	//get the string
	void GetStr() {
		cout << "\n\n\nEnter string: ";
		getline(cin, str);

		if (str == "q" || str=="Q")
			exit(0);
	}


	//get the length and allocate a dynamic memory for the array
	void PrepareStr() {
		len = str.length() + 1;
		strCopy = new char[len];
		strcpy_s(strCopy, sizeof(str), str.c_str());
	}


	//start from the last and keep moving
	void ReverseStr() {
		cout << "Reversed    : ";

		for (i = str.length(); i > 0; i--) {
			cout << strCopy[i - 1];
		}

		cout<<"\n\n\n";
	}
};

void main() {
	 StringReverse Reverse;

	 cout << "Enter q to exit" << endl;

	while (1) {
		Reverse.GetStr();
		Reverse.PrepareStr();
		Reverse.ReverseStr();
	}
}