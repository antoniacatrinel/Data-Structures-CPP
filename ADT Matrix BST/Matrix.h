#pragma once

typedef int TElem;
#define NULL_TELEM 0

class Triplet {
public:
	int line;
	int column;
	TElem value;

	Triplet() : line{ -1 }, column{ -1 }, value{ NULL_TELEM } {};
	Triplet(const int& line, const int& col, const TElem& elem) : line{ line }, column{ col }, value{ elem } {};
};

class BSTNode {
public:
	Triplet elem;
	BSTNode* left;
	BSTNode* right;
};

class Matrix {

private:
	BSTNode* root;
	int lines;
	int columns;

public:
	// constructor
	Matrix(int nrLines, int nrCols);

	// returns the number of lines
	int nrLines() const;

	// returns the number of columns
	int nrColumns() const;

	// returns the element from line i and column j (indexing starts from 0)
	// throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	// modifies the value from line i and column j
	// returns the previous value from the position
	// throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	// sets all the values from the main diagonal to the value elem
	// throws an exception if it is not a square matrix
	void setMainDiagonal(TElem elem);

	// initializes a new node at position (i, j) in matrix
	BSTNode* initNode(int i, int j, TElem e);

	// finds the minimum by going through the left subtree of the given node 
	void findMin(BSTNode* node, BSTNode* min);
};
