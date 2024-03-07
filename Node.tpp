//
// Created by Hassan Attar on 2024-02-12.
//

#include "Node.h"

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