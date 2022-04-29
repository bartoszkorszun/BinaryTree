#include <windows.h>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

// CREATING A NODE
struct node {
	int key;
	struct node *left;
	struct node *right;
	struct node *parent;
};

//POINTER TO ROOT
struct node *root = NULL;

//ADDING A NODE 
void add_node(int value) {
	
	//CREATING POINTERS TO CURRENTLY CONSIDERED NODE AND NEW NODE
	struct node *current = root;
	struct node *newNode = new node;
	
	//ASSIGNING VALUES TO NODE
	newNode -> key = value;
	newNode -> left = NULL;
	newNode -> right = NULL;
	
	//IF ROOT IS EQUAL TO NULL THEN NODE BECOMES THE ROOT
	if (root == NULL) {
		newNode -> parent = NULL;
		root = newNode;
		return;
	}
	else {
 
		while (current != NULL) {
			
			//VALUE OF NEW NODE IS BIGGER OR EQUAL THAN CURRENT ONE
			if (current -> key <= newNode -> key) {
				
				//IF THERE IS FREE SPACE ON THE RIGHT SIDE, ADD NODE
				if (current -> right == NULL) {
					newNode -> parent = current;
					current -> right = newNode;
					return;
				}
				//ELSE, GO DEEPER
				else {
					current = current -> right;
				}
			}
			
			//VALUE OF NEW NODE IS SMALLER THAN CURRENT ONE
			if (current -> key > newNode -> key) {
				
				//IF THERE IS FREE SPACE ON THE LEFT SIDE, ADD NODE
				if (current -> left == NULL) {
					newNode -> parent = current;
					current -> left = newNode;
					return;
				} 
				//ELSE, GO DEEPER
				else {
					current = current -> left;
				}
			}
		}
	}
}

//DELETING A NODE
struct node* delete_node_key(struct node* node, int find) {
 
	if (node == NULL) 
		return node;
 
	if (find < node -> key) {
		return node -> left = delete_node_key(node -> left, find);
	}
 
	else if (find > node -> key) {
		return node -> right = delete_node_key(node -> right, find);
	}
 
	if (find == node -> key) {
		
		//IF BST CONTAINS ONLY ROOT
		if (root -> left == NULL && root -> right == NULL) {
			delete(root);
			root = NULL;
			return NULL;
		}
		
		//INSERTING RIGHT CHILD TO THE CURRENTLY POINTED ONE
		if (node -> left == NULL) {								
			struct node *tmp = node -> right;
			delete(node);
			return tmp;
		}
		//INSERTING LEFT CHILD TO THE CURRENTLY POINTED ONE
		else if (node -> right == NULL) {
			struct node *tmp = node -> left;
			delete(node);
			return tmp;
		}
 
		//CASE WHERE NODE HAS TWO CHILDREN	
		struct node* tmp = node -> right;							
 
		node -> key = tmp -> key;
		while (tmp -> left != NULL) {
			tmp = tmp -> left;
		}
 
		//FINDING A FOLLOW-UP
		node -> right = delete_node_key(node -> right, tmp -> key);		
	}
	return node;
}

//CREATING RANDOM ARRAY
int *new_array(int length){
	int *array = (int*) calloc(length, sizeof(int));
	if(!array){
		cerr << "|error| new_array: could allocate memory!\n";
		exit(1);
	}
	return array;
}

int *generate_random_array(int length) {
	int *array = new_array(length);
	int range = 1000000;
	for (int i = 0; i < length; i++){
		array[i] = rand() % range;
	}
	return array;
}

//SEARCHING FOR THE BIGGEST VALUE IN TREE (RIGHT EDGE NODE)
int find_max() {
	DWORD start, stop;
	struct node *current = root;
	start = GetTickCount();
	while (current -> right != NULL) {
		current = current -> right;
	}
	stop = GetTickCount() - start;
	cout << "Execution time: " << stop << "ms" << endl;
	return current -> key;
}

//SEARCHING FOR THE SMALLEST VALUE IN TREE (LEFT EDGE NODE)
int find_min() {
	DWORD start, stop;
	struct node *current = root;
	start = GetTickCount();
	while (current -> left != NULL) {
		current = current -> left;
	}
	stop = GetTickCount() - start;
	cout << "Execution time: " << stop << "ms" << endl;
	return current -> key;
}

//FINDING HEIGHT OF THE TREE
int find_height(node* node) {
	
	if (node == NULL){
		return 0;
	}else{
		int left_height = find_height(node -> left);
		int right_height = find_height(node -> right);
		
		if (left_height > right_height){
			return(left_height + 1);
		}else{
			return(right_height + 1);
		}
	}
}

