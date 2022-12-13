#include "Matrix.h"
#include <exception>
using namespace std;

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
Matrix::Matrix(int nrLines, int nrCols) {
	this->root = NULL;
	this->lines = nrLines;
	this->columns = nrCols;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
int Matrix::nrLines() const {
	return this->lines;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
int Matrix::nrColumns() const {
	return this->columns;
}

// complexity 
// Best Case =  theta(1), element is the root
// Worst Case = Average Case = theta(n), element is the last node in the degenerated tree
// Overall complexity = O(n)
TElem Matrix::element(int i, int j) const {

	if (i < 0 || i >= this->lines || j < 0 || j >= this->columns)  // invalid indexes
		throw exception();

	BSTNode* currentNode = this->root;
	bool found = false;

	while (currentNode != NULL && !found) 
	{
		if (currentNode->elem.line == i && currentNode->elem.column == j)
			found = true;
		else 
		{
			if (currentNode->elem.line < i)
				currentNode = currentNode->right;
			else 
				if (currentNode->elem.line > i)
					currentNode = currentNode->left;
				else 
				{
					if (currentNode->elem.column < j)
						currentNode = currentNode->right;
					else
						currentNode = currentNode->left;
				}
		}
	}

	if (found)
		return currentNode->elem.value;
	return NULL_TELEM;
}

// complexity 
// Best Case =  theta(1), element is the root
// Worst Case = Average Case = theta(n), element is the last node in the degenerated tree
// Overall complexity = O(n)
TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= this->lines || j < 0 || j >= this->columns)  // invalid indexes
		throw exception();

	if (this->root == NULL) 
	{
		this->root = initNode(i, j, e);
		return NULL_TELEM;
	}

	BSTNode* previousNode = NULL;
	BSTNode* currentNode = this->root;
	bool found = false;
	bool isRoot = false;

	while (currentNode != NULL && !found) 
	{
		if (currentNode->elem.line == i && currentNode->elem.column == j)
			found = true;
		else 
		{
			previousNode = currentNode;
			if (currentNode->elem.line < i)
				currentNode = currentNode->right;
			else 
				if (currentNode->elem.line > i)
					currentNode = currentNode->left;
				else 
				{
					if (currentNode->elem.column < j)
						currentNode = currentNode->right;
					else
						currentNode = currentNode->left;
				}
		}
	}

	if (currentNode == this->root)
		isRoot = true;

	if (found) 
	{
		TElem oldElement = currentNode->elem.value;

		if (e != NULL_TELEM)   // old element != NULL_TELEM, new element != NULL_TELEM
		{ 
			currentNode->elem.value = e;
			return oldElement;
		}
		else  // old element != NULL_TELEM, new element == NULL_TELEM
		{  
			if (currentNode->left == NULL && currentNode->right == NULL) 
			{	// we have 0 descendants
				if (previousNode != NULL) 
				{
					if (previousNode->left == currentNode)
						previousNode->left = NULL;
					else
						previousNode->right = NULL;
				}
				delete currentNode;

				if (isRoot)
					this->root = NULL;
				return oldElement;
			}

			if (currentNode->left != NULL && currentNode->right != NULL) 
			{  // we have 2 descendants
				BSTNode* min = currentNode->right;
				findMin(currentNode->right, min);

				if (isRoot) 
				{
					min->left = this->root->left;
					this->root = min;
				}
				else 
				{
					if (previousNode != NULL) 
					{
						if (previousNode->left == currentNode)
							previousNode->left = min;
						else
							previousNode->right = min;

						min->left = currentNode->left;
					}
				}
				delete currentNode;
				return oldElement;
			}
			if (isRoot) 
			{	// we have 1 descendant
				if (currentNode->left != NULL)
					this->root = currentNode->left;
				else
					this->root = currentNode->right;
			}
			else 
			{
				if (previousNode != NULL) 
				{
					if (previousNode->left == currentNode)
					{
						if (currentNode->left != NULL)
							previousNode->left = currentNode->left;
						else
							previousNode->left = currentNode->right;
					}
					else
						if (currentNode->left != NULL)
							previousNode->right = currentNode->left;
						else
							previousNode->right = currentNode->right;
				}
			}
			delete currentNode;
			return oldElement;
		}
	}
	else 
	{
		if (e == NULL_TELEM)   // old element == NULL_TELEM, new element == NULL_TELEM
			return NULL_TELEM;

		BSTNode* node = new BSTNode();  // old element == NULL_TELEM, new element != NULL_TELEM
		node = initNode(i, j, e);

		if (previousNode->elem.line < i)
			previousNode->right = node;
		else 
			if (previousNode->elem.line > i)
				previousNode->left = node;
			else 
			{
				if (previousNode->elem.column < j)
					previousNode->right = node;
				else
					previousNode->left = node;
			}
		return NULL_TELEM;
	}
}

// complexity 
// Best Case =  theta(l*logn), tree is balanced
// Worst Case = Average Case = theta(l*n), tree is degenerated
// Overall complexity = O(l*n), l = number of lines
void Matrix::setMainDiagonal(TElem elem) {

	if (this->lines != this->columns)  // square matrix
		throw exception();

	int i;
	for (i = 0; i < this->lines; i++)
		modify(i, i, elem);
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
BSTNode* Matrix::initNode(int i, int j, TElem e) {
	BSTNode* node = new BSTNode();
	node->elem.value = e;
	node->elem.line = i;
	node->elem.column = j;

	node->left = NULL;
	node->right = NULL;

	return node;
}

// complexity 
// Best Case =  theta(1), node has no left subtree
// Worst Case = Average Case = theta(n), all nodes of the left subtree are parsed
// Overall complexity = O(n), n = number of nodes in the left subtree
void Matrix::findMin(BSTNode* node, BSTNode* min) {
	BSTNode* currentNode = node;

	while (currentNode->left != NULL) 
		currentNode = currentNode->left;

	min = currentNode;
}