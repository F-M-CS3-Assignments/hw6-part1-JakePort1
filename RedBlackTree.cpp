
#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

/**
 * 
 * This "First Step" tests file is useful to get your project started
 * 
 * To run this code you only need to implement
 * 	+ The Constructor
 * 	+ The Insert() function to insert only one node
 * 	+ The ToInfixString() function to print a tree containing only one node
 * 
**/


/*

struct RBTNode {
	int data;
	unsigned short int color;
	RBTNode *left = nullptr;
	RBTNode *right = nullptr;
	RBTNode *parent = nullptr;
	bool IsNullNode = false;
};

*/


//NOTES TO SELF: 
/*

I may have to go in and make changes to whereever its neededd to get the uncles color 
because i'm not sure if I accounted for the nullptr uncle scenario which still counts as black 


*/


using namespace std;



RedBlackTree::RedBlackTree(){
	root = nullptr; 
}



//copy contructor: 
RedBlackTree::RedBlackTree(const RedBlackTree &rbt){

    // newNode->color = rbt.color;
    // newNode->data = rbt->data;
    // return 
}






void RedBlackTree::Insert(int d){
	//if tree is emtpy, make a root node
    if(root == nullptr){
        RBTNode *node = new RBTNode; 
        node->color = COLOR_BLACK; // root node will always be black
        node->data = d; 
        root = node;
        numItems++;
    } // add further insert here 
    else{
        RBTNode *node = new RBTNode; //dynamically create the node to insert; 

        node->color = COLOR_RED;
        node->data = d; 

        //perform a basic insert; 
        BasicInsert(node); 
        numItems++; //update the size of the tree

        if(node->parent != nullptr && node->parent->color == COLOR_RED){
            InsertFixUp(node); 

        }

    }
}   

void RedBlackTree::InsertFixUp(RBTNode *new_node){
    
    RBTNode *parent = new_node->parent; 
    RBTNode *uncle = GetUncle(new_node); 
    RBTNode *grand_parent = parent->parent; 

    if(uncle->color == COLOR_BLACK){

        //1-1
        if(grand_parent != nullptr){
            grand_parent->color = COLOR_RED;
        }
        //1-2
        if(IsLeftChild(new_node) && IsLeftChild(parent)){
            RightRotate(grand_parent); //still need to implement the rotate functions
            parent->color = COLOR_BLACK;  
        }
        //1-3
        else if(IsRightChild(new_node) && IsRightChild(parent)){
            LeftRotate(grand_parent); 
            parent->color = COLOR_BLACK; 
        }

        else if(IsLeftChild(new_node) && IsRightChild(parent)){
            RightRotate(parent); 
            LeftRotate(grand_parent); 
            new_node->color = COLOR_BLACK; 
            parent->color = COLOR_RED;
        }
        //1-4
        else if(IsRightChild(new_node) && IsLeftChild(parent)){
            LeftRotate(parent); 
            RightRotate(grand_parent); 
            new_node->color - COLOR_BLACK; 
            parent->color = COLOR_RED;
        }
        //1-5
        else{
            //this case is not possible so it will throw an error: 
            throw invalid_argument("invalid state"); 
        }
    }
    else if(uncle != nullptr && uncle->color == COLOR_RED){

        //2-1
        parent->color = COLOR_BLACK; 
        uncle->color = COLOR_BLACK; 

        if(grand_parent != nullptr){
            if(root != grand_parent){
                grand_parent->color = COLOR_RED;
                if(grand_parent->parent != nullptr){
                    if(grand_parent->parent->color == COLOR_RED){
                        InsertFixUp(grand_parent);
                    } 
           
                }   
            }
        }
    }
           
}

bool RedBlackTree::IsLeftChild(RBTNode *node) const{
    RBTNode *parent = node->parent; 

    if(parent->left == node){
        return true; //will return true if the parents left child is equal to the inputted node 
    }
    else{
        return false; 
    }
}

bool RedBlackTree::IsRightChild(RBTNode *node) const{
    RBTNode *parent = node->parent; 

    if(parent->right == node){
        return true; 
    }
    else{
        return false;
    }
}