//A FUNCTION THAT STORE NODES POINTERS IN VECTOR IN ORDER
void storeNodes(node* avlRoot, vector<node*> &nodes) {
	
	if (avlRoot == NULL){
		return;
	}
	storeNodes(avlRoot -> left, nodes);
	nodes.push_back(avlRoot);
	storeNodes(avlRoot -> right, nodes);
}

bool ifRoot;
node* buildTreeUtil(vector<node*> &nodes, int start, int end) {
	
	if (start > end){
		return NULL;
	}
	
	int mid = (start + end) / 2;
	node *newNode = nodes[mid];
	
	if(ifRoot){
		root = newNode;
		ifRoot = false;
	}
	
	newNode -> left = buildTreeUtil(nodes, start, mid-1);
	newNode -> right = buildTreeUtil(nodes, mid+1, end);
	
	return newNode;
}

//CONVERTING BST INTO AVL
node* build_AVL(node* avl){
	
	ifRoot = true;
	
	vector<node *> nodes;
	storeNodes(avl, nodes);
	
	int n = nodes.size();
	return buildTreeUtil(nodes, 0, n-1);
}

//SEARCHING NODE
bool searchNode(struct node* search, int data) {
	
	if(search == NULL){
		return false;
	}
	if(search -> key == data){
		return true;
	}
	
	bool left = searchNode(search -> left, data);
	if(left) return true;
	
	bool right = searchNode(search -> right, data);
	
	return right;
}

//DELETING WHOLE TREE
void deleteTree(node* node) {
	
	if(node == NULL)
		return;
	
	deleteTree(node -> left);
	deleteTree(node -> right);
	
	delete node;
}

