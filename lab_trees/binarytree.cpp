/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    //your code her
	mirror(root);
}

//helper function to the mirror public function
template <typename T>
void BinaryTree<T>::mirror(Node* &subRoot) {
	if(!subRoot)
		return;
	Node* temp = subRoot->left;
	subRoot->left = subRoot->right;
	subRoot->right = temp;

	mirror(subRoot->left);
	mirror(subRoot->right);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
	Node* min = NULL;
	stack<Node*> s;
	Node* current = getRoot();

	while(current != NULL || !s.empty()) {
		while(current != NULL) {
			s.push(current);
			current = current->left;
		}
		current = s.top();
		s.pop();
		if (min && min->elem > current->elem)
			return false;
		min = current;
		current = current->right;
	}
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
	return isOrderedR(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedR(Node* subRoot) const{
	if(!subRoot)
		return true;
	if(subRoot->left != NULL && (maxValLeft(subRoot->left) > subRoot->elem ))
		return false;
	if(subRoot->right != NULL && (minValRight(subRoot->right) < subRoot->elem ))
		return false;
	if(!isOrderedR(subRoot->left) || !isOrderedR(subRoot->right))
		return false;
	return true;
}

template <typename T>
T BinaryTree<T>::maxValLeft(Node* subRoot) const{
	return maxVal(subRoot)->elem;
}

template <typename T>
typename BinaryTree<T>::Node * BinaryTree<T>::maxVal(Node* n) const{
	if (!n)
		return NULL;
	Node *l = maxVal(n->left);
	Node *r = maxVal(n->right);
	if (r) {
		if (l) {
			Node *m = r->elem > l->elem ? r : l;
			return m->elem > n->elem ? m : n;
		}
		return r->elem > n->elem ? r : n;
	} else if (l) {
		return l->elem > n->elem ? l : n;
	}
	return n;
}


template <typename T>
T BinaryTree<T>::minValRight(Node* subRoot) const {
	return minVal(subRoot)->elem;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::minVal(Node* n) const {
	if(!n)
		return NULL;
	Node* l = minVal(n->left);
	Node* r = minVal(n->right);
	if(r) {
		if(l) {
			Node* m = r->elem < l->elem ? r : l;
			return m->elem < n->elem ? m : n;
		}
		return r->elem < n->elem ? r : n;
	} else if(l) {
		return l->elem < n->elem ? l : n;
	}
	return n;
}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(vector<vector<T> > &paths) const
{
    // your code here
	vector<T> path;
	pathHelper(root, paths, path);
}

template <typename T>
void BinaryTree<T>::pathHelper(Node* subRoot, vector<vector<T> >& allpath, vector<T> path) const {

	if(subRoot == NULL)
		return;

	path.push_back(subRoot->elem);


	if(!(subRoot->left) && !(subRoot->right)) {
		allpath.push_back(path);
	}

	else {
		pathHelper(subRoot->left, allpath, path);
		pathHelper(subRoot->right, allpath, path);
	}
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return -1;
}

