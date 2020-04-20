#include "ListSearchTree.h"

ListSearchTree::ListSearchTree()
	:m_root(nullptr)
	,m_size(0)
{}

ListSearchTree::ListSearchTree(const ListSearchTree& obj)
	: m_root(nullptr)
	, m_size(obj.m_size)
{
	allocate(obj);
}

ListSearchTree& ListSearchTree::operator=(const ListSearchTree& obj)
{
	if (this != &obj)
	{
		deallocate(m_root);
		allocate(obj);
	}
	return *this;
}

ListSearchTree::~ListSearchTree()
{
	deallocate(m_root);
}

int ListSearchTree::find(int k) const
{
	if (k <= m_size)
	{
		Node* ptr = m_root;
		while (!is_leaf(ptr))
		{
			InternalNode* pointer = dynamic_cast<InternalNode*>(ptr);
			if (pointer->left_count_leaves >= k)
			{
				ptr = ptr->llink;
			}
			else
			{
				k -= pointer->left_count_leaves;
				ptr = ptr->rlink;
			}
		}
		ExternalNode* pointer = dynamic_cast<ExternalNode*>(ptr);
		return pointer->value;
	}
}

void ListSearchTree::insert(const int& val, int k)
{
	Node* ptr = m_root;
	Node* parent = nullptr;
	Node* Node::*link = nullptr;
	if (m_root == nullptr)
	{
		m_size++;
		m_root = new ExternalNode(val);
		return;
	}
	while (!is_leaf(ptr))
	{
		InternalNode* pointer = dynamic_cast<InternalNode*>(ptr);
		parent = ptr;
		if (pointer->left_count_leaves >= k)
		{
			(pointer->left_count_leaves)++;
			ptr = ptr->llink;
			link = &Node::llink;
		}
		else
		{
			k -= pointer->left_count_leaves;
			ptr = ptr->rlink;
			link = &Node::rlink;
		}
	}
	if (parent != nullptr)
	{
		parent->*link = new InternalNode(1);
		parent = parent->*link;
	}
	else
	{
		m_root = parent = new InternalNode(1);
	}
	ExternalNode* pointer = dynamic_cast<ExternalNode*>(ptr);
	if (k == 1)
	{
		parent->rlink = pointer;
		parent->llink = new ExternalNode(val);
	}
	else
	{
		parent->llink = pointer;
		parent->rlink = new ExternalNode(val);
	}
	m_size++;
}

void ListSearchTree::remove(int k)
{
	Node* ptr = m_root;
	Node* parent = nullptr;
	Node* Node::* link = nullptr;
	if (k > m_size)
	{
		return;
	}
	while (!is_leaf(ptr))
	{
		InternalNode* pointer = dynamic_cast<InternalNode*>(ptr);
		parent = ptr;
		if (pointer->left_count_leaves >= k)
		{
			(pointer->left_count_leaves)--;
			ptr = ptr->llink;
			link = &Node::llink;
		}
		else
		{
			k -= pointer->left_count_leaves;
			ptr = ptr->rlink;
			link = &Node::rlink;
		}
	}
	delete (parent->*link);
	m_size--;
	if (m_size == 0)
	{
		m_root = nullptr;
	}
}
void ListSearchTree::allocate(const ListSearchTree& obj)
{
	if (obj.empty())
	{
		*this = ListSearchTree();
		return;
	}
	ExternalNode* ptr = dynamic_cast<ExternalNode*>(obj.m_root);
	if (ptr != nullptr)
	{
		m_root = new ExternalNode(ptr->value);
	}
	else
	{
		InternalNode* ptr = dynamic_cast<InternalNode*>(obj.m_root);
		m_root = new InternalNode(ptr->left_count_leaves);
	}
	alloc_help(m_root, obj.m_root);
}
void ListSearchTree::deallocate(const Node* const root) const
{
	if (root == nullptr)
		return;
	Node* left = root->llink;
	Node* right = root->rlink;
	delete root;
	if (left != nullptr)
	{
		deallocate(left);
	}
	if (right != nullptr)
	{
		deallocate(right);
	}
}

void ListSearchTree::alloc_help(Node* const root1, Node* const root2) const
{
	if (root2->llink != nullptr)
	{
		ExternalNode* ptr = dynamic_cast<ExternalNode*>(root2->llink);
		if (ptr != nullptr)
		{
			root1->llink = new ExternalNode(ptr->value);
		}
		else
		{
			InternalNode* ptr = dynamic_cast<InternalNode*>(root2->llink);
			root1->llink = new InternalNode(ptr->left_count_leaves);
		}
		alloc_help(root1->llink, root2->llink);
	}
	else
	{
		root1->llink = nullptr;
	}
	if (root2->rlink != nullptr)
	{
		ExternalNode* ptr = dynamic_cast<ExternalNode*>(root2->rlink);
		if (ptr != nullptr)
		{
			root1->rlink = new ExternalNode(ptr->value);
		}
		else
		{
			InternalNode* ptr = dynamic_cast<InternalNode*>(root2->rlink);
			root1->rlink = new InternalNode(ptr->left_count_leaves);
		}
		alloc_help(root1->rlink, root2->rlink);
	}
	else
	{
		root1->rlink = nullptr;
	}
}