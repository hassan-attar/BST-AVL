//
// Created by Hassan Attar on 2024-03-06.
//

#ifndef BST_NODERB_H
#define BST_NODERB_H
#include "Node.h"
#include <iostream>

template<typename T>
class NodeRB : public Node<T> {
public:
    bool isRed;
    NodeRB(const T &_data);
    NodeRB(const T &_data, NodeRB<T> *_left, NodeRB<T> *_right);

    std::string toString() const override;
};


template<typename T>
NodeRB<T>::NodeRB(const T &_data): Node<T>(_data), isRed{true} {}

template<typename T>
NodeRB<T>::NodeRB(const T &_data, NodeRB<T> *_left, NodeRB<T> *_right): Node<T>(_data, _left, _right), isRed{true} {}

template<typename T>
std::string NodeRB<T>::toString() const {
    return std::to_string(this->data).append("-").append(isRed ? "R" : "B");
}
#endif //BST_NODERB_H
