#pragma once

// START OF HPP

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

	Node<KeyType, ValueType>* top;

	Node<KeyType, ValueType>* rotate_left(Node<KeyType, ValueType>* node);

	Node<KeyType, ValueType>* rotate_right(Node<KeyType, ValueType>* node);

	Node<KeyType, ValueType>* insert_node(Node<KeyType, ValueType>* node, const KeyType& key, const ValueType& value, Node<KeyType, ValueType>* parent);

	std::size_t height_node(Node<KeyType, ValueType>* node);
};

// END OF HPP
// 
// START OF TXX

template <typename KeyType, typename ValueType>
std::size_t Treap<KeyType, ValueType>::height_node(Node<KeyType, ValueType>* node)
{
	if (node == nullptr)
	{
		return 0;
	}
	else
	{
		return std::max(this->height_node(node->childl), this->height_node(node->childr)) + 1;
	}
}

template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::Node<KeyType, ValueType>* Treap<KeyType, ValueType>::insert_node(Node<KeyType, ValueType>* node, const KeyType& key, const ValueType& value, Node<KeyType, ValueType>* parent)
{
	if (node == nullptr)
	{
		node = new Node<KeyType, ValueType>(key, value);
		node->priority = this->rndgen();
		node->parent = parent;
		node->childl = nullptr;
		node->childr = nullptr;
		return node;
	}

	if (key < node->key)
	{
		node->childl = this->insert_node(node->childl, key, value, node);

		if (node->childl->priority > node->priority)
		{
			node = this->rotate_right(node);
		}
	}
	else if (key > node->key)
	{
		node->childr = this->insert_node(node->childr, key, value, node);

		if (node->childr->priority > node->priority)
		{
			node = this->rotate_left(node);
		}
	}

	return node;
}

template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::remove(const KeyType& key)
{
	Node<KeyType, ValueType>* temp = this->top;

	while (temp != nullptr)
	{
		if (temp->key == key)
			break;

		if (key < temp->key)
			temp = temp->childl;

		else if (key > temp->key)
			temp = temp->childr;
	}

	if (temp == nullptr)
	{
		throw std::logic_error("Arreeeyyyy treap is empty!!");
	}

	while ((temp->childl != nullptr) && (temp->childr != nullptr))
	{
		if (temp->childl->priority < temp->childr->priority)
		{
			temp = this->rotate_left(temp);
		}
		else if (temp->childl->priority > temp->childr->priority)
		{
			temp = this->rotate_right(temp);
		}

		temp = this->top;

		while (temp != nullptr)
		{
			if (temp->key == key)
				break;

			if (key < temp->key)
				temp = temp->childl;

			else if (key > temp->key)
				temp = temp->childr;
		}
	}

	temp = this->top;

	while (temp != nullptr)
	{
		if (temp->key == key)
			break;

		if (key < temp->key)
			temp = temp->childl;

		else if (key > temp->key)
			temp = temp->childr;
	}

	if ((temp->childl == nullptr) && (temp->childr == nullptr))
	{
		if (temp->parent != nullptr)
		{
			if (temp == temp->parent->childl)
			{
				temp->parent->childl = nullptr;
			}
			else if (temp == temp->parent->childr)
			{
				temp->parent->childr = nullptr;
			}
			temp->parent = nullptr;
		}

		if (temp == this->top)
		{
			this->top = nullptr;
		}

		delete temp;
		temp = nullptr;
		return;
	}

	if (((temp->childl == nullptr) && (temp->childr != nullptr)) || ((temp->childl != nullptr) && (temp->childr == nullptr)))
	{
		/*
		* 1. change it's one child's parent
		* 2. and link current's parent to current's child
		* 3. destroy 3 links:
		*	a. current's parent to current
		*	b. current to its parent
		*	c. current to it's only child
		* 4. delete current
		* 
		*/

		if (temp->childl != nullptr)
		{
			temp->childl->parent = temp->parent;

			if (this->top == temp)
			{
				this->top = temp->childl;
			}
		}
		else if (temp->childr != nullptr)
		{
			temp->childr->parent = temp->parent;

			if (this->top == temp)
			{
				this->top = temp->childr;
			}
		}

		if ((temp->parent != nullptr) && (temp == temp->parent->childl))
		{
			if (temp->childl != nullptr)
			{
				temp->parent->childl = temp->childl;
			}
			else if (temp->childr != nullptr)
			{
				temp->parent->childl = temp->childr;
			}
		}
		else if ((temp->parent != nullptr) && (temp == temp->parent->childr))
		{
			if (temp->childl != nullptr)
			{
				temp->parent->childr = temp->childl;
			}
			else if (temp->childr != nullptr)
			{
				temp->parent->childr = temp->childr;
			}
		}

		if (temp->parent != nullptr)
		{
			temp->parent = nullptr;
		}

		if (temp->childl != nullptr)
		{
			temp->childl = nullptr;
		}
		else if (temp->childr != nullptr)
		{
			temp->childr = nullptr;
		}

		delete temp;
		temp = nullptr;
	}
}

