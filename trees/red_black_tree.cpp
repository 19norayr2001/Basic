#include "red_black_tree.h"

RBTree::RBTree()
	:m_root(nullptr)
	, m_size(0)
{}

RBTree::RBTree(const RBTree& obj)
	: m_root(nullptr)
	, m_size(obj.m_size)
{
	allocate(obj);
}

RBTree& RBTree::operator=(const RBTree& obj)
{
	if (this != &obj)
	{
		deallocate(m_root);
		allocate(obj);
	}
	return *this;
}

RBTree::~RBTree()
{
	deallocate(m_root);
}

void RBTree::insert(const int& val)
{
	m_size++;
	if (m_root == nullptr)
	{
		get_root() = m_root = new RBNode(val);
		nill(m_root);
		return;
	}
	RBNode* ptr = dynamic(insert_node(val));
	nill(ptr);
	uncle_part_insert(ptr, val);
}

void RBTree::remove(const int& val)
{

	if (!find(val))
	{
		return;
	}
	m_size--;
	RBNode* ptr = dynamic(remove_node(val));
	replace_child(ptr);
	if (!ptr->color)
	{
		ptr->color = true;
		return;
	}
	remove_part1(ptr);
}

void RBTree::allocate(const RBTree& obj)
{
	if (obj.empty())
	{
		*this = RBTree();
		return;
	}
	get_root() = m_root = new RBNode(obj.m_root->value);
	alloc_help(m_root, obj.m_root);
}

void RBTree::alloc_help(RBNode* root1, RBNode* root2)
{
	RBNode* din = nullptr;
	if (root2->llink != nullptr)
	{
		din = dynamic(root2->llink);
		root1->llink = new RBNode(din->value, din->color, root1);
		alloc_help(dynamic(root1->llink), dynamic(root2->llink));
	}
	else
	{
		root1->llink = nullptr;
	}
	if (root2->rlink != nullptr)
	{
		din = dynamic(root2->rlink);
		root1->rlink = new RBNode(din->value, din->color, root1);
		alloc_help(dynamic(root1->rlink), dynamic(root2->rlink));
	}
	else
	{
		root1->rlink = nullptr;
	}
}

void RBTree::left_rotate(RBNode* p)
{
	RBNode* din = dynamic(p->rlink);
	RBNode* p1 = din;
	p1->parent = p->parent;
	p->parent = p1;
	p->rlink = p1->llink;
	din = dynamic(p->rlink);
	din->parent = p;
	p1->llink = p;
	if (p1->parent == nullptr)
	{
		get_root() = m_root = p1;
	}
	else if (p1->parent->rlink == p)
	{
		p1->parent->rlink = p1;
	}
	else
	{
		p1->parent->llink = p1;
	}
}

void RBTree::right_rotate(RBNode* p)
{
	RBNode* din = dynamic(p->llink);
	RBNode* p1 = din;
	p1->parent = p->parent;
	p->parent = p1;
	p->llink = p1->rlink;
	din = dynamic(p->llink);
	din->parent = p;
	p1->rlink = p;
	if (p1->parent == nullptr)
	{
		get_root() = m_root = p1;
	}
	else if (p1->parent->llink == p)
	{
		p1->parent->llink = p1;
	}
	else
	{
		p1->parent->rlink = p1;
	}
}

void RBTree::nill(RBNode* p)
{
	p->llink = new RBNode();
	p->rlink = new RBNode();
	RBNode* ptr = dynamic(p->llink);
	ptr->parent = p;
	ptr = dynamic(p->rlink);
	ptr->parent = p;
}

RBNode* RBTree::uncle(RBNode* p) const
{
	return brother(p->parent);
}

RBNode* RBTree::brother(RBNode* p) const
{
	if (p->parent->llink == p)
	{
		return dynamic(p->parent->rlink);
	}
	return dynamic(p->parent->llink);
}

