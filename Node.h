//
// Created by Hassan Attar on 2024-02-12.
//

#ifndef BST_NODE_H
#define BST_NODE_H


template<typename T>
class Node {
public:
    Node(const T &_data);
    Node(const T &_data, Node<T> *_left, Node<T> *_right);
    T data;
    Node<T> *left;
    Node<T> *right;
};

#include "Node.tpp"


#endif //BST_NODE_H
