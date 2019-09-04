// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Henry Nguyen

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "QUEUE.h"
#include <iostream>

using std::cout;
using std::endl;

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree() {destroyTree(rootPtr); cout << "\nDestroying tree...." << endl;}
	BinaryTree & operator = (const BinaryTree & sourceTree);

	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0; cout << "Destroying tree...." << endl << endl;} //empties the tree
	void print() const{int level = 0; printTree(rootPtr, level);}
	void preOrder(void visit(ItemType)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType)) const{_postorder(visit, rootPtr);}
	void BreadthOrder(void visit(ItemType)) const {_breadth(visit, rootPtr);}

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType &, int compare(ItemType, ItemType)) = 0;
	virtual bool remove(ItemType & data, int compare(ItemType, ItemType)) = 0;
	virtual bool getEntry(const ItemType &, ItemType& ID, int compare(ItemType, ItemType)) const = 0;

private:
	// delete entire BST
	void destroyTree(BinaryNode<ItemType>* nodePtr);
	void printTree(BinaryNode<ItemType>* nodePtr, int level) const; // not used

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType), BinaryNode<ItemType>* nodePtr) const;
	void _breadth(void visit(ItemType), BinaryNode<ItemType>* nodePtr) const;

};

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
	BinaryNode<ItemType>* newNodePtr = 0;

    return newNodePtr;
}
// empties tree
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if(nodePtr != 0)
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        count--;
        delete nodePtr;
    }
}
// prints BST in breadth order
template<class ItemType>
void BinaryTree<ItemType>::_breadth(void visit(ItemType), BinaryNode<ItemType>* nodePtr)  const
{
    BinaryNode<ItemType>* newNodePtr;
    Queue<BinaryNode<ItemType>*> line;
    line.enqueue(nodePtr);

    while(!line.isEmpty())
    {
        line.dequeue(newNodePtr);
        ItemType item = newNodePtr->getItem();
        visit(item);
        if(newNodePtr->getLeftPtr() != 0)
            line.enqueue(newNodePtr->getLeftPtr());
        if(newNodePtr->getRightPtr() != 0)
            line.enqueue(newNodePtr->getRightPtr());
    }
}
// prints BST with indented tree with levels shown
template<class ItemType>
void BinaryTree<ItemType>::printTree(BinaryNode<ItemType>* nodePtr, int level) const
{
    level++;
    for(int i = 1; i < level; i++)
    {
        cout << "        ";
    }
    cout << level << ". " << nodePtr->getItem()->getID() << endl;
    if(nodePtr->getRightPtr() != 0)
        printTree(nodePtr->getRightPtr(), level);
    if(nodePtr->getLeftPtr() != 0)
        printTree(nodePtr->getLeftPtr(), level);

}
// prints BST in preorder
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}
// prints BST in inorder
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
	{
	    _inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}
// prints BST in postorder
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
	{
	    _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
	}
}

#endif