int main(){
	
	bool isRunning = true;
	int answear, input, length, search;
	
	while(isRunning) {
		system("cls");
		cout << endl;
		
		cout << "------------------------------------" << endl;
		cout << "[0] Add node" << endl;
		cout << "[1] Delete node" << endl;
		cout << "[2] Add random array to the tree" << endl;
		cout << "[3] Find the smallest value" << endl;
		cout << "[4] Find the biggest value" << endl;
		cout << "[5] Show height of the tree" << endl;
		cout << "[6] Transform BST tree to a AVL tree" << endl;
		cout << "[7] Searching if node exists" << endl;
		cout << "[8] Delete whole tree" << endl;
		cout << "[9] Exit" << endl;
		cout << "------------------------------------" << endl;
		
		cin >> answear;
		cout << endl;
		
		switch(answear) {
			case 0: {
				cout << "Insert value to add: ";
				cin >> input;
				add_node(input);
				cout << input << " has been added to the tree" << endl;
				system("PAUSE");
				break;
			}
			case 1: {
				if (root == NULL) {
					cout << "There is no root - the tree is empty :(" << endl;
				}
				else{
					cout << "Insert value to delete: ";
					cin >> input;
					delete_node_key(root, input);
					cout << input << " has been removed from the tree" << endl;
				}	
				system("PAUSE");
				break;
			}
			case 2: {
				cout << "Insert length of array" << endl;
				cin >> length;
				int *array = generate_random_array(length);
				for (int i=0; i<length; i++){
					add_node(array[i]);
				}
				system("PAUSE");
				break;
			}
			case 3: {
				if(root == NULL)
					cout << "There is no root - the tree is empty :(" << endl;
				else
					cout << "Smallest value = " << find_min() << endl;
				system("PAUSE");
				break;
			}
			case 4: {
				if(root == NULL)
					cout << "There is no root - the tree is empty :(" << endl;
				else
					cout << "Biggest value = " << find_max() << endl;
				system("PAUSE");
				break;
			}
			case 5: {
				if (root == NULL) {
					cout << "There is no root - the tree is empty :(" << endl;
				}else{
					cout << "Hight of the tree: " << find_height(root) << endl;
				}
				system("PAUSE");
				break;
			}
			case 6: {
				if (root == NULL) {
					cout << "There is no root - the tree is empty :(" << endl;
				}else{
					build_AVL(root);
					cout << "BST converted to AVL :)" << endl;
				}
				system("PAUSE");
				break;
			}
			case 7: {
				if(root == NULL)
					cout << "There is no root - the tree is empty :(" << endl;
				else{
					DWORD start, stop;
					cout << "Insert searching value" << endl;
					cin >> search;
					start = GetTickCount();
					if(searchNode(root, search))
						cout << "There is node with value: " << search << endl;
					else
						cout << "There is no such node" << endl;
					stop = GetTickCount() - start;
					cout << "Execution time: " << stop << "ms" << endl;
				}
				system("PAUSE");
				break;
			}
			case 8: {
				if (root == NULL) {
					cout << "There is no root - the tree is empty :(" << endl;
				}else{
					deleteTree(root);
					root = NULL;
					cout << "Tree deleted" << endl;
				}
				system("PAUSE");
				break;
			}
			case 9: {
				isRunning = false;
				break;
			}
			//MEASUREMENTS FOR UNIVERSITY PROJECT
			case 420: {
				for(int i=0; i<12; i++){
					switch(i){
						case 0: {
							int length = 10;
							int *array = generate_random_array(length);
							for (int j=0; j<length; j++) {
								add_node(array[j]);
							}
							cout << "Length: " << length << " | BST Height: " << find_height(root);
							build_AVL(root);
							cout << " | AVL Height: " << find_height(root) << endl;
							deleteTree(root);
							root = NULL;
							break;
						}
						case 1: {
							int length = 50;
							int *array = generate_random_array(length);
							for (int j=0; j<length; j++) {
								add_node(array[j]);
							}
							cout << "Length: " << length << " | BST Height: " << find_height(root);
							build_AVL(root);
							cout << " | AVL Height: " << find_height(root) << endl;
							deleteTree(root);
							root = NULL;
							break;
						}
						case 2: {
							int length = 100;
							int *array = generate_random_array(length);
							for (int j=0; j<length; j++) {
								add_node(array[j]);
							}
							cout << "Length: " << length << " | BST Height: " << find_height(root);
							build_AVL(root);
							cout << " | AVL Height: " << find_height(root) << endl;
							deleteTree(root);
							root = NULL;
							break;
						}
						case 3: {
							int length = 500;
							int *array = generate_random_array(length);
							for (int j=0; j<length; j++) {
								add_node(array[j]);
							}
							cout << "Length: " << length << " | BST Height: " << find_height(root);
							build_AVL(root);
							cout << " | AVL Height: " << find_height(root) << endl;
							deleteTree(root);
							root = NULL;
							break;
						}
						case 4: {
							int length = 1000;
							int *array = generate_random_array(length);
							for (int j=0; j<length; j++) {
								add_node(array[j]);
							}
							cout << "Length: " << length << " | BST Height: " << find_height(root);
							build_AVL(root);
							cout << " | AVL Height: " << find_height(root) << endl;
							deleteTree(root);
							root = NULL;
							break;
						}
						case 5: {
							int length = 5000;
							int *array = generate_random_array(length);
							for (int j=0; j<length; j++) {
								add_node(array[j]);
							}
							cout << "Length: " << length << " | BST Height: " << find_height(root);
							build_AVL(root);
							cout << " | AVL Height: " << find_height(root) << endl;
							deleteTree(root);
							root = NULL;
							break;
						}
						case 6: {
							int length = 10000;
							int *array = generate_random_array(length);
							for (int j=0; j<length; j++) {
								add_node(array[j]);
							}
							cout << "Length: " << length << " | BST Height: " << find_height(root);
							build_AVL(root);
							cout << " | AVL Height: " << find_height(root) << endl;
							deleteTree(root);
							root = NULL;
							break;
						}
						case 7: {
							int length = 50000;
							int *array = generate_random_array(length);
							for (int j=0; j<length; j++) {
								add_node(array[j]);
							}
							cout << "Length: " << length << " | BST Height: " << find_height(root);
							build_AVL(root);
							cout << " | AVL Height: " << find_height(root) << endl;
							deleteTree(root);
							root = NULL;
							break;
						}
						case 8: {
							int length = 100000;
							int *array = generate_random_array(length);
							for (int j=0; j<length; j++) {
								add_node(array[j]);
							}
							cout << "Length: " << length << " | BST Height: " << find_height(root);
							build_AVL(root);
							cout << " | AVL Height: " << find_height(root) << endl;
							deleteTree(root);
							root = NULL;
							break;
						}
						case 9: {
							int length = 500000;
							int *array = generate_random_array(length);
							for (int j=0; j<length; j++) {
								add_node(array[j]);
							}
							cout << "Length: " << length << " | BST Height: " << find_height(root);
							build_AVL(root);
							cout << " | AVL Height: " << find_height(root) << endl;
							deleteTree(root);
							root = NULL;
							break;
						}
						case 10: {
							int length = 1000000;
							int *array = generate_random_array(length);
							for (int j=0; j<length; j++) {
								add_node(array[j]);
							}
							cout << "Length: " << length << " | BST Height: " << find_height(root);
							build_AVL(root);
							cout << " | AVL Height: " << find_height(root) << endl;
							deleteTree(root);
							root = NULL;
							break;
						}
						case 11: {
							int length = 2000000;
							int *array = generate_random_array(length);
							for (int j=0; j<length; j++) {
								add_node(array[j]);
							}
							cout << "Length: " << length << " | BST Height: " << find_height(root);
							build_AVL(root);
							cout << " | AVL Height: " << find_height(root) << endl;
							deleteTree(root);
							root = NULL;
							break;
						}
					}
				}
				system("PAUSE");
				break;
			}
			default: {
				cout << "Wrong choice!" << endl;
				system("PAUSE");
				break;
			}
		}
	}
		
	return 0;
}
