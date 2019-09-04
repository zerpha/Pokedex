// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Henry Nguyen

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr, int compare(ItemType, ItemType));

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, ItemType &target, bool & success, int compare(ItemType, ItemType));

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

	// search for target node
	//BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;

	// search for smallest node
	BinaryNode<ItemType>* findSmall(BinaryNode<ItemType>* treePtr) const;

	// search for largest node
	BinaryNode<ItemType>* findLarge(BinaryNode<ItemType>* treePtr) const;

public:
	// insert a node at the correct location
    bool insert(const ItemType& ID, int compare(ItemType, ItemType));
	// remove a node if found
	bool remove(ItemType & anEntry, int compare(ItemType, ItemType));
	// find a target node
	bool getEntry(const ItemType &  target, ItemType& ID, int compare(ItemType, ItemType)) const;
    // find smallest node
	bool getSmallest(ItemType& ID) const { ID = findSmall(this->rootPtr)->getItem(); return true; }
    // find largest node
	bool getLargest(ItemType& ID) const { ID = findLarge(this->rootPtr)->getItem(); return true; }


};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType& ID, int compare(ItemType, ItemType))
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(ID);
	this->rootPtr = _insert(this->rootPtr, newNodePtr,compare);
	this->count++;
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(ItemType & target, int compare(ItemType, ItemType))
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful, compare);
	this->count--;
	return isSuccessful;
}
//////////////////////////////////////////////////////////////////////////////////
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType &  anEntry, ItemType& ID, int compare(ItemType, ItemType)) const
{
    BinaryNode<ItemType>* CurPtr = this->rootPtr;

    while(CurPtr != 0)
    {
        if(compare(anEntry, CurPtr->getItem()) == -1)
        {
            ID = CurPtr->getItem();
            return true;
        }
        else if(compare(anEntry, CurPtr->getItem()) == 1)
            CurPtr = CurPtr->getLeftPtr();
        else
            CurPtr = CurPtr->getRightPtr();
    }
    return false;
}
//////////////////////////// private functions ////////////////////////////////////////////
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr, int compare(ItemType, ItemType))
{
    if(nodePtr == 0)
    {
        nodePtr = newNodePtr;
        return nodePtr;
    }
    if(compare(newNodePtr->getItem(), nodePtr->getItem()))
        nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr, compare));
    else
        nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr, compare));
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findSmall(BinaryNode<ItemType>* treePtr) const
{
	if (treePtr->getLeftPtr() == 0)
	{
		return treePtr;
	}
	else
	{
		treePtr = findSmall(treePtr->getLeftPtr());
		return treePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findLarge(BinaryNode<ItemType>* treePtr) const
{
	if (treePtr->getRightPtr() == 0)
	{
		return treePtr;
	}
	else
	{
		treePtr = findLarge(treePtr->getRightPtr());
		return treePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                        ItemType &target,
                                                          bool & success, int compare(ItemType, ItemType))
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if(compare(target, nodePtr->getItem()) == 1)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, compare));
	else if (compare(target, nodePtr->getItem()) == 0)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, compare));
	else
	{
		target = nodePtr->getItem();
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}
///////////////////////////////////////////////////////////////////////////
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


#endif