template <typename KeyType, typename ValueType>
ValueType Treap<KeyType, ValueType>::search(const KeyType& key, bool& found)
{
	Node<KeyType, ValueType>* temp = this->top;

	while (temp != nullptr)
	{
		if (temp->key == key)
			break;

		if (key < temp->key)
			temp = temp->childl;

		else if (key > temp->key)
			temp = temp->childr;
	}

	if (temp == nullptr)
	{
		found = false;
		return ValueType();
	}

	found = true;
	return temp->data;
}

template <typename KeyType, typename ValueType>
std::size_t Treap<KeyType, ValueType>::height()
{
	return 0;
}

template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::Node<KeyType, ValueType>* Treap<KeyType, ValueType>::rotate_left(Node<KeyType, ValueType>* node)
{
	Node<KeyType, ValueType>* x = node->childr;

	if (this->top == node)
	{
		this->top = x;
		this->top->parent = nullptr;
	}
	else
	{
		if (node == node->parent->childr)
		{
			node->parent->childr = x;
		}
		else
		{
			node->parent->childl = x;
		}
		x->parent = node->parent;
	}

	node->childr = x->childl;

	if (x->childl != nullptr)
	{
		x->childl->parent = node;
	}

	x->childl = node;
	x->parent = node->parent;
	node->parent = x;
	//b = z;
	return x;
}

template<typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::Node<KeyType, ValueType>* Treap<KeyType, ValueType>::rotate_right(Node<KeyType, ValueType>* node)
{
	Node<KeyType, ValueType>* temp = node->childl;

	if (this->top == node)
	{
		this->top = temp;
		this->top->parent = nullptr;
	}
	else
	{
		if (node == ((node->parent)->childl))
		{
			node->parent->childl = temp;
		}
		else
		{
			node->parent->childr = temp;
		}
		temp->parent = node->parent;
	}

	node->childl = temp->childr;
	if (temp->childr != nullptr)
	{
		temp->childr->parent = node;
	}

	temp->childr = node;
	temp->parent = node->parent;
	node->parent = temp;
	//a = z;
	return temp;
}

template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
	//this->top = this->insert_node(this->top, key, value, nullptr);
	// if the treap is empty then we populate the top directly
	if (this->top == nullptr)
	{
		this->top = new Node<KeyType, ValueType>(key, value);
		this->top->priority = this->rndgen();
		return;
	}

	// a temp node to find the right node
	Node<KeyType, ValueType>* temp = this->top;
	// this node will store the parent of temp
	Node<KeyType, ValueType>* temp_parent = nullptr;

	/*
	* Binary search our way into finding the right spot to insert the new node
	* */
	while (temp != nullptr)
	{
		if (temp->key == key)
		{
			throw std::logic_error("Key already exists");
		}
		
		if (key < temp->key)
		{
			temp_parent = temp;
			temp = temp->childl;
			continue;
		}

		if (key > temp->key)
		{
			temp_parent = temp;
			temp = temp->childr;
			continue;
		}
	}

	// after the while loop we have the right spot we have to insert it in

	temp = new Node<KeyType, ValueType>(key, value); // instantiating
	temp->priority = this->rndgen(); // giving the new node a priority
	temp->parent = temp_parent; // establishing the child-parent relation

	// establishing the parent-child relation
	if ((temp_parent != nullptr) && (temp->key > temp_parent->key))
	{
		temp_parent->childr = temp;

		/*if (temp_parent->priority < temp->priority)
		{
			temp_parent = this->rotate_left(temp_parent);
		}*/
	}
	else if ((temp_parent != nullptr) && (temp->key < temp_parent->key))
	{
		temp_parent->childl = temp;

		/*if (temp_parent->priority < temp->priority)
		{
			temp_parent = this->rotate_right(temp_parent);
		}*/
	}

	while ((temp_parent != nullptr) && (temp_parent->priority < temp->priority))
	{
		if (temp == temp_parent->childl)
		{
			temp_parent = this->rotate_right(temp_parent);
		}
		else if (temp == temp_parent->childr)
		{
			temp_parent = this->rotate_left(temp_parent);
		}

		temp_parent = temp_parent->parent;
	}
}

template <typename KeyType, typename ValueType>
bool Treap<KeyType, ValueType>::empty()
{
	return this->top == nullptr;
}

template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::~Treap()
{
	while (!this->empty())
	{
		this->remove(this->top->key);
	}
}

template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::Treap()
{
	std::random_device rd; // used to get a seed value
	this->rndgen.seed(rd()); // seeds the psudo random number generator

	// setting the first node of the tree to nullptr
	this->top = nullptr;
}

// END OF TXX

#endif