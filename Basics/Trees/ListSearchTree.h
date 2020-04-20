#pragma once

class ListSearchTree
{
public:
	struct Node
	{
		Node* llink;
		Node* rlink;
		Node()
			:llink(nullptr)
			, rlink(nullptr)
		{}
		virtual ~Node() {}
	};

	struct InternalNode : Node
	{
		int left_count_leaves;
		InternalNode(int v = 0)
			: left_count_leaves(v)
		{}
	};

	struct ExternalNode : Node
	{
		int value;
		ExternalNode(int v = 0)
			:value(v)
		{}
	};

	ListSearchTree();
	ListSearchTree(const ListSearchTree&);
	ListSearchTree& operator=(const ListSearchTree&);
	~ListSearchTree();
public:
	bool empty() const { return m_root == nullptr; }
	int size() const { return m_size; }
	int find(int k) const;
	void insert(const int&, int k);
	void remove(int k);
private:
	bool is_leaf(Node* node) const { return node->llink == nullptr && node->rlink == nullptr; }
	void allocate(const ListSearchTree&);
	void deallocate(const Node* const root) const;
	void alloc_help(Node* const root1, Node* const root2) const;
private:
	Node* m_root;
	int m_size;
};

