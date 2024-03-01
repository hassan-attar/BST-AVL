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
