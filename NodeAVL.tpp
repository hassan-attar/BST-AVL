//
// Created by Hassan Attar on 2024-03-06.
//

#include "NodeAVL.h"

template<typename T>
NodeAVL<T>::NodeAVL(const T &_data) : Node<T>(_data), height{0} {}

template<typename T>
NodeAVL<T>::NodeAVL(const T &_data, NodeAVL<T> *_left, NodeAVL<T> *_right): Node<T>(_data, _left, _right), height{0} {}


template<typename T>
std::string NodeAVL<T>::toString() const {
    int bf = 0;
    if(this->left && this->right){
        bf = (static_cast<const NodeAVL<T> *>(this->right)->height + 1) - (static_cast<const NodeAVL<T> *>(this->left)->height + 1);
    }else if(this->left){
        bf = -1 * (static_cast<const NodeAVL<T> *>(this->left)->height + 1);
    }else if(this->right){
        bf = (static_cast<const NodeAVL<T> *>(this->right)->height + 1);
    }
    return std::string(std::to_string(this->data)).append("(").append(std::to_string(bf)).append(")");
}