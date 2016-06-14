#pragma once
#include<iostream>

using namespace std;


enum Color
{
	RED,
	BLACK
};

template<class K,class V>
struct RBNode
{
	RBNode<K, V>* _left;
	RBNode<K, V>* _right;
	RBNode<K, V>* _parent;
	K _key;
	V _value;
	Color _color;
	RBNode(const K& key, const V& value)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(value)
		, _color(RED)
	{}
};

template<class K,class V>
class RBTree
{
public:
	typedef RBNode<K, V> Node;
	RBTree()
		:_root(NULL)
	{}
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_color = BLACK;
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			parent = cur;
			if (cur->_key > key)
				cur = cur->_left;
			else if (cur->_key < key)
				cur = cur->_right;
			else
				return false;
		}
		cur = new Node(key, value);
		cur->_parent = parent;
		if (parent->_key > key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		if (parent->_color == BLACK)//如果插入的结点的父节点是黑色，那么不必调整
			return true;
		while (cur != _root &&cur->_color == RED&& parent->_color == RED)
		{
			Node* grandpa = parent->_parent;
			Node* uncle = NULL;
			if (parent == grandpa->_left)
				uncle = grandpa->_right;
			else
				uncle = grandpa->_left;
			if (uncle&&uncle->_color == RED)
			{
				grandpa->_color = RED;
				uncle->_color = BLACK;
				parent->_color = BLACK;
			}
			else
			{
				if (grandpa->_left == parent&&parent->_left == cur)
				{
					_RotateR(grandpa);
					grandpa->_color = RED;
					parent->_color = BLACK;
					cur->_color = RED;
				}
				if (grandpa->_right == parent&&parent->_right == cur)
				{
					_RotateL(grandpa);
					parent->_color = BLACK;
					grandpa->_color = RED;
				}
				if (grandpa->_left == parent&&parent->_right == cur)
				{
					_RotateLR(grandpa);
					cur->_color = BLACK;
					grandpa->_color = RED;
				}
				if (grandpa->_right == parent&&parent->_left == cur)
				{
					_RotateRL(grandpa);
					cur->_color = BLACK;
					grandpa->_color = RED;

				}
			}
			_root->_color = BLACK;
			cur = parent;
			parent = cur->_parent;
		}
		_root->_color = BLACK;
		return true;
	}
	bool Isbalance()
	{
		return _Isbalance();
	}
protected:
	bool _Isbalance()
	{

	}
	void _RotateR(Node*& parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* pNode = parent->_parent;
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		parent->_parent = subL;
		parent = subL;
		subL->_parent = pNode;
		
		if (pNode == NULL)
		{
			_root = subL;
		}
		else
		{
			if (pNode->_key > subL->_key)
			{
				pNode->_left = subL;
			}
			else
			{
				pNode->_right = subL;
			}
		}
	}
	void _RotateL(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* pNode = parent->_parent;
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		parent->_parent = subR;

		parent = subR;
		parent->_parent = pNode;

		if (pNode == NULL)
		{
			_root = subR;
		}
		else
		{
			if (pNode->_key > subR->_key)
			{
				pNode->_left = subR;
			}
			else
			{
				pNode->_right = subR;
			}
		}
	}
	void _RotateRL(Node* parent)
	{
		_RotateR(parent->_right);
		_RotateL(parent);
	}
	void _RotateLR(Node* parent)
	{
		_RotateL(parent->_left);
		_RotateR(parent);
	}

protected:
	Node* _root;
};
