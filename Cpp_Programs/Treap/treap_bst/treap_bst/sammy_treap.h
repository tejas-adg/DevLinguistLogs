#pragma once

#ifndef _TREAP_H_
#define _TREAP_H_

#include <random>
#include <iostream>
#include <algorithm>

#include "abstract_bst.h"

template <typename KeyType, typename ValueType>
class Treap : public AbstractBST<KeyType, ValueType>
{
public:
	Treap();

	~Treap();

	Treap(const Treap& rhs);

	Treap& operator=(Treap rhs);

	void swap(Treap& x, Treap& y);

	bool empty();

	void insert(const KeyType& key, const ValueType& value);

	ValueType search(const KeyType& key, bool& found);

	void remove(const KeyType& key);

	std::size_t height();


private:
	std::mt19937 rndgen;

	template <typename K, typename V>
	struct Node
	{
		K key;
		V data;
		std::mt19937::result_type priority;
		Node* parent;
		Node* childl;
		Node* childr;

		Node(const K& k, const V& d, Node* p = nullptr) : key(k), data(d), parent(p), childl(nullptr), childr(nullptr)
		{

		}
	};

	typedef Node<KeyType, ValueType>* cursor;

	cursor veryTopNode;

	void search_two(cursor dot, const KeyType& key, bool& found, cursor* out_dot);

	void insert_two(cursor& dot, const KeyType& key, const ValueType& value, cursor parent);

	std::size_t height_two(cursor dot);

	void remove_two(cursor& dot, const KeyType& key);

	void leftRotator(cursor& dot);

	void rightRotator(cursor& dot);

	void copier(cursor dot);


};


//rotating left function
template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::leftRotator(cursor& dot)
{
	//letting a be b's right child
	cursor a = dot->childr;
	cursor b = dot;

	//checking to see if the root is b
	if (veryTopNode == b)
	{
		//we want the root now to be a 
		veryTopNode = a;
		//setting the a's parent to nullptr since the root has no parent
		veryTopNode->parent = nullptr;
	}
	else
	{
		//checking to see if the b = c
		if (b == ((b->parent)->childr))
		{
			//if true then c = a
			b->parent->childr = a;
		}
		else
		{
			b->parent->childl = a;
		}
		a->parent = b->parent;
	}

	b->childr = a->childl;

	if (a->childl != nullptr)
	{
		a->childl->parent = b;
	}

	a->childl = b;
	a->parent = b->parent;
	b->parent = a;
	dot = a;
}

template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::rightRotator(cursor& dot)
{
	cursor a = dot->childl;
	cursor b = dot;

	if (veryTopNode == b)
	{
		veryTopNode = a;
		veryTopNode->parent = nullptr;
	}
	else
	{
		if (b == ((b->parent)->childl))
		{
			b->parent->childl = a;
		}
		else
		{
			b->parent->childr = a;
		}
		a->parent = b->parent;
	}

	b->childl = a->childr;

	if (a->childr != nullptr)
	{
		a->childr->parent = b;
	}

	a->childr = b;
	a->parent = b->parent;
	b->parent = a;
	dot = a;
}

//default constructor
template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::Treap()
{
	std::random_device rd;
	//seeds the random number generator
	rndgen.seed(rd());
	//sets root to NULL
	veryTopNode = nullptr;
}

//destructor
template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::~Treap()
{
	while (!empty())
	{
		remove(veryTopNode->key);
	}
}


//copy constructor
template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::Treap(const Treap& rhs)
{
	//random generator
	std::random_device rd;
	rndgen.seed(rd());
	//sets the root to nullptr
	veryTopNode = NULL;
	//deep copies
	copier(rhs.veryTopNode);

}

//operator= function
template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>& Treap<KeyType, ValueType>::operator=(Treap rhs)
{
	//swaps the root from this to rhs
	swap((*this), rhs);
	//returns current object
	return (*this);
}


template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::swap(Treap& x, Treap& y)
{
	//swaps the root with x and y and vice versa
	std::swap(x.veryTopNode, y.veryTopNode);
}

template <typename KeyType, typename ValueType>
bool Treap<KeyType, ValueType>::empty()
{
	//checks to see if the root is equal to nullptr, returns true if it is
	if (veryTopNode == nullptr)
	{
		//returns true
		return true;
	}
	//returns false otherwise
	return false;
}


template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
	insert_two(veryTopNode, key, value, nullptr);
}

