#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H


#define COLOR_RED 0
#define COLOR_BLACK 1
#define COLOR_DOUBLE_BLACK 2

#include <iostream>

using namespace std;


struct RBTNode {
	int data;
	unsigned short int color;
	RBTNode *left = nullptr;
	RBTNode *right = nullptr;
	RBTNode *parent = nullptr;
	bool IsNullNode = false;
};


class RedBlackTree {
	
	public:
		RedBlackTree();
		RedBlackTree(int newData);
		RedBlackTree(const RedBlackTree &rbt);

		string ToInfixString() const {return ToInfixString(root);};
		string ToPrefixString() const { return ToPrefixString(root);};
		string ToPostfixString() const { return ToPostfixString(root);};

		void Insert(int newData);

		bool Contains(int data) const ;
		size_t Size() const {return numItems;};
		int GetMin() const;
		int GetMax() const;
		

		vector<int> allData; //i will store all the inserted data values here, so that it makes creating 
							// a copy constructor easier ( i can just iterate though and insert each one to the copy, 
							//in the same order) 
	
	private: 
		unsigned long long int numItems  = 0;
		RBTNode *root = nullptr;

		//using this as a helper function to recursively iterate throught the tree; 
		bool containsHelper(RBTNode *node, int data) const;
		
		static string ToInfixString(const RBTNode *n);
		static string ToPrefixString(const RBTNode *n);
		static string ToPostfixString(const RBTNode *n);
		
		static string GetColorString(const RBTNode *n);
		static string GetNodeString(const RBTNode *n);
		
		void BasicInsert(RBTNode *node);
		void InsertFixUp(RBTNode *node);
		
		RBTNode *GetUncle(RBTNode *node) const;
		
		bool IsLeftChild(RBTNode *node) const;
		bool IsRightChild(RBTNode *node) const;
		
		void LeftRotate(RBTNode *node);
		void RightRotate(RBTNode *node);
		
		RBTNode *CopyOf(const RBTNode *node);


		RBTNode *Get(int data) const;

};

#endif
