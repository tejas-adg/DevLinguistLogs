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

		Node(const K& k, const V& d, Node* p = nullptr) : key(k), data(d), parent(p), childl(nullptr), childr(nullptr), priority(0)
		{

		}
	};

	typedef Node<KeyType, ValueType>* node_ptr;

	node_ptr root;

	node_ptr search_node(node_ptr node, const KeyType& key, bool& found);

	node_ptr insert_node(node_ptr node, const KeyType& key, const ValueType& value, node_ptr parent);

	node_ptr remove_node(node_ptr node, const KeyType& key);

	node_ptr rotate_left(node_ptr node);

	node_ptr rotate_right(node_ptr node);

	void copy_nodes(node_ptr node);

	std::size_t height_node(node_ptr node);
};
template <typename KeyType, typename ValueType>
std::size_t Treap<KeyType, ValueType>::height_node(node_ptr node)
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
void Treap<KeyType, ValueType>::copy_nodes(node_ptr node)
{
	if (node != nullptr)
	{

		this->copy_nodes(node->childl);
		this->insert(node->key, node->data);
		this->copy_nodes(node->childr);
	}
}
template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::Treap(const Treap& rhs)
{
	std::random_device rd;
	this->rndgen.seed(rd());

	this->root = nullptr;
	this->copy_nodes(rhs.root);
}

template <typename KeyType, typename ValueType>
typename Treap<KeyType, ValueType>::node_ptr Treap<KeyType, ValueType>::remove_node(node_ptr node, const KeyType& key)
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
		node_ptr temp = node->childr;
		delete node;
		node = temp;
	}
	else if (node->childr == nullptr)
	{
		node_ptr temp = node->childl;
		delete node;
		node = temp;
	}
	else if (node->childl->priority < node->priority)
	{
		node = this->rotate_left(node);
		node->childl = this->remove_node(node->childl, key);
	}
	else
	{
		node = this->rotate_right(node);
		node->childr = this->remove_node(node->childr, key);
	}

	return node;
}

template <typename KeyType, typename ValueType>
typename Treap<KeyType, ValueType>::node_ptr Treap<KeyType, ValueType>::rotate_left(node_ptr node)
{
	node_ptr a = node->childr, b = node;

	if (this->root == b)
	{
		this->root = a;
		this->root->parent = nullptr;
	}
	else
	{
		if (b == ((b->parent)->childr))
		{
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
	//node = a;
	return a;
}

template <typename KeyType, typename ValueType>
typename Treap<KeyType, ValueType>::node_ptr Treap<KeyType, ValueType>::rotate_right(node_ptr node)
{
	node_ptr a = node->childl, b = node;

	if (this->root == b)
	{
		this->root = a;
		this->root->parent = nullptr;
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
	//node = a;
	return a;
}

template <typename KeyType, typename ValueType>
typename Treap<KeyType, ValueType>::node_ptr Treap<KeyType, ValueType>::insert_node(node_ptr node, const KeyType& key, const ValueType& value, node_ptr parent)
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
typename Treap<KeyType, ValueType>::node_ptr Treap<KeyType, ValueType>::search_node(node_ptr node, const KeyType& key, bool& found)
{
	if (node == nullptr)
	{
		found = false;
		return nullptr;
	}

	if (node->key == key)
	{
		found = true;
		return node;
	}

	if (node->key < key)
	{
		return this->search_node(node->childr, key, found);
	}
	else
	{
		return this->search_node(node->childl, key, found);
	}
}

template <typename KeyType, typename ValueType>
std::size_t Treap<KeyType, ValueType>::height()
{
	return this->height_node(this->root);
}

template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::remove(const KeyType& key)
{
	this->root = this->remove_node(this->root, key);
}

template <typename KeyType, typename ValueType>
ValueType Treap<KeyType, ValueType>::search(const KeyType& key, bool& found)
{
	node_ptr p = search_node(this->root, key, found);

	if (p == nullptr)
	{
		return ValueType();
	}

	return p->data;
}

template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
	this->root = insert_node(this->root, key, value, nullptr);
}

template <typename KeyType, typename ValueType>
bool Treap<KeyType, ValueType>::empty()
{
	return (this->root == nullptr);
}

template <typename KeyType, typename ValueType>
void Treap<KeyType, ValueType>::swap(Treap& x, Treap& y)
{
	std::swap(x.root, y.root);
}

template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>& Treap<KeyType, ValueType>::operator=(Treap rhs)
{
	this->swap((*this), rhs);
	return (*this);
}

template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::~Treap()
{
	while (!this->empty())
	{
		this->remove(this->root->key);
	}
}

template <typename KeyType, typename ValueType>
Treap<KeyType, ValueType>::Treap()
{
	std::random_device rd;
	this->rndgen.seed(rd());

	this->root = nullptr;
}

#endif