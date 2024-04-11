#pragma once
#ifndef ABSTRACT_BST_HPP
#define ABSTRACT_BST_HPP

template <typename KeyType, typename ValueType>
class AbstractBST
{
public:
	virtual bool empty() = 0;

	virtual ValueType search(const KeyType& key, bool& found) = 0;

	virtual void insert(const KeyType& key, const ValueType& value) = 0;

	virtual void remove(const KeyType& key) = 0;
};

#endif