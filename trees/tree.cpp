#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

#include "tree.hpp"

int BinaryTree::count_leaf(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->llink == nullptr && root->rlink == nullptr) {
        return 1;
    }
    return count_leaf(root->llink) + count_leaf(root->rlink);
}

int BinaryTree::count_node(Node* root) {
    if (root == nullptr)
        return 0;
    return 1 + count_node(root->llink) + count_node(root->rlink);
}

bool BinaryTree::strict(Node* root) {
    if (root == nullptr)
        return true;
    bool flag = true;
    if (root->llink != nullptr)
        flag = !flag;
    if (root->rlink != nullptr)
        flag = !flag;
    return flag && strict(root->llink) && strict(root->rlink);
}

int BinaryTree::height(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + std::max(height(root->llink), height(root->rlink));
}

int BinaryTree::max_value(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return std::max(root->value, std::max(max_value(root->llink), max_value(root->rlink)));
}

void BinaryTree::bfs(Node* root) {
    if (root == nullptr)
        return;
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* ptr = q.front();
        std::cout << ptr->value << std::endl;
        if (ptr->llink != nullptr)
            q.push(ptr->llink);
        if (ptr->rlink != nullptr)
            q.push(ptr->rlink);
        q.pop();
    }
}

void BinaryTree::preorder_traversal(Node* root) {
    if (root == nullptr)
        return;
    preorder_traversal(root->llink);
    std::cout << root->value << std::endl;
    preorder_traversal(root->rlink);
}

void BinaryTree::inorder_traversal(Node* root) {
    if (root == nullptr)
        return;
    std::cout << root->value << std::endl;
    inorder_traversal(root->llink);
    inorder_traversal(root->rlink);
}

void BinaryTree::postorder_traversal(Node* root) {
    if (root == nullptr)
        return;
    postorder_traversal(root->llink);
    postorder_traversal(root->rlink);
    std::cout << root->value << std::endl;
}

void BinaryTree::preorder_traversal_stack(Node* root) {
    if (root == nullptr) {
        return;
    }
    std::stack<Node*> st;
    st.push(nullptr);
    while (root != nullptr) {
        st.push(root);
        root = root->llink;
    }
    Node* ptr = st.top();
    while (ptr != nullptr) {
        std::cout << ptr->value << std::endl;
        if (ptr->rlink != nullptr) {
            ptr = ptr->rlink;
            while (ptr != nullptr) {
                st.push(ptr);
                ptr = ptr->llink;
            }
        } else {
            Node* topptr = ptr;
            do {
                ptr = topptr;
                st.pop();
                topptr = st.top();
            } while (topptr != nullptr && topptr->rlink == ptr);
        }
        ptr = st.top();
    }
}

void BinaryTree::inorder_traversal_stack(Node* root) {
    if (root == nullptr) {
        return;
    }
    std::stack<Node*> st;
    st.push(nullptr);
    st.push(root);
    Node* ptr = st.top();
    while (ptr != nullptr) {
        std::cout << ptr->value << std::endl;
        if (ptr->llink != nullptr) {
            st.push(ptr->llink);
        } else if (ptr->rlink != nullptr) {
            st.push(ptr->rlink);
        } else {
            Node* topptr = ptr;
            do {

                ptr = topptr;
                st.pop();
                topptr = st.top();
            } while (topptr != nullptr && ((topptr->rlink == ptr) || (topptr->rlink == nullptr)));
            if (topptr != nullptr) {
                st.push(topptr->rlink);
            }
        }
        ptr = st.top();
    }
}

void BinaryTree::postorder_traversal_stack(Node* root) {
    if (root == nullptr) {
        return;
    }
    std::stack<Node*> st;
    st.push(nullptr);
    while (root != nullptr) {
        st.push(root);
        root = root->llink;
    }
    Node* ptr = st.top();
    while (ptr != nullptr) {
        std::cout << ptr->value << std::endl;
        Node* topptr = ptr;
        do {
            std::cout << topptr->value << std::endl;
            ptr = topptr;
            st.pop();
            topptr = st.top();
        } while (topptr != nullptr && ((topptr->rlink == ptr) || (topptr->rlink == nullptr)));
        if (topptr != nullptr) {
            topptr = topptr->rlink;
            while (topptr != nullptr) {
                st.push(topptr);
                topptr = topptr->llink;
            }
        }
        ptr = st.top();
    }
}