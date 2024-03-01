//
// Created by Hassan Attar on 2024-02-12.
//

#include "BST.h"
#include "cmath"
#include "vector"
#include "queue"
#include "stack"
#include "iomanip"
#include "ctime"

// to improve readability in the code
template <typename T>
using ParentNode = Node<T>;

template <typename T>
using CurrentNode = Node<T>;


template<typename T>
BST<T>::BST()
:root{nullptr}, size{0}{}

template<typename T>
BST<T>::BST(std::initializer_list<T> &list): BST() {
    int *indexes = new int[list.size()];
    for(int i = 0 ; i < list.size(); i++){
        indexes[i] = i;
    }
    shuffleRandomized(indexes, list.size());
    for(int i = 0 ; i < list.size(); i++){
        insert(list[indexes[i]]);
    }
}

template<typename T>
BST<T>::BST(const T *arr, int size): BST() {
    int *indexes = new int[size];
    for(int i = 0 ; i < size; i++){
        indexes[i] = i;
    }
    shuffleRandomized(indexes, size);
    for(int i = 0 ; i < size; i++){
        insert(arr[indexes[i]]);
    }
}


template<typename T>
void BST<T>::shuffleRandomized(int *arr, int size){
    int temp;
    std::srand(time(nullptr));
    for(int i = 0, j; i < size; i++){
        temp = arr[i];
        j = std::rand() % (size - i) + i;
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// PUBLIC INTERFACE
template<typename T>
bool BST<T>::insert(const T &data) {
    if(!root){
        root = new Node<T>(data);
        size++;
    } else{
        std::pair<ParentNode *, CurrentNode *> p= findParent(data);
        if(p.second){ // the node exists in the tree.
            return false;
        }
        if(data > p.first->data){
            p.first->right = new Node<T>(data);
        } else {
            p.first->left = new Node<T>(data);
        }
        size++;
    }
    return true;
}

template<typename T>
bool BST<T>::remove(const T &data) {
    std::pair<ParentNode *, CurrentNode *> nodePair = findParent(data);
    auto &node = nodePair.second;
    auto &nodeParent = nodePair.first;

    if(!node){ // node not in the tree.
        return false;
    }

    std::pair<ParentNode *, CurrentNode *> predPair = findBottomDownInOrderPredecessor(node);
    auto &predecessor = predPair.second;

    //while predecessorNode exists
    while(predecessor){
        swap(nodePair, predPair); // swap the node with its predecessor
        //                                        node
        predPair = findBottomDownInOrderPredecessor(node); // find the predecessor of the swapped node.
    }
    // by here, we know for sure that node->left is null
    if(nodeParent) { // if we are not deleting the very last node
        if(nodeParent->left == node){
            nodeParent->left = node->right;
        }else {
            nodeParent->right = node->right;
        }
    }else { // the node being deleted is the root, and root->left is null
        root = node->right;
    }
    delete node;
    size--;
    return true;
}

template<typename T>
void BST<T>::swap(std::pair<ParentNode *, CurrentNode *> &p1, std::pair<ParentNode *, CurrentNode *> &p2) {
    // !(node1 == node2Parent  ||     node2 == node1Parent ) => At least one of them needs to be true to have a Parent-child
    if(!(p1.second == p2.first || p2.second == p1.first)){
        // Parent-Child swap
        swapIndependentNodes(p1, p2);
    } else {
        // Independent Nodes swap
        swapParentChildNodes(p1,p2);
    }
}

template<typename T>
void
BST<T>::swapIndependentNodes(std::pair<ParentNode *, CurrentNode *> &p1, std::pair<ParentNode *, CurrentNode *> &p2) {
    auto& node1 = p1.second;
    auto& node2 = p2.second;
    Node<T> *temp;
    // #### Swap the children ####
    // Swapping left child
    temp = node1->left;
    node1->left = node2->left;
    node2->left = temp;
    // Swapping right child
    temp = node1->right;
    node1->right = node2->right;
    node2->right = temp;

    // #### Swap the parents' links ####
    // (node1Parent && node2Parent) => none of them is the root node
    if(   p1.first && p2.first   ){
        auto& node1Parent = p1.first;
        auto& node2Parent = p2.first;

        if(node1Parent == node2Parent){ // Same Parents, nodes are left/right child of the same parent
            if(node1Parent->left == node1){ // which side of the node1Parent is node1? put node2 on that side, and node1 on the other
                node1Parent->left = node2;
                node1Parent->right = node1;
            } else{
                node1Parent->right = node2;
                node1Parent->left = node1;
            }
        } else { // Independent Parents
            // For node1Parent
            if(node1Parent->left == node1){ // which side of the node1Parent is node1? put node2 on that side
                node1Parent->left = node2;
            } else{
                node1Parent->right = node2;
            }
            // For node2Parent : same logic
            if(node2Parent->right == node2){ // which side of the node2Parent is node2? put node1 on that side
                node2Parent->right = node1;
            } else{
                node2Parent->left = node1;
            }
        }
    } else { // One of them is the root, since it's parent is null
        auto &theNotRootNode = root == node1 ? node2 : node1; // this node will become the new root.
        // and we have the root as one variable
        //                                                  node1Parent : node2Parent
        auto &theNotRootNodeParent = theNotRootNode == node1 ? p1.first : p2.first;

        // swap the parent link of theNotRootNodeParent
        if(theNotRootNodeParent->left == theNotRootNode){
            theNotRootNodeParent->left = root;
        } else{
            theNotRootNodeParent->right = root;
        }
        root = theNotRootNode;

    }
    // to keep the pairs, p1 & p2, valid based on the modification, swap the parents
    temp = p1.first;
    p1.first = p2.first;
    p2.first = temp;
}

template<typename T>
void
BST<T>::swapParentChildNodes(std::pair<ParentNode *, CurrentNode *> &p1, std::pair<ParentNode *, CurrentNode *> &p2) {
    // !(node1 == node2Parent  ||     node2 == node1Parent ) => At least one of them needs to be true to have a Parent-child
    if(!(p1.second == p2.first || p2.second == p1.first)){ 
        return; // SafeGuard: there is not Parent-Child relationship, retuning...
    }
    // Making meaningful aliases
    // Q1: Who is the parent of the other?
    //             (node1 == node2Parent ) ?     node1 : node2    ; => we can make these conclusions because of the SafeGuard.
    auto &parent = (p1.second == p2.first) ? p1.second : p2.second;
    // Q2: Who is the child?
    //            (parent == node1)     ?     node2 : node1    ;
    auto &child = (parent == p1.second) ? p2.second : p1.second;

    Node<T> *temp;
    // #### Swap the children ####
    if(parent->right == child){ // the child is on the right side of the parent
        // child right, will be the parent. in other words: parent is becoming the child of its child
        parent->right = child->right;
        child->right = parent;
        // swap left child
        temp = child->left;
        child->left = parent->left;
        parent->left = temp;
    } else { // the child is on the left side of the parent
        // child left, will be the parent
        parent->left = child->left;
        child->left = parent;
        // swap right child
        temp = child->right;
        child->right = parent->right;
        parent->right = temp;
    }


    // #### Swap the parents' links ####
    // (node1Parent && node2Parent) => none of them is the root node
    if(p1.first && p2.first){ // same as the above condition
        // Q3: Who is the parent of the parent?
        //                     (parent == node1)     ?  node1Parent : node2Parent
        auto &parentOfParent = (parent == p1.second) ?     p1.first : p2.first;
        // swap parentOfParent link
        if(parentOfParent->right == parent){
            parentOfParent->right = child;
        } else {
            parentOfParent->left = child;
        }
        // child's parent is now parentOfParent
        // to keep pairs valid after modification: You can ignore this part
        if(parent == p1.second){
            temp = parentOfParent;
            p1.first = child;
            // p2.first = (temp == parentOfParent) ? parentOfParent : temp;
            p2.first = temp;
        } else {
            temp = parentOfParent;
            p2.first = child;
            p1.first = temp;
            // p1.first = (temp == parentOfParent)? parentOfParent : temp;
        }
    } else {
        // if parent was the root, there is no parent of the parent, therefore, no linking is needed
        // updating the root to the new node
        root = child;
        // to keep pairs valid after modification: You can ignore this part
        // parent's parent is the child
        ( p1.second == p2.first) ? p1.first = child : p2.first = child;
        // child's parent is null
        (parent == p1.second) ? p2.first = nullptr : p1.first = nullptr;

    }
}

template<typename T>
const Node<T> *BST<T>::getSuccessor(const Node<T> *node) const{
    if(!node) return nullptr;
    if(node->right){
        return getMin(node->right);
    }
    std::stack<Node<T> *> s;
    s.push(nullptr);
    Node<T> *temp = root;
    while(temp && temp != node){
        s.push(temp);
        if(node->data > temp->data){
            temp = temp->right;
        }else{
            temp = temp->left;
        }
    }
    while(s.top() != nullptr && temp == s.top()->right){
        temp = s.top();
        s.pop();
    }
    return s.top();
}

template<typename T>
const Node<T> *BST<T>::getPredecessor(const Node<T> *node) const {
    if(!node) return nullptr;
    if(node->left){
        return getMax(node->left);
    }
    std::stack<Node<T> *> s;
    s.push(nullptr);
    Node<T> *temp = root;
    while(temp && temp != node){
        s.push(temp);
        if(node->data > temp->data){
            temp = temp->right;
        }else{
            temp = temp->left;
        }
    }
    while(s.top() != nullptr && temp == s.top()->left){
        temp = s.top();
        s.pop();
    }
    return s.top();
}



template<typename T>
const Node<T> *BST<T>::search(const T& data) const {
    Node<T> *cur = root;
    while(cur){
        if(data > cur->data){
            cur = cur->right;
        } else if(data < cur->data){
            cur = cur->left;
        } else { // cur->data == data
            break;
        }
    }
    return cur;
}

template<typename T>
size_t BST<T>::getHeight() const{
    return getHeight(root);
}

template<typename T>
size_t BST<T>::getHeightRecursive() const{
    return getHeightRecursive(root);
}

template<typename T>
size_t BST<T>::getHeightRecursive(const Node<T> *node) const {
    if(!node || (!node->left && !node->right)){
        return 0;
    } else {
        return std::max(getHeightRecursive(node->left), getHeightRecursive(node->right)) + 1;
    }
}

template<typename T>
size_t BST<T>::getHeight(const Node<T> *node) const {
    if(!node || (!node->left && !node->right)) return 0;
    std::queue<const Node<T> *> q;
    const Node<T> *temp;
    q.push(node);
    size_t maxLevel = 0;
    size_t nodesAtLevel;
    while(!q.empty()){
        nodesAtLevel = q.size();
        maxLevel++;
        while(nodesAtLevel > 0){
            temp = q.front();
            q.pop();
            if(temp->right) q.push(temp->right);
            if(temp->left) q.push(temp->left);
            nodesAtLevel--;
        }
    }
    return maxLevel - 1;
}

template<typename T>
inline constexpr size_t BST<T>::getSize() const {
    return size;
}

template<typename T>
const Node<T> *BST<T>::getMax(const Node<T> *node) const {
    if(!node) return nullptr;
    while(node->right){
        node = node->right;
    }
    return node;
}

template<typename T>
const Node<T> *BST<T>::getMin(const Node<T> *node) const {
    if(!node) return nullptr;
    while(node->left){
        node = node->left;
    }
    return node;
}

template<typename T>
const Node<T> *BST<T>::getMax() const {
    return getMax(root);
}

template<typename T>
const Node<T> *BST<T>::getMin() const {
    return getMin(root);
}


template<typename T>
std::vector<const Node<T> *> *BST<T>::convertToVector(const Node<T> *node) const {
    size_t totalSpots = getMaxNodeCount(getHeight(node));
    std::vector<const Node<T> *> *vec = new std::vector<const Node<T>*>;
    vec->reserve(totalSpots);
    std::queue<const Node<T>*> q;
    q.push(node);
    const Node<T> *cur;
    while(totalSpots > 0){
        cur = q.front();
        q.push(cur ? cur->left : nullptr);
        q.push(cur ? cur->right : nullptr);
        vec->push_back(cur);
        totalSpots--;
        q.pop();
    }
    return vec;
}

template<typename T>
std::vector<const Node<T> *> *BST<T>::getPath(const T &data) const {
    std::vector<const Node<T> *> v;
    Node<T> *temp = root;
    while(temp && temp->data != data){
        v.push_back(temp);
        if(data > temp->data){
            temp = temp->right;
        }else{
            temp = temp->left;
        }
    }
    if(!temp){
        delete v;
        return nullptr;
    }
    return v;
}

/**
 * Displays Binary tree graphically in the terminal
 * @param maxInputPrintWidth the maximum input width of the data being printed
 * @param horizontal_scale the scale in which the tree will expand horizontally in the terminal
 */
template<typename T>
void BST<T>::displayTree(size_t maxDataFieldPrintWidth, size_t horizontal_scale) const{
    static const int slashWidth = 1; // for better readability
    if(!root || (!root->left && !root ->right)){ // check the case of empty tree or a tree with just one node
        if(!root){
            std::cout << "Empty Tree" << std::endl;
        } else{
            std::cout << root->data << std::endl;
        }
        return;
    }
    // get a vector of nodes, including nullptr if a child doesn't exist, in level order.
    std::vector<const Node<T>*> *vec = convertToVector(root);
    // get the height of this tree
    size_t height = getHeight(root);
    size_t i, j;
    // left space is the offset from the left, when printing different levels of the tree
    // branchLength is the length between a parent node and its child
    size_t leftSpace = 0, branchLength = 0;

    if(maxDataFieldPrintWidth & 1) maxDataFieldPrintWidth++; // if print width was odd, round it to the next even number, to make it easier for alignment.
    // that is the heart of this method: building block is lengthOfData + whitespace until the next node on that level(is a multiple of lengthOfData).
    size_t buildingBlockSize = maxDataFieldPrintWidth + (horizontal_scale * maxDataFieldPrintWidth);
    leftSpace = (buildingBlockSize / 2) * static_cast<size_t>(std::pow(2, height) - 1); // Sum of geometric series
    buildingBlockSize *= static_cast<size_t>(std::pow(2, height));
    /*
    Has been factored out from the below:
    for(i = 0; i < height; i++){
        leftSpace += buildingBlockSize / 2;
        buildingBlockSize *= 2;
    }
    */

    size_t nodeAtLevel = 1;
    if(leftSpace > 0) std::cout << std::setw((int)leftSpace) << " "; // adding leftSpace indentation if necessary
    i = 0;
    while(i < vec->size()){ // still node left to print
        // ############## Printing Values ##############
        if((*vec)[i] == nullptr){ // No node at that position
            std::cout << std::left << std::setw((int) buildingBlockSize) << " "; // print the space
        } else { // Node present
            if(i & 1){ // left children are present at odd indexes
                std::cout << std::right << std::setw((int) maxDataFieldPrintWidth) << (*vec)[i]->data // printing data
                << std::setw((int)(buildingBlockSize - maxDataFieldPrintWidth)) << " "; // printing the space between left/right child
            }else{ // right children are present at even indexes
                // First node on the first level will be treated like a right child (index is 0)
                std::cout << std::left << std::setw((int) buildingBlockSize) << (*vec)[i]->data; // printing data
            }
        }
        i++;
        if(i == nodeAtLevel){ // Enters here if and only if all the nodes at the current level have been printed
            // updating variables
            nodeAtLevel = nodeAtLevel * 2 + 1; // the number of nodes at the next level is updated
            buildingBlockSize /= 2;
            leftSpace -= buildingBlockSize / 2;

            std::cout << std::endl;
            if(leftSpace > 0) std::cout << std::setw((int)leftSpace) << " "; // adding leftSpace indentation if necessary
            j = i;
            branchLength = (buildingBlockSize - (2 * maxDataFieldPrintWidth) - (2 * slashWidth)) / 2;
            // branchLength is the length of this shape (------),
            // ############## Printing Connections ##############
            while(j < nodeAtLevel && nodeAtLevel <= vec->size()){
                if((*vec)[j] == nullptr){ // no child present
                    // All about printing space
                    if(j & 1){ // empty left branch
                        std::cout << std::setw((int) ((branchLength + (maxDataFieldPrintWidth / 2)) + maxDataFieldPrintWidth + slashWidth)) << " ";
                    } else{ // empty right branch
                        std::cout << std::setw((int) (branchLength + maxDataFieldPrintWidth / 2) + slashWidth) << " ";
                    }
                } else { // child present
                    if(j & 1){ // child will be at left branch
                        std::cout << std::setw((int) maxDataFieldPrintWidth) << " ";
                        std::cout << std::left << "/";
                        std::cout << std::setfill('-') << std::setw((int) (branchLength + (maxDataFieldPrintWidth / 2))) << "-";
                    } else{ // child will be at right branch
                        std::cout << std::setfill('-') << std::setw((int) (branchLength + maxDataFieldPrintWidth / 2)) << "-";
                        std::cout << std::left << '\\';
                    }
                    std::cout << std::setfill(' ');
                }

                if(!(j & 1)){ // whenever we pass a right child, parent will change
                    std::cout << std::setw((int) buildingBlockSize) << " "; // space between right and left children of different parents (children on the same level)
                }
                j++;
            }
            std::cout << std::endl;
            if(leftSpace > 0) std::cout << std::setw((int)leftSpace) << " ";  // adding leftSpace indentation if necessary
        }
    }
    std::cout << std::endl;
    delete vec;
}


// STATIC PUBLIC INTERFACE
template<typename T>
inline constexpr size_t BST<T>::getMaxHeight(size_t nodeCount) {
    return nodeCount - 1;
}

template<typename T>
inline constexpr size_t BST<T>::getMinHeight(size_t nodeCount) {
    return static_cast<size_t>(std::ceil(std::log2(nodeCount + 1))) - 1;
}

template<typename T>
inline constexpr size_t BST<T>::getMaxNodeCount(size_t height) {
    return static_cast<size_t>(std::pow(2, height + 1)) - 1;
}

template<typename T>
inline constexpr size_t BST<T>::getMinNodeCount(size_t height) {
    return height + 1;
}


// HELPER METHODS
/**
 * returns a pointer to the parent node of the node could hold data.
 * @param data data of the node.
 * @return std::pair<parentNode, currentNode>
 */
template<typename T>
std::pair<ParentNode<T>*, CurrentNode<T>*> BST<T>::findParent(const T &data) const{
    Node<T> *parent = nullptr;
    Node<T> *cur = root;
    while(cur){
        if(data > cur->data){
            parent = cur;
            cur = cur->right;
        } else if(data < cur->data){
            parent = cur;
            cur = cur->left;
        } else { // cur->data == data
            break;
        }
    }
    return std::pair(parent, cur);
}

template<typename T>
std::pair<ParentNode<T>*, CurrentNode<T>*> BST<T>::findBottomDownInOrderPredecessor(Node<T>* node) const{
    Node<T> *parent = node;
    Node<T> *cur = node->left;
    while(cur && cur->right){
        parent = cur;
        cur = cur->right;
    }
    return std::pair(parent, cur);
}

template<typename T>
std::pair<ParentNode<T>*, CurrentNode<T>*> BST<T>::findBottomDownInOrderSuccessor(Node<T> *node) const{
    const Node<T> *parent = node;
    const Node<T> *cur = node->right;
    while(cur && cur->left){
        cur = cur->left;
    }
    return std::pair(parent, cur);
}


template<typename T>
void BST<T>::preOrderS(const std::function<void(const Node<T> *)> &lambda) const{
    std::stack<const Node<T> *> stack;
    const Node<T> *cur;
    stack.push(root);
    while(!stack.empty()){
        cur = stack.top();
        lambda(cur);
        stack.pop();
        if(cur->right) stack.push(cur->right);
        if(cur->left)  stack.push(cur->left);
    }
}

template<typename T>
void BST<T>::inOrderS(const std::function<void(const Node<T> *)> &lambda) const{
    std::stack<const Node<T> *> stack;
    const Node<T> *cur = root;
    while(cur || !stack.empty()){
        if(cur){
            stack.push(cur);
            cur = cur->left;
        }else{
            cur = stack.top();
            stack.pop();
            lambda(cur);
            cur = cur->right;
        }
    }
}

template<typename T>
void BST<T>::inOrder(const std::function<void(const Node<T> *)> &lambda){
    Node<T> *cur{root};
    Node<T> *pred;
    while(cur != nullptr){
        if(cur->left == nullptr){
            // if no left child, visit the node and go to the right
            lambda(cur);
            cur = cur->right;
        } else {
            // before going left:
            // we need to set up the thread, that connects "inorder predecessor of the cur" to the "cur"
            // Go to the cur inorder predecessor
            pred = cur->left;
            while(pred->right && pred->right != cur){
                pred = pred->right;
            }
            if(pred->right == nullptr){
                // if predecessor->right child was null, set up the thread (pred->right = cur)
                // then go and process the left subtree of the cur
                pred->right = cur;
                cur = cur->left;
            }else {
                // if pred->right was current, we have already processed the left subtree; remove the thread (set it back to nullptr again)
                // process the cur (since we already processed the left subtree)
                // move to the right subtree
                pred->right = nullptr;
                lambda(cur);
                cur = cur->right;
            }
        }
    }
}

template<typename T>
void BST<T>::preOrder(const std::function<void(const Node<T> *)> &lambda) {
    Node<T> *cur{root};
    Node<T> *prev;
    while(cur != nullptr){
        if(cur->left == nullptr){
            // if no left child, visit the node and go to the right
            lambda(cur);
            cur = cur->right;
        } else {
            // before going left:
            // we need to set up the thread, that connects "inorder predecessor of the cur" to the "cur"
            // Go to the cur inorder predecessor
            prev = cur->left;
            while(prev->right && prev->right != cur){
                prev = prev->right;
            }
            if(prev->right == nullptr){
                // if predecessor->right child was null, set up the thread (pred->right = cur)
                // visit the cur
                // then go and process the left subtree of the cur
                prev->right = cur;
                lambda(cur);
                cur = cur->left;
            }else {
                // if pred->right was current, we have already processed the left subtree; remove the thread (set it back to nullptr again)
                // move to the right subtree
                prev->right = nullptr;
                cur = cur->right;
            }
        }
    }
}

template<typename T>
void BST<T>::postOrder(const std::function<void(const Node<T> *)> &lambda) {
    Node<T> *cur;
    Node<T> *temp, *prev, *temp2, *dummy = new Node<T>(T());
    // "dummy" is a node created to be the parent of the root, it will be deleted at the end.
    dummy->left = root;
    cur = dummy;
    Node<T> *pred;
    while(cur != nullptr){
        if(cur->left == nullptr){
            // if no left child, just go to the right
            cur = cur->right;
        } else {
            // before going left:
            // we need to set up the thread, that connects "inorder predecessor of the cur" to the "cur",
            // Go to the cur inorder predecessor
            pred = cur->left;
            while(pred->right && pred->right != cur){
                pred = pred->right;
            }
            if(pred->right == nullptr){
                // if predecessor->right child was null, set up the thread (pred->right = cur)
                // then go and process the left subtree of the cur
                pred->right = cur;
                cur = cur->left;
            }else {
                // if pred->right was current, we have already passed that subtree.
                temp = cur->left;
                prev = cur;
                // start "temp" from the "cur->left" to the "predecessor", set the right child of "temp" to the parent of "temp"
                while(temp != cur){
                    temp2 = temp->right;
                    temp->right = prev;
                    prev = temp;
                    temp = temp2;
                }

                // move from the child up to the current node:
                // the first round is from the left child up to the parent(only the left child will be visited)
                // the second round is from the right child up to the parent (the right child and then the parent will be visited as well)
                temp = pred;
                temp2 = nullptr;
                while(temp != cur){
                    lambda(temp);
                    prev = temp->right;
                    temp->right = temp2;
                    temp2 = temp;
                    temp = prev;
                }
                pred->right = nullptr;
                cur = cur->right;
            }
        }
    }
    delete dummy;
}

template<typename T>
void BST<T>::postOrderS(const std::function<void(const Node<T> *)> &lambda) const{
    std::stack<const Node<T> *> stack;
    const Node<T> *cur{root}, *temp;
    while(cur || !stack.empty()){
        if(cur){
            stack.push(cur);
            cur = cur->left;
        }else{
            temp = stack.top()->right;
            if(temp){
               cur = temp;
            }else{
                temp = stack.top();
                lambda(temp);
                stack.pop();
                while(!stack.empty() && temp == stack.top()->right){
                    temp = stack.top();
                    stack.pop();
                    lambda(temp);
                }
            }
        }
    }
}

template<typename T>
typename BST<T>::iterator BST<T>::begin() const {
    return BST<T>::iterator(getMin(root), root);
}

template<typename T>
const typename BST<T>::iterator BST<T>::end() const {
    return iterator();
}

template<typename T>
typename BST<T>::reverse_iterator BST<T>::rbegin() const {
    return BST<T>::reverse_iterator(getMax(root), root);
}

template<typename T>
const typename BST<T>::reverse_iterator BST<T>::rend() const {
    return reverse_iterator();
}

// ITERATOR
template<typename T>
BST<T>::iterator::iterator(): ptr{nullptr}, cur_internal{nullptr} {
}


template<typename T>
BST<T>::iterator::iterator(const Node<T> *node, const Node<T> *root){
    init(node, root);
}
template<typename T>
void BST<T>::iterator::init(const Node<T> *node, const Node<T> *root) {
    cur_internal = root;
    while(ptr != node){
        getNext();
    }
}

template<typename T>
void BST<T>::iterator::getNext() {
    if(!(cur_internal || !stack.empty())){
        ptr = nullptr;
        return;
    }
    while(cur_internal || !stack.empty()){
        if(cur_internal){
            stack.push(cur_internal);
            cur_internal = cur_internal->left;
        }else{
            cur_internal = stack.top();
            stack.pop();
            ptr = cur_internal;
            cur_internal = cur_internal->right;
            break;
        }
    }
}

template<typename T>
typename BST<T>::iterator &BST<T>::iterator::operator++() {
    if(!ptr) return *this;
    getNext();
    return *this;
}


template<typename T>
typename BST<T>::iterator BST<T>::iterator::operator++(int) {
    if(!ptr) return *this;
    BST<T>::iterator it = *this;
    ++(*this);
    return it;
}


template<typename T>
bool BST<T>::iterator::operator!=(const BST<T>::iterator &rhs) const {
    return ptr != rhs.ptr;
}

template<typename T>
const T &BST<T>::iterator::operator*() const {
    return ptr->data;
}

template<typename T>
BST<T>::reverse_iterator::reverse_iterator(): iterator() {}
template<typename T>
BST<T>::reverse_iterator::reverse_iterator(const Node<T> *node, const Node<T> *root) {
    init(node, root);
}

template<typename T>
void BST<T>::reverse_iterator::getNext() {
    auto &cur_internal = BST<T>::iterator::cur_internal;
    auto &ptr = BST<T>::iterator::ptr;
    auto &stack = BST<T>::iterator::stack;

    if(!(cur_internal || !stack.empty())){
        ptr = nullptr;
        return;
    }
    while(cur_internal || !stack.empty()){
        if(cur_internal){
            stack.push(cur_internal);
            cur_internal = cur_internal->right;
        }else{
            cur_internal = stack.top();
            stack.pop();
            ptr = cur_internal;
            cur_internal = cur_internal->left;
            break;
        }
    }
}

template<typename T>
void BST<T>::reverse_iterator::init(const Node<T> *node, const Node<T> *root) {
    BST<T>::iterator::cur_internal = root;
    while(BST<T>::iterator::ptr != node){
        getNext();
    }
}