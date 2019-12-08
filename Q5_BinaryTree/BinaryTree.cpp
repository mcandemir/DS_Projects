#include <iostream>
using namespace std;

typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
}node;

node* root = NULL;

class BinaryTree {
public:
	void Add(int data) {
		//Create the temp node
		node* temp = new node;
		temp->data = data;
		temp->left = NULL;
		temp->right = NULL;
		
		//If root is empty, assign to root
		if (root == NULL) {
			root = temp;
		}

		//If root is not empty, then search for a fit place
		else {
			Travel(temp);
		}
		
	}

	void Travel(node*temp) {
		//create a `walk` pointer to walk the tree
		node* walk = root;

		while (1) {
			//if temp'data is bigger than walk's data, go right node until its empty. If the right is empty, assign the temp to right
			if (temp->data > walk->data) {
				if (walk->right == NULL) {
					walk->right = temp;
					break;
				}
				walk = walk->right;
			}

			//if temp'data is lesser than walk's data, go left node until its empty. If the left is empty, assign the temp to left
			else {
				if (walk->left == NULL) {
					walk->left = temp;
					break;
				}
				walk = walk->left;
			}
		}
	}

	void Show(node *walk) {
		//until walk is empty, recursively print all the data and start from left & right leaves.
		if (walk == NULL)
			return;
		Show(walk->left);
		Show(walk->right);
		cout << "-->" << walk->data << endl;
	}
};

int main() {
	BinaryTree BT;

	int option = 0;
	int data = 0;

	while (1) {
		cout << "\n\n1-Add\n2-Show\n" << endl;
		cin >> option;
		switch (option) {
		case 1:	cout << "Enter data: ";
			cin >> data;
			BT.Add(data);	break;
		case 2:	node * walk = root;
			BT.Show(walk);	break;
		}

	}
}