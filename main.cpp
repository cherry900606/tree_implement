#include <iostream>
using namespace std;

class binarySearchTree
{
public:
	binarySearchTree() { this->data = 0; this->left = NULL; this->right = NULL; }
	binarySearchTree(int n) { this->data = n; this->left = NULL; this->right = NULL; }
	binarySearchTree* max();
	void insert(int key);
	binarySearchTree* search(int key);
	void Delete(binarySearchTree *&tree,int key);
	friend int height(binarySearchTree*);
	friend int totalNodes(binarySearchTree*);
	friend int totalExternalNodes(binarySearchTree*);
	binarySearchTree* mirrorImage();

//private:
	int data;
	binarySearchTree *left, *right;
};
binarySearchTree* binarySearchTree::mirrorImage()
{
	if (this == NULL)
		return this;
	(this->left)->mirrorImage();
	(this->right)->mirrorImage();
	binarySearchTree *temp = this->left;
	this->left = this->right;
	this->right = temp;
	return temp;
}
int totalExternalNodes(binarySearchTree *tree)
{
	if (tree == NULL)
		return 0;
	else if (tree->left == NULL && tree->right == NULL)
		return 1;
	else
		return totalExternalNodes(tree->left) + totalExternalNodes(tree->right);
}
int totalNodes(binarySearchTree *tree)
{
	if (tree == NULL)
		return 0;
	else
		return totalNodes(tree->left) + totalNodes(tree->right) + 1;
}
int height(binarySearchTree* tree)
{
	if (tree == NULL)
		return 0;
	else
	{
		int leftHeight = height(tree->left);
		int rightHeight = height(tree->right);
		if (leftHeight > rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;
	}
}
binarySearchTree* binarySearchTree::max()
{
	if (this->right == NULL)
		return this;
	return (this->right)->max();
}
void binarySearchTree::Delete(binarySearchTree *&tree, int key)
{
	if (tree == NULL)
		cout << "this element not found in the tree" << endl;
	else if (key < tree->data)
		Delete(tree->left, key);
	else if (key > tree->data)
		Delete(tree->right, key);
	else if (tree->right != NULL && tree->left != NULL)
	{
		binarySearchTree *temp = (tree->left)->max();
		tree->data = temp->data;
		Delete(tree->left, temp->data);
	}
	else
	{
		binarySearchTree *temp = tree;
		if (tree->left == NULL && tree->right == NULL)
			tree = NULL;
		else if (tree->left != NULL)
			tree = tree->left;
		else
			tree = tree->right;
		free(temp);
	}
}
binarySearchTree* binarySearchTree::search(int key)
{
	if (this == NULL || this->data == key)
		return this;
	else
	{
		if (key < this->data)
			return (this->left)->search(key);
		else
			return (this->right)->search(key);
	}
}
void binarySearchTree::insert(int key)
{
	if (key > this->data)
	{
		if (this->right == NULL)
		{
			binarySearchTree *temp = new binarySearchTree(key);
			temp->left = temp->right = NULL;
			this->right = temp;
		}
		else
			(this->right)->insert(key);
	}
	else if (key < this->data)
	{
		if (this->left == NULL)
		{
			binarySearchTree *temp = new binarySearchTree(key);
			temp->left = temp->right = NULL;
			this->left = temp;
		}
		else
			(this->left)->insert(key);
	}
}
int main()
{
	binarySearchTree *tree = new binarySearchTree(10);
	tree->insert(7);
	tree->insert(12);
	tree->insert(20);
	tree->insert(11);
	tree->insert(9);

	cout << height(tree) << endl;
	cout << totalNodes(tree) << endl;
	cout << totalExternalNodes(tree) << endl;

	return 0;
}
