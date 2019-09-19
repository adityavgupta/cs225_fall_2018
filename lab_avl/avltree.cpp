 /**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <cmath>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
	Node* x = t;
	Node* y = t->right;

	x->right = y->left;
	//updateHeight(x);

	y->left = x;
	//updateHeight(y);

	t = y;
	updateHeight(x);
	updateHeight(y);
	 
	//t = y;	   
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
	Node* x = t;
	Node* y = t->left;

	x->left = y->right;
	//updateHeight(x);

	y->right = x;
	//updateHeight(y);

	t = y;

	updateHeight(x);
	updateHeight(y);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
	rotateRight(t->right);
	rotateLeft(t);
}

//helper function to update height
template <class K, class V>
void AVLTree<K, V>::updateHeight( Node*& subtree) {
	subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
	if(subtree == NULL) {
		updateHeight(subtree);
		return;
	}
	else {
		int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);

		if(balance == -2) {
			int l_balance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
			if(l_balance == -1) {
				rotateRight(subtree);
			} else {
				rotateLeftRight(subtree);
			}
		} else if(balance == 2) {
			//cout << "reached 90" <<endl;
			int r_balance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
			if(r_balance == 1) {
				rotateLeft(subtree);
			} else {
				rotateRightLeft(subtree);
			}
		}
		updateHeight(subtree);
	}
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
	if(subtree == NULL) {
		subtree = new Node(key , value);
		updateHeight(subtree);
	} else if(key < subtree->key) {
		insert(subtree->left, key, value);
		rebalance(subtree);
	} else if(key > subtree->key) {
		insert(subtree->right, key, value);
		rebalance(subtree);
	}
	//rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::iopRemove(Node* & node, Node* & iop) {
	if(iop->right) {
		iopRemove(node, iop->right);
	} else {
		swap(node, iop);
		delete iop;
		iop = NULL;
	}
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
		remove(subtree->left, key);
		rebalance(subtree);

    } else if (key > subtree->key) {
        // your code here
		remove(subtree->right, key);
		rebalance(subtree);
    } else {
		
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
			delete subtree;
			subtree = NULL;
				
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
			iopRemove(subtree, subtree->left);
			//rebalance(subtree);

        } else {
            /* one-child remove */
            // your code here
			
			//One-Child (left) remove
			if(subtree->left && !(subtree->right)) {
				Node* temp = subtree;
				subtree = subtree->left;
				delete temp;
			}
			//One-Cild remove (right)
			if(!(subtree->left) && subtree->right) {
				Node *temp = subtree;
				subtree = subtree->right;
				delete temp;
			}
        }
    }
}
