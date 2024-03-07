//
// Created by Hassan Attar on 2024-02-12.
//

#ifndef BST_NODE_H
#define BST_NODE_H
#include <iostream>

template<typename T>
class Node {
//    friend std::ostream &operator<<(std::ostream &os, const Node<T> &node);
public:
    Node(const T &_data);
    Node(const T &_data, Node<T> *_left, Node<T> *_right);
    T data;
    Node<T> *left;
    Node<T> *right;

    virtual std::string toString() const;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const Node<T> &node){
    os << node.toString();
    return os;
}

#include "Node.tpp"


#endif //BST_NODE_H
