#ifndef RB_TREE_H
#define RB_TREE_H

#include "binary_search_tree.h"

struct RBNode : Node {
    bool color;
    RBNode* parent;

    RBNode(int v = 0, bool col = true, RBNode* p = nullptr)
            : Node(v), color(col), parent(p) {}

    virtual ~RBNode() {}
};

class RBTree : public BinarySearchTree {
public:
    RBTree();

    RBTree(const RBTree&);

    RBTree& operator=(const RBTree&);

    virtual ~RBTree();

public:
    void insert(const int&);

    void remove(const int&);

public:
    int size() const { return _size; }

private:
    void allocate(const RBTree&);

    void alloc_help(RBNode* root1, RBNode* root2);

private:
    void left_rotate(RBNode*);

    void right_rotate(RBNode*);

    void nill(RBNode*);

    RBNode* uncle(RBNode*) const;

    RBNode* brother(RBNode*) const;

private:
    void black_uncle(RBNode*, RBNode*, RBNode*, RBNode*);

    void uncle_part_insert(RBNode*, const int&);

private:
    void remove_part1(RBNode*);

    void remove_part2(RBNode*);

    void remove_part3(RBNode*);

    void remove_part4(RBNode*);

    void remove_part5(RBNode*);

    void remove_part6(RBNode*);

    void replace_child(RBNode*);

private:
    RBNode* dynamic(Node* ptr) const { return dynamic_cast<RBNode*>(ptr); }

private:
    RBNode* _root;
    int _size;
};

#endif // RB_TREE_H