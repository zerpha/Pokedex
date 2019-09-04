#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include <iostream>

template<class T, class T1>

class HashNode

{
private:

	T Key;
	T1 Item;
	HashNode<T, T1> *next;

public:

	HashNode(T value, const T1 data) : Key(value), Item(data), next(nullptr) {};
	void setKey(T value) { Key = value; }
	void setItem(T1 data) { Item = data; }
	void setNext(HashNode<T, T1>* pointer) { next = pointer; }
	T getKey() const { return Key; }
	T1 getItem() const { return Item; }
	HashNode<T, T1>* getNext() { return next; }
	//int getcount() const { return count; }

};

#endif // HASHTABLE_H_INCLUDED
