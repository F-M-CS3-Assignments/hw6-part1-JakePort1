
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


using namespace std;



RedBlackTree::RedBlackTree(){
	root = nullptr; 
}

void RedBlackTree::Insert(int d){
	//if tree is emtpy, make a root node
    if(root == nullptr){
        RBTNode node; 
        node.color = COLOR_BLACK; // root node will always be black
        node.data = d; 
        root = &node;
        numItems++;
    } // add further insert here 
    else{
        RBTNode node; 
        node.color = COLOR_RED;
        node.data = d; 

        //perform a basic insert; 
        BasicInsert(&node); 

        



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