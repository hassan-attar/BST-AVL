//
// Created by Hassan Attar on 2024-02-12.
//

#ifndef BST_BST_H
#define BST_BST_H
#include "iostream"
#include "Node.h"
#include "initializer_list"
#include "stack"

template<typename T>
class BST {
protected:
    using ParentNode = Node<T>;
    using CurrentNode = Node<T>;  // For better readability
    Node<T> *root;
    size_t size;

    // ########## Helpers ##########
    // High-Level Helpers
    void swap(std::pair<ParentNode *, CurrentNode *> &p1, std::pair<ParentNode *, CurrentNode *> &p2);
    void shuffleRandomized(T *arr, int size);
    std::pair<ParentNode *, CurrentNode *> findParent(const T& data) const;
    std::pair<ParentNode *, CurrentNode *> findBottomDownInOrderSuccessor(Node<T>* node) const;
    std::pair<ParentNode *, CurrentNode *> findBottomDownInOrderPredecessor(Node<T>* node) const;
    // Low-Level Helpers
    void swapIndependentNodes(std::pair<ParentNode *, CurrentNode *> &p1, std::pair<ParentNode *, CurrentNode *> &p2);
    void swapParentChildNodes(std::pair<ParentNode *, CurrentNode *> &p1, std::pair<ParentNode *, CurrentNode *> &p2);
    std::vector<const Node<T>*> *convertToVector(const Node<T>* node) const;
public:
    // ########## Static Methods ##########
    static inline constexpr size_t getMaxNodeCount(size_t height);
    static inline constexpr size_t getMinNodeCount(size_t height);
    static inline constexpr size_t getMaxHeight(size_t nodeCount);
    static inline constexpr size_t getMinHeight(size_t nodeCount);
    // ########## Iterator Class ##########
    class iterator {
    private:
        const Node<T> *ptr;                 // pointer to the node, holding data
        const Node<T> *cur_internal;        // cur pointer in the current inorder traversal iteration
        std::stack<const Node<T> *> stack;  // stack holding pointers in the inorder traversal
        // %%%% Helpers %%%%
        virtual void init(const Node<T> *node, const Node<T> *root);
        virtual void getNext();
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = size_t;
        using pointer = T*;
        using reference = T&;
        // %%%% Constructors %%%%
        iterator();
        explicit iterator(const Node<T> *node, const Node<T> *root);
        ~iterator() = default;
        // %%%% Operator Overload %%%%
        iterator &operator++();
        iterator operator++(int);
        bool operator!=(const BST<T>::iterator &rhs) const;
        const T &operator*() const;
    };
    // ########## Reverse Iterator Class ##########
    class reverse_iterator : public iterator{
        // %%%% Helpers (override) %%%%
        void init(const Node<T> *node, const Node<T> *root) override;
        void getNext() override;
    public:
        // %%%% Constructors %%%%
        reverse_iterator();
        explicit reverse_iterator(const Node<T> *node, const Node<T> *root);
    };

    iterator begin() const;
    const iterator end() const;
    reverse_iterator rbegin() const;
    const reverse_iterator rend() const;
    // ########## Constructor, Destructor, Copy/Move Semantics ##########
    BST();
    BST(const std::initializer_list<T> &list);
    BST(const T*, int size);


    // ########## Iterative Interface ##########
    virtual bool insert(const T &data);
    virtual bool remove(const T &data);
    const Node<T> *search(const T& data) const;
    const Node<T> *getSuccessor(const Node<T>* node) const;
    const Node<T> *getPredecessor(const Node<T>* node) const;
    inline size_t getHeight() const;
    size_t getHeight(const Node<T> *node) const;
    inline constexpr size_t getSize() const;
    inline const Node<T> *getMax() const;
    inline const Node<T> *getMin() const;
    const Node<T> *getMax(const Node<T> *node) const;
    const Node<T> *getMin(const Node<T> *node) const;
    std::vector<const Node<T>*> *getPath(const T& data) const;
    void displayTree(size_t maxDataFieldPrintWidth, size_t horizontal_scale = 3) const;

    // Iterative, Space Efficient Traversals using "Morris Traversal" Algorithm: Time O(n), Space O(1)
    void inOrder(const std::function<void(const Node<T> *node)> &lambda);
    void preOrder(const std::function<void(const Node<T> *node)> &lambda);
    void postOrder(const std::function<void(const Node<T> *node)> &lambda);

    // Iterative Traversals using Stack: Time O(n), Space O(log(n))
    void inOrderS(const std::function<void(const Node<T> *node)> &lambda) const;
    void preOrderS(const std::function<void(const Node<T> *node)> &lambda) const;
    void postOrderS(const std::function<void(const Node<T> *node)> &lambda) const;

    // ########## Recursive Interface ##########
    inline size_t getHeightRecursive() const;
    size_t getHeightRecursive(const Node<T> *node) const;
    void inOrderRecursive(const Node<T> *node, const std::function<void(const Node<T> *node)> &lambda) const;
    void preOrderRecursive(const Node<T> *node, const std::function<void(const Node<T>* node)> &lambda) const;
    void postOrderRecursive(const Node<T> *node, const std::function<void(const Node<T>* node)> &lambda) const;


    // DELETE LATER
    int singleParent(){
        return singleParent(root);
    }
    int singleParent(Node<T> *node){
        if(node){
            int left = singleParent(node->left);
            int right = singleParent(node->right);
            if((!node->left) ^ (!node->right)){
                return left + right + 1;
            }
            return right + left;
        }
        return 0;
    }
    int sumAtLevelK(int k){
        return sumAtLevelK(root, k, 0);
    }
    int sumAtLevelK(Node<T> *node, int k, int curLevel){
        if(node){
            int left = sumAtLevelK(node->left, k, curLevel + 1);
            int right = sumAtLevelK(node->right, k, curLevel + 1);
            if(k == curLevel){
                return left + right + node->data;
            }
            return left + right;
        }
        return 0;
    }
};

#include "BST.tpp"


#endif //BST_BST_H
