#include <iostream>
#include <string>
#include "AVLTree.h"
#include <iomanip>
#include <queue>
using namespace std;

AVLTree::AVLTree(){
    root = nullptr;
}

AVLTree::~AVLTree(){
    

}

AVLNode* AVLTree::getRoot(){
    return root;
}


// search value ss in the AVL tree
bool AVLTree::find(string ss){
    if (root == nullptr) {
        return false;
    }
    
    AVLNode* node = root;
    
    while (node != nullptr) {
        if (ss.compare(node->ssn) == 0) {
            return true;
        }
        if (ss.compare(node->ssn) < 0) {
            node = node->left;
        }
        else{
            node = node->right;
        }
    }
    return false;
}

// return the height of the subtree rooted at node
// if subtree is empty, height is -1
// if subtree has one node, height is 0
int AVLTree::height(AVLNode* node){
    
    if(node != nullptr){
        return node->height;
    }
    else{
        return -1;
    }
}

// return the balance factor of the node
int AVLTree::balanceFactor(AVLNode* node){
    return height(node->left) - height(node->right);
}

// update the height of the node
// this should be done whenever the tree is modified
void AVLTree::updateHeight(AVLNode* node){
    int hl = height(node->left);
    int hr = height(node->right);
    node->height = (hl>hr ? hl : hr) + 1;
}


// rotate right the subtree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::rotateRight(AVLNode* node){
    AVLNode* lp = node->left;      // left child of node
    if (node->parent!=nullptr) {  // node is not root
        if (node->parent->left == node) { // node is a left child
            node->parent->left = lp;
        }else{
            node->parent->right = lp;     // node is a right child
        }
    }

    if (lp->right != nullptr) {           // pointer update
        lp->right->parent = node;
    }
    
    lp->parent = node->parent;
    node->left = lp->right;
    lp->right = node;
    node->parent = lp;
    updateHeight(node);                   // after rotation, update height
    updateHeight(lp);                     // after rotation, update height
    if (node == root) {
        root = lp;
    }
    return lp; // lp is the new root of the subtree
}


// rotate left the subtree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::rotateLeft(AVLNode* node){
    AVLNode* rp = node->right;
    if (node->parent!=nullptr) {
        if (node->parent->left == node) {
            node->parent->left = rp;
        }else{
            node->parent->right = rp;
        }
    }

    if (rp->left != nullptr) {
       rp->left->parent = node;
    }
    
    rp->parent = node->parent;
    
    node->right = rp->left;
    rp->left = node;
    node->parent = rp;
    node->parent = rp;
    updateHeight(node);
    updateHeight(rp);
    if (node == root) {
        root = rp;
    }
    return rp;
}


// rebalance a tree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::balance(AVLNode* node){
    updateHeight(node);
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left); // for left right case
        }
        
        AVLNode* temp = rotateRight(node);
        updateHeight(temp);
        return temp;
    }
    
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);  // for right left case
        }
        AVLNode* temp2 = rotateLeft(node);
        updateHeight(temp2);
        return temp2;
    }
    return node;
}

