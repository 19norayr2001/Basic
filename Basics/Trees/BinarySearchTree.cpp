#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree()
	:m_root(nullptr)
{}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& obj)
	:m_root(nullptr)
{
	allocate(obj);
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& obj)
{
	if (this != &obj)
	{
		deallocate(m_root);
		allocate(obj);
	}
	return *this;
}

BinarySearchTree::~BinarySearchTree()
{
	deallocate(m_root);
}

void BinarySearchTree::insert(const int& value)
{
	if (m_root == nullptr)
	{
		m_root = new Node(value);
		nill(m_root);
		return;
	}
	Node* ptr = insert_node(value);
	nill(ptr);
}

void BinarySearchTree::remove(const int& value)
{
	if (!find(value))
	{
		return;
	}
	Node* ptr = remove_node(value);
	replace_child(ptr);
	if (is_nill(m_root))
	{
		delete m_root;
		m_root = nullptr;
	}
}

bool BinarySearchTree::find(const int& value) const
{
	Node* ptr = find_node(value);
	return ptr != nullptr && !is_nill(ptr);
}

void BinarySearchTree::allocate(const BinarySearchTree& obj)
{
	if (obj.empty())
	{
		*this = BinarySearchTree();
		return;
	}
	m_root = new Node(obj.m_root->value);
	alloc_help(m_root, obj.m_root);
}

void BinarySearchTree::alloc_help(Node* root1, Node* root2)
{
	if (root2->llink != nullptr)
	{
		root1->llink = new Node(root2->llink->value);
		alloc_help(root1->llink, root2->llink);
	}
	else
	{
		root1->llink = nullptr;
	}
	if (root2->rlink != nullptr)
	{
		root1->rlink = new Node(root2->rlink->value);
		alloc_help(root1->rlink, root2->rlink);
	}
	else
	{
		root1->rlink = nullptr;
	}
}

void BinarySearchTree::nill(Node* ptr) const
{
	ptr->llink = new Node();
	ptr->rlink = new Node();
}

void BinarySearchTree::deallocate(Node* root)
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

Node* BinarySearchTree::insert_node(const int& value)
{
	Node* ptr = m_root;
	do
	{
		if (ptr->value > value)
			ptr = ptr->llink;
		else
			ptr = ptr->rlink;
	} while (!is_nill(ptr));
	ptr->value = value;
	return ptr;
}

Node* BinarySearchTree::remove_node(const int& value)
{
	Node* ptr = find_node(value);
	Node* nextptr = next(ptr);
	int temp = ptr->value;
	ptr->value = nextptr->value;
	nextptr->value = temp;
	ptr = nextptr;
	Node* child = is_nill(ptr->llink) ? ptr->rlink : ptr->llink;
	return ptr;
}

Node* BinarySearchTree::find_node(const int& value) const
{
	Node* ptr = m_root;
	if (m_root == nullptr)
	{
		return m_root;
	}
	while (!is_nill(ptr) && ptr->value != value)
	{
		if (ptr->value > value)
		{
			ptr = ptr->llink;
		}
		else
		{
			ptr = ptr->rlink;
		}
	}
	return ptr;
}

Node* BinarySearchTree::next(Node* p) const
{
	Node* ret = p;
	p = p->llink;
	while (!is_nill(p))
	{
		ret = p;
		p = p->rlink;
	}
	return ret;
}

void BinarySearchTree::replace_child(Node* ptr)
{
	Node* child = is_nill(ptr->llink) ? ptr->rlink : ptr->llink;
	Node* brother = is_nill(ptr->llink) ? ptr->llink : ptr->rlink;
	delete brother;
	ptr->value = child->value;
	ptr->llink = child->llink;
	ptr->rlink = child->rlink;
	delete child;
}