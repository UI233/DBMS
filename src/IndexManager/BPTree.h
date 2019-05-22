//
// Created by logos on 2019/5/12.
//

#ifndef DBMS_BPTREE_H
#define DBMS_BPTREE_H


#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename T>
class BPTreeNode {
public:
    BPTreeNode() = default;

    BPTreeNode(int degree, bool isLeaf);

    ~BPTreeNode() {}

    bool search(const T &key, int &index) const;

    BPTreeNode *split(T &key);

    int add(const T &key);

    int add(const T &key, int offset);

    void removeAt(int index);

    bool isRoot() const { return parent == nullptr; }

    bool isLeaf;
    int degree, cnt;
    BPTreeNode *parent, *sibling;
    vector <T> keys;
    vector<int> keyOffset;
    vector<BPTreeNode<T> *> children;

    void debug(int id) {
        cout << "Keys [" << id << "]: ";
        for (int i = 0; i < this->cnt; i++) {
            cout << keys[i] << " ";
        }
        cout << endl;
    }

private:
    bool binarySearch(const T &key, int &index) const;
};

template<typename T>
BPTreeNode<T>::BPTreeNode(int degree, bool isLeaf) : degree(degree), isLeaf(isLeaf), cnt(0), parent(nullptr),
                                                     sibling(nullptr) {
    children.resize(degree + 1);
    keys.resize(degree);
    keyOffset.resize(degree);
}

template<typename T>
bool BPTreeNode<T>::search(const T &key, int &index) const {
}

template<typename T>
bool BPTreeNode<T>::binarySearch(const T &key, int &index) const {

}

template<typename T>
BPTreeNode<T> *BPTreeNode<T>::split(T &key) {

}

template<typename T>
int BPTreeNode<T>::add(const T &key) {

}

template<typename T>
int BPTreeNode<T>::add(const T &key, int offset) {

}

template<typename T>
void BPTreeNode<T>::removeAt(int index) {

}

template<typename T>
struct NodeSearchParse {
    int index;
    BPTreeNode<T> *node;
};

template<typename T>
class BPTree {
public:
    typedef BPTreeNode<T> *TreeNode;

    BPTree(string fileName, int sizeofKey, int degree);

    ~BPTree();

    TreeNode getHeadNode() const { return head; }

    int find(const T &key);

    NodeSearchParse<T> findNode(const T &key);

    bool insert(const T &key, int offset);

    bool remove(const T &key);

private:
    string fileName;
    TreeNode root, head;
    int sizeofKey, level, keyCount, nodeCount, degree;

    void initBPTree();

    bool findKeyFromNode(TreeNode node, const T &key, NodeSearchParse<T> &res);

    void cascadeInsert(TreeNode node);

    bool cascadeDelete(TreeNode node);

    bool deleteBranchLL(TreeNode node, TreeNode parent, TreeNode sibling, int index);

    bool deleteBranchLR(TreeNode node, TreeNode parent, TreeNode sibling, int index);

    bool deleteBranchRL(TreeNode node, TreeNode parent, TreeNode sibling, int index);

    bool deleteBranchRR(TreeNode node, TreeNode parent, TreeNode sibling, int index);

    bool deleteLeafLL(TreeNode node, TreeNode parent, TreeNode sibling, int index);

    bool deleteLeafLR(TreeNode node, TreeNode parent, TreeNode sibling, int index);

    bool deleteLeafRL(TreeNode node, TreeNode parent, TreeNode sibling, int index);

    bool deleteLeafRR(TreeNode node, TreeNode parent, TreeNode sibling, int index);

    void debug(TreeNode node, int id) {
        node->debug(id);
        if (!node->isLeaf) {
            for (int i = 0; i <= node->cnt; i++) {
                debug(node->children[i], i);
            }
        }
    }
};

template<typename T>
BPTree<T>::BPTree(string fileName, int sizeofKey, int degree) : fileName(fileName), sizeofKey(sizeofKey),
                                                                degree(degree), keyCount(0), nodeCount(0), level(0),
                                                                root(
                                                                        nullptr), head(nullptr) {
    initBPTree();
}

template<typename T>
BPTree<T>::~BPTree() {

}

template<typename T>
void BPTree<T>::initBPTree() {
}

template<typename T>
bool BPTree<T>::findKeyFromNode(TreeNode node, const T &key, NodeSearchParse<T> &res) {

}

template<typename T>
int BPTree<T>::find(const T &key) {

}

template<typename T>
NodeSearchParse<T> BPTree<T>::findNode(const T &key) {

}

template<typename T>
bool BPTree<T>::insert(const T &key, int offset) {

}

template<typename T>
void BPTree<T>::cascadeInsert(BPTree::TreeNode node) {

}

template<typename T>
bool BPTree<T>::remove(const T &key) {

}

template<typename T>
bool BPTree<T>::cascadeDelete(BPTree::TreeNode node) {

}

template<typename T>
bool BPTree<T>::deleteBranchLL(BPTree::TreeNode node, BPTree::TreeNode parent, BPTree::TreeNode sibling, int index) {

}

template<typename T>
bool BPTree<T>::deleteBranchLR(BPTree::TreeNode node, BPTree::TreeNode parent, BPTree::TreeNode sibling, int index) {

}

template<typename T>
bool BPTree<T>::deleteBranchRL(BPTree::TreeNode node, BPTree::TreeNode parent, BPTree::TreeNode sibling, int index) {

}

template<typename T>
bool BPTree<T>::deleteBranchRR(BPTree::TreeNode node, BPTree::TreeNode parent, BPTree::TreeNode sibling, int index) {

}

template<typename T>
bool BPTree<T>::deleteLeafLL(BPTree::TreeNode node, BPTree::TreeNode parent, BPTree::TreeNode sibling, int index) {

}

template<typename T>
bool BPTree<T>::deleteLeafLR(BPTree::TreeNode node, BPTree::TreeNode parent, BPTree::TreeNode sibling, int index) {

}

template<typename T>
bool BPTree<T>::deleteLeafRL(BPTree::TreeNode node, BPTree::TreeNode parent, BPTree::TreeNode sibling, int index) {

}

template<typename T>
bool BPTree<T>::deleteLeafRR(BPTree::TreeNode node, BPTree::TreeNode parent, BPTree::TreeNode sibling, int index) {

}

#endif //DBMS_BPTREE_H