RBTNode* RedBlackTree::GetUncle(RBTNode *node) const{    
    
    RBTNode *grandParent = node->parent->parent; 

    if(node->parent->parent == nullptr){
        return nullptr; //will return nullptr if the node is too high to have an uncle, 
                        //for example, if it is the child of the root node, there will be no uncle. 
    }
    else if(IsLeftChild(node->parent)){
        return node->parent->parent->right;

    }
    else if(IsRightChild(node->parent)){
        return node->parent->parent->left;
    }
}


void RedBlackTree::BasicInsert(RBTNode *node){

    //this assumes that the root node already exists.
    RBTNode *parent = nullptr;
    RBTNode *currNode; 

    currNode = root;

    while(true){

        //right path
        if(node->data > currNode->data){
            //check if the right of the root (or currnode) is nullptr; nullptr is base case
            //if base case, then just add the node and break out of the while loop.
            if(currNode->right == nullptr){
                currNode->right = node;
                break;
            }
            //else, make the right node the currnode and continue throughout the loop
            else{
                RBTNode *temp = currNode;//this will hold the orignal node so that we can reference it later as a parent. 
                currNode = currNode->right; 
                currNode->parent = temp; //after updating the currNode, it sets its parent value. 
                continue; 
            }
        }

        //left path, this is the same thing as the above code, but done for a left side scenario
        if(node->data < currNode->data){
            if(currNode->left == nullptr){
                currNode->left = node;
                break;
            }
            //else, make the right node the currnode and continue throughout the loop
            else{
                RBTNode *temp = currNode;
                currNode = currNode->left; 
                currNode->parent = temp;
                continue; 
            }
        }
    }
}

int RedBlackTree::GetMin() const {

    RBTNode *currNode = root; 

    while(currNode->left != nullptr){
        currNode = currNode->left;

    }

    return currNode->data; 
}
		   
int RedBlackTree::GetMax() const {
    
    RBTNode *currNode = root; 

    while(currNode->right != nullptr){
        currNode = currNode->right;

    }

    return currNode->data; 
}

RBTNode *CopyOf(const RBTNode *node){

    RBTNode *newNode = new RBTNode; //dynamically create a new node; 

    newNode->data = node->data;    
    newNode->color = node->color; 
    newNode->IsNullNode = node->IsNullNode; 
    newNode->left = node->left; 
    newNode->right = node->right; 
    newNode->parent = node->parent; 

    return newNode; 
}

string RedBlackTree::ToInfixString(const RBTNode *n){ //will have to update this again later
    if(n ==  nullptr){
        return "";
    }else{
        cout << "----- test111 -----" << endl;
        return " B" + to_string(n->data) + " ";
    }
}

bool RedBlackTree::Contains(int data) const{

    bool answer = false;

    //base case: 
    return answer;
}

bool containsHelper(RBTNode node, int data){


    //do this recusrively, base case is that the current node has the value of data, which will return true. Else
    //will recall recurslibe on the right and left node (assuming that they are not nullptr)



}


void RedBlackTree::RightRotate(RBTNode *node){


    RBTNode *copyOfParent = CopyOf(node); //save a copy of the parent

    RBTNode *savedRightChild = node->left->right;  //save a copy of the part of the tree that may become abonded

    node = node->left; //this rotates the left child up; 

    node->right = copyOfParent; //this (updates) makes the right side of the rotated node

    //the left side of now parent node stays the same
    //adressing the now abandoned right node of: 

    node->right->left = savedRightChild; 
}


void RedBlackTree::LeftRotate(RBTNode *node){
    //this is the same as the above right rotate, just reveresed: 
    
    RBTNode *copyOfParent = CopyOf(node); //copy of parent child 

    RBTNode *savedLeftChild = node->right->left;  //this will become the left childs right node (from the parent)

    node = node->right; //this rotates the right child up; 

    node->left = copyOfParent; //this make continues the pattern 

    //the right side of now parent node stays the same, but it updates the right child spot:
    node->left->right = savedLeftChild; 
}