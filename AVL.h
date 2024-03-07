//
// Created by Hassan Attar on 2024-03-06.
//

#ifndef BST_AVL_H
#define BST_AVL_H

#include "NodeAVL.h"
#include "BST.h"

template<typename T>
class AVL : public BST<T>{
private:
    int getNodeHeight(const Node<T> *node);
protected:
    NodeAVL<T> *rotateLeft(NodeAVL<T> *x);
    NodeAVL<T> *rotateRight(NodeAVL<T> *x);
    NodeAVL<T> *leftRightImbalance(NodeAVL<T> *x);
    NodeAVL<T> *rightLeftImbalance(NodeAVL<T> *x);
    NodeAVL<T> *leftLeftImbalance(NodeAVL<T> *x);
    NodeAVL<T> *rightRightImbalance(NodeAVL<T> *x);
public:
    virtual bool insert(const T &data) override;
    virtual bool remove(const T &data) override;
};


#include "AVL.tpp"

#endif //BST_AVL_H
