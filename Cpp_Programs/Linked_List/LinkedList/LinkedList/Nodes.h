#pragma once
#ifndef _NODES_H_
#define _NODES_H_

template<typename T>
class Single_Link_Node
{
private:
	 T obj;
	 Single_Link_Node<T>* nextNode;

public:
	Single_Link_Node();
	~Single_Link_Node();

	T getData(void);
	void setData(T);
	Single_Link_Node<T>* getNextNode(void);
	void setNextNode(Single_Link_Node<T>*);
	static Single_Link_Node<T>* createNode(T);
};

template<typename T>
Single_Link_Node<T>* Single_Link_Node<T>::createNode(T Obj)
{
	Single_Link_Node<T>* new_node_ptr = new Single_Link_Node<T>();
	new_node_ptr->setData(Obj);
	new_node_ptr->setNextNode(nullptr);

	return new_node_ptr;
}

template<typename T>
Single_Link_Node<T>::Single_Link_Node()
{
	obj = 0;
	nextNode = nullptr;
}

template<typename T>
Single_Link_Node<T>::~Single_Link_Node()
{
	obj = 0;
	nextNode = nullptr;
}

template<typename T>
T Single_Link_Node<T>::getData()
{
	return obj;
}

template<typename T>
void Single_Link_Node<T>::setData(T _obj)
{
	obj = _obj;
}

template<typename T>
Single_Link_Node<T>* Single_Link_Node<T>::getNextNode()
{
	return nextNode;
}

template<typename T>
void Single_Link_Node<T>::setNextNode(Single_Link_Node<T>* _next_Node)
{
	nextNode = _next_Node;
}


template<typename T>
class Double_Link_Node
{
private:
	T obj;
	Double_Link_Node<T>* nextNode;
	Double_Link_Node<T>* previousNode;

public:
	Double_Link_Node();
	~Double_Link_Node();

	T getData(void);
	void setData(T);
	Double_Link_Node<T>* getNextNode(void);
	void setNextNode(Double_Link_Node<T>*);
	Double_Link_Node<T>* getPreviousNode(void);
	void setPreviousNode(Double_Link_Node<T>*);
	static Double_Link_Node<T>* create_node(T);
};

template<typename T>
Double_Link_Node<T>* Double_Link_Node<T>::create_node(T obj)
{
	Double_Link_Node<T>* new_node_ptr = new Double_Link_Node<T>();
	new_node_ptr->setData(obj);
	new_node_ptr->setNextNode(nullptr);
	new_node_ptr->setPreviousNode(nullptr);

	return new_node_ptr;
}

template<typename T>
Double_Link_Node<T>::Double_Link_Node()
{
	obj = 0;
	nextNode = nullptr;
	previousNode = nullptr;
}

template<typename T>
Double_Link_Node<T>::~Double_Link_Node()
{
	obj = 0;
	nextNode = nullptr;
	previousNode = nullptr;
}

template<typename T>
T Double_Link_Node<T>::getData()
{
	return obj;
}

template<typename T>
void Double_Link_Node<T>::setData(T _obj)
{
	obj = _obj;
}

template<typename T>
Double_Link_Node<T>* Double_Link_Node<T>::getNextNode()
{
	return nextNode;
}

template<typename T>
void Double_Link_Node<T>::setNextNode(Double_Link_Node<T>* _nextNode)
{
	nextNode = _nextNode;
}

template<typename T>
Double_Link_Node<T>* Double_Link_Node<T>::getPreviousNode()
{
	return previousNode;
}

template<typename T>
void Double_Link_Node<T>::setPreviousNode(Double_Link_Node<T>* _previousNode)
{
	previousNode = _previousNode;
}
#endif