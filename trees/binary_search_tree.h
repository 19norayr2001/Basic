#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

struct Node {
    int value;
    Node *llink;
    Node *rlink;

    Node(int v = 0)
            : value(v), llink(nullptr), rlink(nullptr) {}

    virtual ~Node() {}
};

class BinarySearchTree {
public:

    BinarySearchTree();

    BinarySearchTree(const BinarySearchTree &);

    BinarySearchTree &operator=(const BinarySearchTree &);

    virtual ~BinarySearchTree();

public:
    bool empty() const { return m_root == nullptr; }

    virtual void insert(const int &);

    virtual void remove(const int &);

    bool find(const int &) const;

private:
    void allocate(const BinarySearchTree &);

    void alloc_help(Node *, Node *);

private:
    void nill(Node *) const;

protected:
    void deallocate(Node *);

protected:
    bool is_nill(Node *ptr) const { return ptr->llink == nullptr && ptr->rlink == nullptr; }

    Node *&get_root() { return m_root; }

protected:
    Node *insert_node(const int &);

    Node *remove_node(const int &);

    Node *find_node(const int &) const;

    Node *next(Node *) const;

private:
    void replace_child(Node *);

private:
    Node *m_root;
};

#endif // BINARY_SEARCH_TREE_H