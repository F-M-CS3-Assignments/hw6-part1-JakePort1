//Jacob Port 
// HW6 Part 1 
// CPS 222 
// Professor Hu

#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"
using namespace std;

RedBlackTree::RedBlackTree(){
	root = nullptr; 
}

RedBlackTree::RedBlackTree(int newData){
    this->Insert(newData); 
}

//copy contructor: 
RedBlackTree::RedBlackTree(const RedBlackTree &rbt){
    for(int i : rbt.allData){
        this->Insert(i); 
    }
}

void RedBlackTree::Insert(int d){
    allData.push_back(d); //add to list of all data, which I will use for copy constructor 

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

    if(uncle == nullptr || uncle->color == COLOR_BLACK){ //if the uncle doesn't exist it will be a null ptr, which is also 
                                                        //considered black 

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
            new_node->color = COLOR_BLACK; 
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
                parent = currNode; 
                break;
            }
            //else, make the right node the currnode and continue throughout the loop
            else{         
                currNode = currNode->right; 
                continue; 
            }
        }

        //left path, this is the same thing as the above code, but done for a left side scenario
        if(node->data < currNode->data){
            if(currNode->left == nullptr){
                currNode->left = node;
                parent = currNode; 
                break;
            }
            //else, make the right node the currnode and continue throughout the loop
            else{
                currNode = currNode->left; 
                continue; 
            }
        }
    }

    node->parent = parent; 
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

RBTNode* RedBlackTree::CopyOf(const RBTNode *node){

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
   
    //used this video for guidance https://www.youtube.com/watch?v=b_NjndniOqY
    string answer = "";
    string color; 

    //base case
    if(n ==nullptr){
    return "";
    }


    //this just gets the color in a usable format 
    if(n->color == COLOR_BLACK){
        color = "B";
    }
    else{
        color = "R"; 
    }

   //base case 
   answer += ToInfixString(n->left);        //recursive call 
   answer += (" " + color + to_string(n->data)  + " ");  //creates the output
   answer += ToInfixString(n->right); 

   return answer; 

}

bool RedBlackTree::Contains(int data) const{

    return containsHelper(root, data);
}

bool RedBlackTree::containsHelper(RBTNode *node, int data) const{

    //do this recusrively, base case is that the current node has the value of data, which will return true. Else
    //will recall recurslibe on the right and left node (assuming that they are not nullptr)
    bool answer; 

    //base case 
    if(node == nullptr){
        return false; 
    }

    //other base case 
    if(node->data == data){
        return true; 
    }

    return containsHelper(node->left, data) ||  containsHelper(node->right, data);

}

//these have bugs and need to be fixed 
void RedBlackTree::RightRotate(RBTNode *node){

    // RBTNode *copyOfParent = CopyOf(node); //save a copy of the parent

    RBTNode *leftChild = node->left; //save the leftChild so that it can be refernces later. 

    //this may be redunant: 
    if(leftChild == nullptr){
        return; 
    }

    //the nodes left child will now become the left child of the its right child, because 
    //the nodes->left->right is going to be bigger than what will replace the node, but we know
    //it will be smaller than the orignal node (because its already on the left side)
    node->left = leftChild->right; 


    //this udpates the parent, since the parent is changing when you rotate
    if(leftChild->right != nullptr){
        leftChild->right->parent = node; 
    }

    leftChild->parent = node->parent; 

    if(node->parent == nullptr){
        root = leftChild; //this makes sure that the root member does not get lost after a rotaiton
    }

    else if (node == node->parent->left){
        node->parent->left = leftChild; 
    }

    else{
        node->parent->right = leftChild; 
    }

    leftChild->right = node; 
    node->parent = leftChild; 

}

void RedBlackTree::LeftRotate(RBTNode *node){
    //this is copied from the RightRotate, just reverersed (same logic),
    
    RBTNode *rightChild = node->right; //save the right child so that it can be accessed later: 

    //This part might be redundant: 
    if(rightChild == nullptr){
        return; 
    }

    node->right = rightChild->left; 

    if(rightChild->left != nullptr){
        rightChild->left->parent = node; 
    }

    rightChild->parent = node->parent; 

    if(node->parent == nullptr){ 
        root = rightChild; 
    }

    else if(node == node->parent->left){
        node->parent->left = rightChild; 
    }

    else{
        node->parent->right = rightChild; 
    }

    rightChild->left = node; 
    node->parent = rightChild; 
}

string RedBlackTree::ToPrefixString(const RBTNode *n){

    //will use these if the base case is not satisfied
    string color; 
    string leftSide; 
    string rightSide; 
    string answer;

    //do this recursively, base case is that the ndoe is nullptr: 
    if(n == nullptr){
        return ""; 
    }
    //else create a string to that holds the info for the currNode, then recursively get the 
    //rest of the right and left trees:
    else{
        if(n->color == COLOR_BLACK){ //this just helps get the color in a string format. 
            color = "B";
        }else{
            color = "R"; 
        }
        answer = " " + color + to_string(n->data) + " ";

        leftSide = ToPrefixString(n->left); 
        rightSide = ToPrefixString(n->right); 
    }

    return answer + leftSide + rightSide; 
    
}

//for debugging: 
string RedBlackTree::ToPostfixString(const RBTNode *n){

    //used this video for guidance: https://www.youtube.com/watch?v=b_NjndniOqY

     //base case 
    if(n == nullptr){
        return ""; 
    }

    string answer = ""; //will store the final answer here 

    //this helps to get the color in a string format
    string color; 
    if(n->color == COLOR_BLACK){
            color = "B";
    }
    else{
        color = "R"; 
    }

    answer += ToPostfixString(n->left); //do left first then right 
    answer += ToPostfixString(n->right); 

    answer += " " + color + to_string(n->data) + " ";  //format the output.

    return answer; 

}