// insert a new node with (ss, na) to the AVL tree
// if there exists ss value, return false
// otherwise, insert it, balance the tree, return true
bool AVLTree::insert(string ss, string na){
	//creates new node
	AVLNode* temp = new AVLNode(ss,na);
	
	//if tree is empty, add root
	if (root == nullptr) {
		root = temp;
        return false;
    }
    
    AVLNode* node = root;
    
	//if tree is not empty, check to see if value already exists within tree
	if(find(ss) == false){
		
		//while current node is not a leaf, treverses down the tree until it is
		while(node != NULL) {
			if(node->left == nullptr && node->right == nullptr)
				break;
			else{
				if (ss.compare(node->ssn) < 0) {
					if(node->left == NULL)
						break;
					node = node->left;
				}
				else{
					if(node->right == NULL)
						break;
					node = node->right;
				}
			}
		}
		
		   //adds nodes to tree
		if (ss.compare(node->ssn) < 0){
			node->left = temp; ;
		}
		else{
			node->right = temp;
		}
		updateHeight(node);
		
		
		int balance = balanceFactor(node);
		
		//if the tree is unbalanced, re-balances
		if (balance > 1 && ss < node->left->ssn){
			cout << ss << endl;
			rotateRight(node);
		}
		if (balance < -1 && ss > node->right->ssn)
			rotateLeft(node);
		if (balance > 1 && ss > node->left->ssn)
		{
			node->left =  rotateLeft(node->left);
			rotateRight(node);
		}
		if (balance < -1 && ss < node->right->ssn)
		{
			node->right = rotateRight(node->right);
			rotateLeft(node);
		}
		updateHeight(root);
		
		return true;
		
	}
	else return false;
}


AVLNode* AVLTree::maxOfSubtree(AVLNode* node){
    if (node == nullptr) {
        return nullptr;
    }
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

// delete the node containing value ss
// if there is not such node, return false
// otherwise, delete the node, balance the tree, return true
bool AVLTree::deleteNode(string ss){
	
    //if node exists, it is deleted, if not, return false
    if(find(ss)){
		
		AVLNode *temp = root;
		
		//Define a placeholder node
			
			//locate the node you want to delete
			while(temp->ssn != ss){
				if(temp->ssn > ss)
					temp = temp->left;
				else
					temp = temp->right;
			}
			cout << temp->ssn << endl;
			//if node has no children, set it to nullptr
			//if(temp->left == nullptr && temp->right == nullptr)
				//temp = nullptr;
			//if node has one child, set node to child, set child to nullptr, set parent->left/right to child
			if(temp->left == nullptr || temp->right == nullptr){
				if(temp->left != nullptr){
					temp->parent = temp->left;
					temp = temp->left;
					temp->left = nullptr;
				}
			else{
					temp->parent = temp->right;
					temp = temp->right;
					temp->right = nullptr;
				}
			}/*
			//if node has two children, find max element in left subtree, set temp to that, delete max element
			if(temp->left != nullptr || temp->right != nullptr){
				temp->ssn = maxOfSubtree(temp)->ssn;
				maxOfSubtree(temp);
			}
			
			int balance = balanceFactor(temp);
			
			//if the tree is unbalanced, re-balances
			if (balance > 1 && ss < temp->left->ssn){
				cout << ss << endl;
				rotateRight(temp);
			}
			if (balance < -1 && ss > temp->right->ssn)
				rotateLeft(temp);
			if (balance > 1 && ss > temp->left->ssn)
			{
				temp->left =  rotateLeft(temp->left);
				rotateRight(temp);
			}
			if (balance < -1 && ss < temp->right->ssn)
			{
				temp->right = rotateRight(temp->right);
				rotateLeft(temp);
			}
			updateHeight(root);
			*/
			return true;
	}
	else return false;
    
}

// internal function
// do not call it directly
void AVLTree::print(AVLNode* x, int indent){
    if(x == nullptr) return;
    if (x->right != nullptr) {
        print(x->right, indent+4);
    }
    
    if (indent != 0) {
        cout << std::setw(indent) << ' ';
    }
    
    if(x->right != nullptr){
        cout << " /\n" << std::setw(indent) << ' ';
    }
    
    cout << x->ssn << endl;
    
    if (x->left != nullptr) {
        cout << std::setw(indent) << ' ' <<" \\\n";
        print(x->left, indent+4);
    }
    
}

// print out the structure of the binary tree
// use it for debugging, I love this function
void AVLTree::print(){
    int count = 0;
    print(root, count);
}


// it does not level order traversal
// it prints out the number of node
// use it mainly for debugging
void AVLTree::levelOrder(){
	
	int count;
	
	cout << count << endl;
	
}


