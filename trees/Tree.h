#ifndef TREE_H
#define TREE_H

namespace BinaryTree
{
	struct Node
	{
		int value;
		Node* llink;
		Node* rlink;
		Node(int v = 0)
			: value(v)
			, llink(nullptr)
			, rlink(nullptr)
		{}
	};

	int count_leaf(Node* root);
	int count_node(Node* root);
	bool strict(Node* root);
	int height(Node* root);
	int max_value(Node* root);
	void bfs(Node* root);
	void preorder_traversal(Node* root);
	void inorder_traversal(Node* root);
	void postorder_traversal(Node* root);
	void preorder_traversal_stack(Node* root);
	void inorder_traversal_stack(Node* root);
	void postorder_traversal_stack(Node* root);
}

#endif // TREE_H