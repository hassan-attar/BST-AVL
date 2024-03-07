//
// Created by Hassan Attar on 2024-03-06.
//

#ifndef BST_NODEAVL_H
#define BST_NODEAVL_H

#include <iostream>
#include "Node.h"

template<typename T>
class NodeAVL : public Node<T> {
public:
    int height;

    NodeAVL(const T &_data);
    NodeAVL(const T &_data, NodeAVL<T> *_left, NodeAVL<T> *_right);

    virtual std::string toString() const;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const NodeAVL<T> &node){
    os << (std::to_string(node.data) + "-" + node.height);
    return os;
}

#include "NodeAVL.tpp"


#endif //BST_NODEAVL_H