template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::remove(const KeyType& key)
{
	remove_two(veryTopNode, key);
}

template <typename KeyType, typename ValueType>
ValueType Treap<KeyType, ValueType>::search(const KeyType& key, bool& found)
{

	cursor tempNode = nullptr;
	//stores data in t node
	search_two(veryTopNode, key, found, &tempNode);

	if (tempNode)
	{
		//directly returns data
		return tempNode->data;

	}
	//returning default value for value type
	return ValueType();

}


template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::remove_two(cursor& dot, const KeyType& key)
{
	if (dot == nullptr)
	{
		throw std::logic_error("no treap");
	}
	bool less = key < dot->key;
	bool greater = key > dot->key;
	bool leftIsNull = dot->childl == nullptr;
	bool rightIsNull = dot->childr == nullptr;
	if (less)
	{
		remove_two(dot->childl, key);
	}
	else if (greater)
	{
		remove_two(dot->childr, key);
	}
	else if (leftIsNull)
	{
		cursor t = dot->childr;
		delete dot;
		dot = t;
	}
	else if (rightIsNull)
	{
		cursor t = dot->childl;
		delete dot;
		dot = t;
	}

	//checking if priority is less than the left side child, then we rotate left and we remove the node
	else if (dot->priority < dot->childl->priority)
	{
		leftRotator(dot);
		remove_two(dot->childl, key);

	}
	//checking if priority is greater than the right side child, then we rotate right and we remove the node
	else //if (dot->priority > dot->childr->priority)
	{
		rightRotator(dot);
		remove_two(dot->childr, key);
	}


}

//repeating until priority node < priority parent
template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::insert_two(cursor& dot, const KeyType& key, const ValueType& value, cursor parent)
{

	if (dot == nullptr)
	{
		// creating a new node with the given key and value
		dot = new Node<KeyType, ValueType>(key, value, parent);
		// setting the children to nullptr
		dot->childr = nullptr;
		// making a random priority
		dot->priority = this->rndgen();
		// setting the children to nullptr
		dot->childl = nullptr;
	}
	//insert via binary search
	if (key < dot->key)
	{
		//does the insert
		insert_two(dot->childl, key, value, dot);
		//if priority of parent less than priority
		if (dot->priority < dot->childl->priority)
		{
			//if left child, rotate right about parent
			rightRotator(dot);
		}
	}
	//insert via binary search
	else if (key > dot->key)
	{
		//does the insert
		insert_two(dot->childr, key, value, dot);
		//if priority of parent less than priority
		if (dot->priority < dot->childr->priority)
		{
			//if right child, rotate left about parent
			leftRotator(dot);
		}
	}

}

template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::search_two(cursor dot, const KeyType& key, bool& found, cursor* out_dot)
{
	// if the current node is null then 
	// we have not found the required node in the treap
	if (dot == nullptr)
	{
		found = false;
		(*out_dot) = nullptr;
		return;
	}
	// if the current node is what we need then
	// we have found the node we need
	if (dot->key == key)
	{
		// set the found variable to true
		found = true;
		// set the outer valuetype variable to the data in the node
		(*out_dot) = dot;
		// return the control back to the caller
		return;
	}


	// Binary Search to find the node we want

	// if the required key is lesser than the current node's key then
	// we move to the left subtree
	if (dot->key > key)
	{
		found = false;
		search_two(dot->childl, key, found, out_dot);
	}
	// if the required key is greater than the current node's key then
	// we move to the right subtree.
	else
	{
		found = false;
		search_two(dot->childr, key, found, out_dot);
	}
}

//calculates height
template <typename KeyType, typename ValueType>
std::size_t Treap<KeyType, ValueType>::height_two(cursor dot)
{
	if (dot == nullptr)
		return 0;
	//adds 1 to height if there's either a left or right child
	return std::max(height_two(dot->childl), height_two(dot->childr)) + 1;


}

//calls height_two function that calucates height
template <typename KeyType, typename ValueType>
std::size_t Treap<KeyType, ValueType>::height()
{
	// calling the recursive function
	return height_two(veryTopNode);

}


//copies nodes from one place to another
template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::copier(cursor dot)
{
	if (dot != nullptr)
	{
		//left first (in order traversal)
		copier(dot->childl);
		//insert data
		insert(dot->key, dot->data);
		//copies right at last
		copier(dot->childr);
	}
}

#endif