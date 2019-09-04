//int filesize = 0;
//    while(!inputfile.eof())
//    {
//        getline(inputfile, input);
//        filesize++;
//    }
//    HashTable<string, Pokemon> hashtable(filesize);
//    inputfile.close();
//    inputfile.open(inputfilename);

#pragma once
#include "Bucket.h"
#include "cmath"
using namespace std;

template <class T, class T1>

class HashTable
{
private:

	HashNode<T, T1> **ptr;
	int sizeHash;

public:

	HashTable(int);
	~HashTable();

	int hashFunction(T key) const;
	void insert(T key, T1 item);
	bool remove(T key, T1& item);
	void display() const;
	double loadFactor() const;
	bool search(const T &Key, T1 &value, T1& returnItem);
	void rehash();

};
///////////////////Done//////////////////
template<class T, class T1>
HashTable<T, T1>::HashTable(int filesize)

{
	sizeHash = filesize;
	ptr = new HashNode<T, T1>*[sizeHash];//hash linked list being created
	for (int i = 0; i < sizeHash; i++)
	{
		ptr[i] = nullptr;
	}
}

template<class T, class T1>
int HashTable<T, T1>::hashFunction(T key) const

{
	int result = 0;
	for (int i = 0; i < key.length(); i++)
	{
		result = result + pow(key[i], i + 1);//pow raise the power
	}
	return (result % sizeHash);
}
///////////////////Done//////////////////
template<class T, class T1>
bool HashTable<T, T1>::search(const T &key, T1 &value, T1& returnItem)
{

	unsigned long HashValue = hashFunction(key);
    HashNode<T, T1> *entry = ptr[HashValue];

    if (!entry)
        return false;

	while(entry != nullptr && entry -> getItem() != value)
	{
		entry = entry->getNext();
	}

    if (entry)
    {
        returnItem = entry -> getItem();
        return true;
    }
    else
        return false;
}

///////////////////Done//////////////////
template<class T, class T1>
void HashTable<T, T1>::rehash()
{

    int primeNum[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,
                        83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167};

    int num = 0;
    while(sizeHash*2 > primeNum[num])
    {
        num++;
    }
    int OldSize = sizeHash;
    sizeHash = primeNum[num];
    HashNode<T, T1> **newptr = new HashNode<T, T1>*[sizeHash]();

    for (int i = 0; i < OldSize; i++)
	{
		HashNode<T, T1> * current = ptr[i];
		while (current)
		{
		    HashNode<T,T1>  *holder = current -> getNext();
			T1 TEMP = current->getItem();
            delete current;
            current = holder;

			string KEY = TEMP.getID();
			unsigned long hashValue = hashFunction(KEY);
			HashNode<T, T1> *prev = NULL;
            HashNode<T, T1> *entry = newptr[hashValue];
			HashNode<T, T1>* newNode = new HashNode<T, T1>(KEY, TEMP);
            if (!newptr[hashValue])
            {
                newptr[hashValue] = newNode;
                continue;
            }
            while(entry != nullptr)
            {
                prev = entry;
                entry = entry->getNext();
            }
            prev -> setNext(newNode);
		}
	}

    delete [] ptr;
    ptr = newptr;
}

///////////////////Done//////////////////
template<class T, class T1>
void HashTable<T, T1>::insert(T key, T1 item)

{
	unsigned long hashValue = hashFunction(key);
	HashNode <T, T1> *prev = NULL;
	HashNode <T, T1> *entry = ptr[hashValue];
	HashNode<T, T1>* newNode = new HashNode<T, T1>(key, item);
    if (!ptr[hashValue])
    {
        ptr[hashValue] = newNode;
        return;
    }
	while(entry != NULL)
	{
        prev = entry;
		entry = entry->getNext();
	}
    prev -> setNext(newNode);

    if(loadFactor() >= 75)
    {
        rehash();
    }

}

///////////////////Done//////////////////
template<class T, class  T1>
bool HashTable<T, T1>::remove(T key, T1& item)

{
	unsigned long hashValue = hashFunction(key);
	HashNode<T, T1> *prev = NULL;
	HashNode <T, T1> *entry = ptr[hashValue];
	while(entry != NULL && entry->getKey() != key)
	{
		prev = entry;
		entry = entry->getNext();
	}
	if (entry == NULL)
	{
		//key not found
		return false;
	}
	else
	{
		if (prev == NULL)
		{
			//remove first in da list
			item = entry->getItem();
			ptr[hashValue] = entry->getNext();
		}
		else
		{
		    item = entry->getItem();
			prev->setNext(entry->getNext());
		}
		delete entry;
		return true;
	}
}


template<class T, class  T1>
void HashTable<T, T1>::display() const

{
	for (int i = 0; i < sizeHash; i++)
	{
		cout << i + 1 << ": ";
		HashNode<T, T1> * current = ptr[i];
		while (current)
		{
			cout << current->getItem() << " --> ";
			current = current->getNext();
		}

		if (current == NULL)
		{
			cout << "Empty";
		}
		//cout << count;
		cout << endl;
	}
}
///////////////////Done//////////////////
template<class T, class  T1>
HashTable<T, T1>::~HashTable()
{
	for (int i = 0; i < sizeHash; i++)
	{
		HashNode<T, T1> * current = ptr[i];
		while (current != NULL)
		{
			//Changed made here
			HashNode<T,T1>  *prev = current -> getNext();
            delete current;
            current = prev;
		}
        cout << "Deleting HashNode number: " << i+1 << endl;
	}
	delete[] ptr;
}
///////////////////Done//////////////////
template<class T, class  T1>
double HashTable<T, T1>::loadFactor() const

{
	double countPtr = 0;
	for (int i = 0; i < sizeHash; i++)
	{
		if (ptr[i]!= nullptr)
		{
			countPtr++;
		}
	}

	double loadfactor = countPtr / sizeHash * 100;
	return loadfactor;
}
