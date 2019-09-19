#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...

    return e(root);
}

double AbstractSyntaxTree::e(Node* subRoot) const {
	if(!subRoot)
		return 0;
	if(!(subRoot->left) && !(subRoot->right))
		return stod(subRoot->elem);

	double l = e(subRoot->left);
	double r = e(subRoot->right);

	if(subRoot->elem == "+")
		return l + r;
	if(subRoot->elem == "-")
		return l - r;
	if(subRoot->elem == "*")
		return l * r;
	return l/r;
}

