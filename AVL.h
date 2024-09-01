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
    // ########## Helpers ##########
    int getNodeHeight(const Node<T> *node);         // Getting node height utilizing height field in NodeAVL class
    void balanceFixup(std::stack<NodeAVL<T>*> &s);
protected:
    // Rotations
    NodeAVL<T> *rotateLeft(NodeAVL<T> *x);
    NodeAVL<T> *rotateRight(NodeAVL<T> *x);
    // Imbalances
    NodeAVL<T> *leftRightImbalance(NodeAVL<T> *x);
    NodeAVL<T> *rightLeftImbalance(NodeAVL<T> *x);
    NodeAVL<T> *leftLeftImbalance(NodeAVL<T> *x);
    NodeAVL<T> *rightRightImbalance(NodeAVL<T> *x);
public:
    // ########## Interface (Override) ##########
    bool insert(const T &data) override;
    bool remove(const T &data) override;
};


// ########## Helpers ##########
template<typename T>
int AVL<T>::getNodeHeight(const Node<T> *node) {
    if(!node) return -1;
    return static_cast<const NodeAVL<T> *>(node)->height;
}
// Rotations
template<typename T>
NodeAVL<T> *AVL<T>::rotateLeft(NodeAVL<T> *x) {
    std::cout << "**Performing Left Rotation on node " << x->data << "**\n";
    NodeAVL<T> *y = static_cast<NodeAVL<T> *>(x->right);
    x->right = y->left;
    y->left = x;

    x->height = std::max(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;
    y->height = std::max(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;
    return y;
}
template<typename T>
NodeAVL<T> *AVL<T>::rotateRight(NodeAVL<T> *x) {
    std::cout << "**Performing Right Rotation on node " << x->data << "**\n";
    NodeAVL<T> *y = static_cast<NodeAVL<T> *>(x->left);
    x->left = y->right;
    y->right = x;

    x->height = std::max(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;
    y->height = std::max(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;

    return y;
}
// Imbalances
template<typename T>
NodeAVL<T> *AVL<T>::leftLeftImbalance(NodeAVL<T> *x) {
    std::cout << "@@LL Imbalance Detected@@\n";
    return rotateRight(x);
}
template<typename T>
NodeAVL<T> *AVL<T>::rightRightImbalance(NodeAVL<T> *x) {
    std::cout << "@@RR Imbalance Detected@@\n";
    return rotateLeft(x);
}
template<typename T>
NodeAVL<T> *AVL<T>::leftRightImbalance(NodeAVL<T> *x) {
    std::cout << "@@LR Imbalance Detected@@\n";
    x->left = rotateLeft(static_cast<NodeAVL<T> *>(x->left));
    return rotateRight(x);
}
template<typename T>
NodeAVL<T> *AVL<T>::rightLeftImbalance(NodeAVL<T> *x) {
    std::cout << "@@RL Imbalance Detected@@\n";
    x->right = rotateRight(static_cast<NodeAVL<T> *>(x->right));
    return rotateLeft(x);
}

template<typename T>
void AVL<T>::balanceFixup(std::stack<NodeAVL<T> *> &s) {
    int leftHeight, rightHeight, balanceFactor;
    NodeAVL<T> *child, *temp, *cur;
    while(true){
        cur = s.top();
        s.pop();
        temp = cur;
        leftHeight  = getNodeHeight(cur->left);
        rightHeight = getNodeHeight(cur->right);
        cur->height = std::max(leftHeight, rightHeight) + 1; //Update the height
        balanceFactor = (rightHeight + 1) - (leftHeight + 1);
        if(balanceFactor <= -2){ // LEFT Imbalance
            child = static_cast<NodeAVL<T> *>(cur->left);
            leftHeight  = getNodeHeight(child->left);
            rightHeight = getNodeHeight(child->right);
            balanceFactor = (rightHeight + 1) - (leftHeight + 1);
            if(balanceFactor <= -1){ // LEFT-LEFT Imbalance
                temp = leftLeftImbalance(cur);
            }else{ // LEFT-RIGHT Imbalance
                temp = leftRightImbalance(cur);
            }
        }else if(balanceFactor >= 2){ // RIGHT Imbalance
            child = static_cast<NodeAVL<T> *>(cur->right);
            leftHeight  = getNodeHeight(child->left);
            rightHeight = getNodeHeight(child->right);
            balanceFactor = (rightHeight + 1) - (leftHeight + 1);
            if(balanceFactor >= 1){ // RIGHT-RIGHT Imbalance
                temp = rightRightImbalance(cur);
            }else{ // RIGHT-LEFT Imbalance
                temp = rightLeftImbalance(cur);
            }
        }
        // Update the parent link in case of rotation, otherwise just returning current
        if(!s.empty()){
            if(s.top()->left == cur){
                s.top()->left = temp;
            }else{
                s.top()->right = temp;
            }
        }else{
            break;
        }
    }
    this->root = temp;
}

// ########## Interface (Override) ##########
template<typename T>
bool AVL<T>::insert(const T &data) {
    if(!this->root){ // Empty tree case
        BST<T>::root = new NodeAVL<T>(data);
        BST<T>::size++;
        return true;
    }
    std::stack<NodeAVL<T> *> s;
    NodeAVL<T> *cur = static_cast<NodeAVL<T> *>(BST<T>::root);
    while(cur && cur->data != data){
        s.push(cur);
        if(data > cur->data){
            cur = static_cast<NodeAVL<T> *>(cur->right);
        }else{
            cur = static_cast<NodeAVL<T> *>(cur->left);
        }
    }
    if(cur) return false; // duplicate detected

    //Adding the node
    if(data > s.top()->data){
        s.top()->right = new NodeAVL<T>(data);
    }else{
        s.top()->left = new NodeAVL<T>(data);
    }

    balanceFixup(s);
    return true;
}

template<typename T>
bool AVL<T>::remove(const T &data) {
    if(!this->root){ // Empty tree case
        return false;
    }
    std::stack<NodeAVL<T> *> s;
    NodeAVL<T> *cur = static_cast<NodeAVL<T> *>(this->root);
    while(cur && cur->data != data){
        s.push(cur);
        if(data > cur->data){
            cur = static_cast<NodeAVL<T> *>(cur->right);
        }else{
            cur = static_cast<NodeAVL<T> *>(cur->left);
        }
    }
    if(!cur) return false;
    if(!cur->left && !cur->right){ // CASE 1: Leaf Node
        if(data > s.top()->data){ // Update parent link to null.
            s.top()->right = nullptr;
        }else {
            s.top()->left  = nullptr;
        }
        delete cur;
        if(this->size == 1){ // root will be deleted only through CASE 1
            this->root = nullptr;
        }
        this->size--;
        balanceFixup(s);
        return true;
    }else if(cur->left && cur->right){ // CASE 2: Both children exist
        s.push(cur);
        NodeAVL<T> *pred = static_cast<NodeAVL<T> *>(cur->left);
        while(pred && pred->right){
            s.push(pred);
            pred = static_cast<NodeAVL<T> *>(pred->right);
        }
        T temp = std::move(cur->data);
        cur->data = std::move(pred->data);
        pred->data = std::move(temp); // pred is now the node to be deleted
        if(s.top()->right == pred){ // connect parent to the only child of the predecessor (left)
            s.top()->right = pred->left;
        }else{
            s.top()->left = pred->left;
        }
        delete pred;
        balanceFixup(s);
        this->size--;
        return true;
    }else{ // CASE 3: Only one child exist
        // connect parent to the only child of cur
        if(s.top()->right == cur){
            s.top()->right = cur->left ? cur->left : cur->right;
        }else {
            s.top()->left = cur->left ? cur->left : cur->right;
        }
        delete cur;
        this->size--;
        balanceFixup(s);
        return true;
    }
}




#endif //BST_AVL_H
