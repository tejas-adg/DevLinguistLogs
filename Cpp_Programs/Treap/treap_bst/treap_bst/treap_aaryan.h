#pragma once

#ifndef _TREAP_H_
#define _TREAP_H_

#include <random>
#include <iostream>

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
	// random number generator
	std::mt19937 rndgen;
	std::size_t Height_length;
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

	Node<KeyType, ValueType>* rt;

	void rl(Node<KeyType, ValueType>*& b); 
	void rr(Node<KeyType, ValueType>*& a);
	Node<KeyType, ValueType>* remove_node(Node<KeyType, ValueType>* node, const KeyType& key);


	// You may add private member variables/methods as needed.
};

template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::Node<KeyType, ValueType>* Treap<KeyType, ValueType>::remove_node(Node<KeyType, ValueType>* node, const KeyType& key)
{
	if (node == nullptr)
	{
		return node;
	}

	if (key < node->key)
	{
		node->childl = this->remove_node(node->childl, key);
	}
	else if (key > node->key)
	{
		node->childr = this->remove_node(node->childr, key);
	}
	else if (node->childl == nullptr)
	{
		Node<KeyType, ValueType>* temp = node->childr;
		delete node;
		node = temp;
	}
	else if (node->childr == nullptr)
	{
		Node<KeyType, ValueType>* temp = node->childl;
		delete node;
		node = temp;
	}
	else if (node->childl->priority < node->priority)
	{
		this->rl(node);
		node->childl = this->remove_node(node->childl, key);
	}
	else
	{
		this->rr(node);
		node->childr = this->remove_node(node->childr, key);
	}

	return node;
}

// this is the constructor
// in this function we get a new seed value
template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::Treap()
{
	std::random_device rd;
	rndgen.seed(rd()); // rd is a non repetitivie random number generator

	this->rt = nullptr;
	this->Height_length = 0;
}


template<typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::~Treap()
{
	//std::cout << "In the destructor\n";
	   // in the destructure we remove nodes
	while (!this->empty())
	{
		this->remove(this->rt->key);
	}
	//std::cout << "Done with the destructor\n";
}

// in the copy constuctor 
template<typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::Treap(const Treap& rhs)
{
	// setting root to null
	this->rt = nullptr;
	this->Height_length = 0;
}

template<typename KeyType, typename ValueType>
Treap<KeyType, ValueType>& Treap<KeyType, ValueType>::operator=(Treap rhs)
{
	// TODO: insert return statement here
	swap(*this, rhs);
	return *this;
}
// this is the swap function
template<typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::swap(Treap& x, Treap& y)
{
	std::swap(x.rt, y.rt); // in this line we swap x and y
}

template<typename KeyType, typename ValueType>
bool Treap<KeyType, ValueType>::empty()
{
	// returning if the root is empty
	return (this->rt == nullptr);
}


template<typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
	//this checks if the root is at a null pointer or not
	// if its at null
	if (this->rt == nullptr)
	{
		this->rt = new Node<KeyType, ValueType>(key, value);
		this->rt->priority = this->rndgen();
		return;
	}

	// finding the right key
	Node<KeyType, ValueType>* tempval = this->rt; // temp value for root
	Node<KeyType, ValueType>* tempval_p = nullptr; // temp val for the parent

	while (tempval != nullptr) // if the statement is true then the places are checked and the position of the child is found
	{
		// no keys can be similar every key is unique
		if (tempval->key == key) // if the key is equal to the key then the place is already present 
		{
			throw std::logic_error(" there is a key present");
		}

		if (tempval->key > key) // checking if the temp key is greater than the key
		{
			tempval_p = tempval; // setting the parent to the key of the root
			tempval = tempval->childl;// setting to the left
			continue;
		}

		if (tempval->key < key)// checking if temp key is lesser than the key
		{
			tempval_p = tempval; // setting the parent to the key to the root
			tempval = tempval->childr; // setting to the right
			continue;
		}
	}
	// making a new node of the temp val to store the 
	tempval = new Node<KeyType, ValueType>(key, value);
	tempval->priority = this->rndgen();
	// setting the new parent 
	tempval->parent = tempval_p;

	// checking if the parent is not null and the key is greater than parent 
	if ((tempval_p != nullptr) && (tempval->key > tempval_p->key))
	{
		// setting the child right to the node
		tempval_p->childr = tempval;
	}
	// if the parent is not null and the key is lesser than parent
	else if ((tempval_p != nullptr) && (tempval->key < tempval_p->key))
	{
		//setting the child left to the node
		tempval_p->childl = tempval;
	}
	// loop when the parent is not null and the parent priority is lesser than the nodes priority 
	while ((tempval_p != nullptr) && (tempval_p->priority < tempval->priority))
	{

		if (tempval == tempval_p->childl)
		{
			// calling the rotate right of the parent node
			this->rr(tempval_p);
		}
		else if (tempval == tempval_p->childr)
		{
			// calling rotate left of the parent node
			this->rl(tempval_p);
		}

		if (tempval_p != nullptr)
			tempval_p = tempval_p->parent;
	}
}

template<typename KeyType, typename ValueType>
ValueType Treap<KeyType, ValueType>::search(const KeyType& key, bool& found)
{
	Node<KeyType, ValueType>* tempval = this->rt;
	while (tempval != nullptr)
	{
		//std::cout << "at the key: " << tempval->key << std::endl;
			  // no keys can be similar every key is unique
		if (tempval->key == key) // if the key is equal to the key then the place is already present 
		{
			break;
		}

		if (tempval->key > key) // checking if the temp key is greater than the key
		{
			tempval = tempval->childl;// setting to the left	
		}

		if (tempval->key < key)// checking if temp key is lesser than the key
		{
			tempval = tempval->childr; // setting to the right
		}

	}
	//std::cout << "searched the key: " << tempval->key << " key = " << key << std::endl;
	if (tempval == nullptr)
	{
		found = false;
		return ValueType();
	}
	//std::cout << "it is found!\n";
	found = true;
	return tempval->data;
}

template<typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::remove(const KeyType& key)
{
	this->rt = this->remove_node(this->rt, key);
}
// need to implement this
template<typename KeyType, typename ValueType>
std::size_t Treap<KeyType, ValueType>::height()
{
	return this->Height_length;
}

// rotating to the left
template<typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::rl(Node<KeyType, ValueType>*& b)
{
	Node<KeyType, ValueType>* z = b->childr;

	if (this->rt == b)
	{
		this->rt = z;
		this->rt->parent = nullptr;
	}
	else
	{
		if (b == b->parent->childr)
		{
			b->parent->childr = z;
		}
		else
		{
			b->parent->childl = z;
		}
		z->parent = b->parent;
	}
	b->childr = z->childl;
	if (z->childl != nullptr)
	{
		z->childl->parent = b;
	}
	z->childl = b;
	z->parent = b->parent;
	b->parent = z;
	b = z;
}

// for rotating to the right
template<typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::rr(Node<KeyType, ValueType>*& a)
{
	Node<KeyType, ValueType>* z = a->childl;

	if (this->rt == a)
	{
		this->rt = z;
		this->rt->parent = nullptr;
	}
	else
	{
		if (a == ((a->parent)->childl))
		{
			a->parent->childl = z;
		}
		else
		{
			a->parent->childr = z;
		}
		z->parent = a->parent;
	}

	a->childl = z->childr;
	if (z->childr != nullptr)
	{
		z->childr->parent = a;
	}
	z->childr = a;
	z->parent = a->parent;
	a->parent = z;
	a = z;
}

#endif