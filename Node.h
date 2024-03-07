//
// Created by Hassan Attar on 2024-02-12.
//

#ifndef BST_NODE_H
#define BST_NODE_H
#include <iostream>

template<typename T>
class Node {
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

template<typename T>
Node<T>::Node(const T &_data, Node<T> *_left, Node<T> *_right)
        : data{_data}, left{_left}, right{_right} {}

template<typename T>
Node<T>::Node(const T &_data)
        : Node(_data, nullptr, nullptr){}

template<typename T>
std::string Node<T>::toString() const {
    return std::to_string(data);
}


#endif //BST_NODE_H