void RBTree::black_uncle(RBNode* ptr, RBNode* father, RBNode* grand, RBNode* uncle)
{
	if (grand->llink == father)
	{
		if (father->rlink == ptr)
		{
			left_rotate(father);
			RBNode* temp = ptr;
			ptr = father;
			father = temp;
		}
		right_rotate(grand);
	}
	else
	{
		if (father->llink == ptr)
		{
			right_rotate(father);
			RBNode* temp = ptr;
			ptr = father;
			father = temp;
		}
		left_rotate(grand);
	}
	father->color = true;
	grand->color = false;
}

void RBTree::uncle_part_insert(RBNode* ptr, const int& val)
{
	ptr->color = false;
	while (ptr != m_root && !(ptr->parent->color))
	{
		RBNode* father = ptr->parent;
		RBNode* grand = father->parent;
		RBNode* uncl = uncle(ptr);
		if (uncl->color == false)
		{
			father->color = true;
			grand->color = false;
			uncl->color = true;
			ptr = grand;
			continue;
		}
		black_uncle(ptr, father, grand, uncl);
		break;
	}
	m_root->color = true;
}

void RBTree::remove_part1(RBNode* ptr)
{
	if (ptr->parent == nullptr)
	{
		if (is_nill(ptr))
		{
			get_root() = m_root = nullptr;
			delete ptr;
		}
	}
	else
	{
		remove_part2(ptr);
	}
}

void RBTree::remove_part2(RBNode* ptr)
{
	RBNode* bro = brother(ptr);
	RBNode* father = ptr->parent;
	if (!bro->color)
	{
		if (father->llink == bro)
		{
			right_rotate(father);
		}
		else
		{
			left_rotate(father);
		}
		bro->color = true;
		father->color = false;
		remove_part4(ptr);
	}
	else
	{
		remove_part3(ptr);
	}
}

void RBTree::remove_part3(RBNode* ptr)
{
	RBNode* bro = brother(ptr);
	RBNode* father = ptr->parent;
	RBNode* din1 = dynamic(bro->llink), *din2 = dynamic(bro->rlink);
	if (din1->color && din2->color)
	{
		if (father->color)
		{
			bro->color = false;
			remove_part1(father);
		}
		else
		{
			remove_part4(ptr);
		}
	}
	else
	{
		remove_part5(ptr);
	}
}

void RBTree::remove_part4(RBNode* ptr)
{
	RBNode* bro = brother(ptr);
	RBNode* father = ptr->parent;
	bro->color = false;
	father->color = true;
}

void RBTree::remove_part5(RBNode* ptr)
{
	RBNode* bro = brother(ptr);
	RBNode* father = ptr->parent;
	RBNode* din = nullptr;
	if (father->llink == ptr)
	{
		din = dynamic(bro->rlink);
		if (din->color)
		{
			din = dynamic(bro->llink);
			RBNode* left = din;
			right_rotate(father);
			bro->color = false;
			left->color = true;
		}
	}
	else
	{
		din = dynamic(bro->llink);
		if (din->color)
		{
			din = dynamic(bro->rlink);
			RBNode* right = din;
			left_rotate(father);
			bro->color = false;
			right->color = true;
		}
	}
	remove_part6(ptr);
}

void RBTree::remove_part6(RBNode* ptr)
{
	RBNode* bro = brother(ptr);
	RBNode* father = ptr->parent;
	if (father->llink == ptr)
	{
		RBNode* right = dynamic(bro->rlink);
		left_rotate(father);
		bool temp = father->color;
		right->color = true;
		father->color = bro->color;
		bro->color = temp;
	}
	else
	{
		RBNode* left = dynamic(bro->llink);
		right_rotate(father);
		bool temp = father->color;
		left->color = true;
		father->color = bro->color;
		bro->color = temp;
	}
}

void RBTree::replace_child(RBNode* ptr)
{
	Node* child = is_nill(ptr->llink) ? ptr->rlink : ptr->llink;
	Node* brother = is_nill(ptr->llink) ? ptr->llink : ptr->rlink;
	delete brother;
	ptr->value = child->value;
	ptr->llink = child->llink;
	ptr->rlink = child->rlink;
	RBNode* din = dynamic(child);
	if (!din->color || !ptr->color)
	{
		din->color = true;
		ptr->color = false;
	}
	delete child;
}