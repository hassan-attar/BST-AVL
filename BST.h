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
public:
    class iterator {
    protected:
        const Node<T> *ptr;
        const Node<T> *cur_internal;
        std::stack<const Node<T> *> stack;
        virtual void getNext();
        virtual void init(const Node<T> *node, const Node<T> *root);
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = size_t;
        using pointer = T*;
        using reference = T&;
        iterator();
        explicit iterator(const Node<T> *node, const Node<T> *root);
        iterator & operator++();
        iterator operator++(int);
        bool operator!=(const BST<T>::iterator &rhs) const;
        const T &operator*() const;
    };

    class reverse_iterator : public iterator{
        void getNext() override;
        void init(const Node<T> *node, const Node<T> *root) override;
    public:
        reverse_iterator();
        explicit reverse_iterator(const Node<T> *node, const Node<T> *root);
    };



    using ParentNode = Node<T>;
    using CurrentNode = Node<T>;

    BST();
    BST(std::initializer_list<T> &list);
    BST(const T*, int size);


    bool insert(const T &data);
    bool remove(const T &data);
    const Node<T> *search(const T& data) const;
    const Node<T> *getSuccessor(const Node<T>* node) const;
    const Node<T> *getPredecessor(const Node<T>* node) const;
    inline const Node<T> *getMax() const;
    inline const Node<T> *getMin() const;
    const Node<T> *getMax(const Node<T> *node) const;
    const Node<T> *getMin(const Node<T> *node) const;
    inline size_t getHeight() const;
    inline size_t getHeightRecursive() const;
    size_t getHeight(const Node<T> *node) const;
    size_t getHeightRecursive(const Node<T> *node) const;
    inline constexpr size_t getSize() const;

    std::vector<const Node<T>*> *getPath(const T& data) const;
    void displayTree(size_t maxDataFieldPrintWidth, size_t horizontal_scale = 3) const;


    void inOrderS(const std::function<void(const Node<T> *node)> &lambda) const;
    void inOrder(const std::function<void(const Node<T> *node)> &lambda);
    void preOrderS(const std::function<void(const Node<T> *node)> &lambda) const;
    void preOrder(const std::function<void(const Node<T> *node)> &lambda);
    void postOrder(const std::function<void(const Node<T> *node)> &lambda);
    void postOrderS(const std::function<void(const Node<T> *node)> &lambda) const;


    static inline constexpr size_t getMaxNodeCount(size_t height);
    static inline constexpr size_t getMinNodeCount(size_t height);
    static inline constexpr size_t getMaxHeight(size_t nodeCount);
    static inline constexpr size_t getMinHeight(size_t nodeCount);



    iterator begin() const;
    const iterator end() const;
    reverse_iterator rbegin() const;
    const reverse_iterator rend() const;
private:
    void swap(std::pair<ParentNode *, CurrentNode *> &p1, std::pair<ParentNode *, CurrentNode *> &p2);
    void swapIndependentNodes(std::pair<ParentNode *, CurrentNode *> &p1, std::pair<ParentNode *, CurrentNode *> &p2);
    void swapParentChildNodes(std::pair<ParentNode *, CurrentNode *> &p1, std::pair<ParentNode *, CurrentNode *> &p2);
    std::pair<ParentNode *, CurrentNode *> findParent(const T& data) const;
    std::pair<ParentNode *, CurrentNode *> findBottomDownInOrderSuccessor(Node<T>* node) const;
    std::pair<ParentNode *, CurrentNode *> findBottomDownInOrderPredecessor(Node<T>* node) const;
    std::vector<const Node<T>*> *convertToVector(const Node<T>* node) const;
    void shuffleRandomized(int *arr, int size);
    Node<T> *root;
    size_t size;
};

#include "BST.tpp"


#endif //BST_BST_H
