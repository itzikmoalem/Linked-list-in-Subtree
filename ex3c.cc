/*File: ex3c.cc
===============================================================================
Binary Trees - Bereaved Tree

This Program search the depth of father with one kid.
the program print the data that include in the same tree.

Name: Itzik Moalem | ID: 313181638 | Login:itzikmo
=============================================================================*/
//-----------------------------Includes----------------------------------------
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <new>
//---------------------------- Using-------------------------------------------
using std::cin;
using std::cout;
using std::endl;
using std::nothrow;
using std::cerr;
//-----------------------------Structs-----------------------------------------
struct Node{
	int _data;
	struct Node *_left, *_right;
};
//------------------------------Protptype--------------------------------------
void build_bst (struct Node *&root);
void insert_into_bst (struct Node *new_node , struct Node *&root);
void free_tree(struct Node *root);
void result (struct Node *root, int &counter, int &count, int &keep_data);
bool one_kid (struct Node* root);
//------------------------------Main-------------------------------------------
int main () 
{
	struct Node *root = NULL;
	int counter = 0, count = 0 ,keep_data =0;

	build_bst (root); 
    result (root, counter, count, keep_data);
    cout << keep_data << endl;
	free_tree(root);

return EXIT_SUCCESS; 
} 
//-----------------------------Functions---------------------------------------
//-------------------------------Build Bst-------------------------------------
void build_bst (struct Node *&root) 
{	
	int num; 
	cin >> num;
	while (!cin.eof())
	{	
		struct Node *new_node = new (nothrow) struct Node; //new box
		if (new_node == NULL)			//check for failure
		{
			cerr << "cannot allocate memory \n";
			exit (EXIT_FAILURE); 
		}
		new_node -> _data = num;		//cin the number
		new_node -> _left = new_node -> _right = NULL;
		insert_into_bst(new_node , root); 
		cin >> num;
	}
}
//------------------------------Insert Into Bst--------------------------------
void insert_into_bst (struct Node *new_node ,struct Node *&root)
{	
	if (root == NULL)								//is new cross section
		root = new_node;
	else if (root -> _data >= new_node -> _data)	//put in the left side 	
		insert_into_bst(new_node , root -> _left);
	else											//put in the right side	
		insert_into_bst(new_node , root -> _right);
}
//---------------------------------Free Tree-----------------------------------
void free_tree(struct Node * root) 
{
    if (root != NULL) {
        free_tree(root->_left);
        free_tree(root->_right);
        delete root;
    }
}
//-----------------------------------Result------------------------------------
void result (struct Node *root, int &counter, int &count, int &keep_data)
{
    if (root == NULL)
        return;

    if (one_kid (root)) //if there is one kid
        ++counter;

    else if (root->_right != NULL && root->_left != NULL) //cross!
        counter = 0;
    
    result (root->_left, counter, count, keep_data);   //left side

    if ((counter > count) && (root->_right != NULL && root->_left != NULL))
    {   //if you back to the cross
        count = counter+1;  //amount
        keep_data = root->_left->_data; //keep
        counter = 0;
    }

    result (root->_right, counter, count, keep_data);  //right side

    if ((counter > count) && (root->_right != NULL && root->_left != NULL))
    {
        count = counter+1;  //amount
        keep_data = root->_right->_data; //keep
        counter = 0;    //restart counter
    }
}
//---------------------------------Check Kids----------------------------------
bool one_kid (struct Node* root)
{
    if ((root->_left == NULL && root->_right != NULL) ||
        (root->_left != NULL && root->_right == NULL))  //only one kid
        return true;

    return false;
}