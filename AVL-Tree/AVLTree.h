#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// AVL Node Clas
template<class K, class V>
class AVLTreeNode {
public:
    // Should have attributes named:
    // parent - pointer to parent
    // left - pointer to left child
    // right - pointer to right child
    // key - node's key
    // value - node's value
    // height - node's height
    K key;
    V value;

    AVLTreeNode *left;
    AVLTreeNode *right;
    AVLTreeNode *parent;

    int height{};

    // Constructors ...
    AVLTreeNode(K ky, V val) {
        key = ky;
        value = val;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        height = 0;
    }

    AVLTreeNode(K key, V value, AVLTreeNode *parent, AVLTreeNode *left, AVLTreeNode *right) {
        this->key = key;
        this->value = value;
        this->parent = parent;
        this->left = left;
        this->right = right;
        this->height = 0;
    }
};

// AVL Tree class
template<class K, class V>
class AVLTree {
private:
    // Tree attributes go here
    // Your tree MUST have a root node named root
    AVLTreeNode<K, V> *root;
    int treeSize;

    AVLTreeNode<K, V> *copy(AVLTreeNode<K, V> *rhs) const;

    void valuesHelper(AVLTreeNode<K, V> *node, vector<V> &vs) const;

    void keysHelper(AVLTreeNode<K, V> *node, vector<V> &ks) const;

    void deleteAll(AVLTreeNode<K, V> *node);

    V searchHelper(AVLTreeNode<K, V> *node, const K &k) const;

    bool searchBoolHelper(AVLTreeNode<K, V> *node, const K &k) const;

    void rightRotate(AVLTreeNode<K, V> *a);

    AVLTreeNode<K, V> *rightRotateNode(AVLTreeNode<K, V> *a);

    void leftRotate(AVLTreeNode<K, V> *a);

    AVLTreeNode<K, V> *leftRotateNode(AVLTreeNode<K, V> *a);

    AVLTreeNode<K, V> *removeHelper(AVLTreeNode<K, V> *node, K a);

    void updateBF(AVLTreeNode<K, V> *node);

    void fixBF(AVLTreeNode<K, V> *node);

public:
    AVLTree();

    AVLTree(const AVLTree<K, V> &avl);

    AVLTree<K, V> &operator=(const AVLTree<K, V> &avl);

    ~AVLTree();

    bool insert(const K &key, const V &value);

    bool remove(const K &key);

    V search(const K &key) const;

    vector<V> values() const;

    vector<K> keys() const;

    int size() const;

    bool searchBool(const K &k) const;

    void *getRoot() const { return root; };

    int getHeight(AVLTreeNode<K, V> *node) const;
};
// AVL Tree Methods go here

template<class K, class V>
int AVLTree<K, V>::getHeight(AVLTreeNode<K, V> *node) const {
    if (node == nullptr) return 0;
    return node->height;
}


template<class K, class V>
AVLTreeNode<K, V> *AVLTree<K, V>::copy(AVLTreeNode<K, V> *rhs) const {
    if (rhs == nullptr) return nullptr;

    AVLTreeNode<K, V> *lhs = new AVLTreeNode<K, V>(rhs->key, rhs->value);

    lhs->left = copy(rhs->left);

    lhs->height = rhs->height;

    if (lhs->left != nullptr) lhs->left->parent = lhs;

    lhs->right = copy(rhs->right);

    if (lhs->right != nullptr) lhs->right->parent = lhs;

    return lhs;
}

template<class K, class V>
void AVLTree<K, V>::valuesHelper(AVLTreeNode<K, V> *node, vector<V> &vs) const {
    if (node != nullptr) {
        valuesHelper(node->left, vs);
        vs.push_back(node->value);
        valuesHelper(node->right, vs);
    }
}

template<class K, class V>
void AVLTree<K, V>::keysHelper(AVLTreeNode<K, V> *node, vector<V> &ks) const {
    if (node != nullptr) {
        keysHelper(node->left, ks);
        ks.push_back(node->key);
        keysHelper(node->right, ks);
    }
}

template<class K, class V>
void AVLTree<K, V>::deleteAll(AVLTreeNode<K, V> *node) {
    if (!node)
        return;
    deleteAll(node->left);
    deleteAll(node->right);
    delete node;
}

template<class K, class V>
V AVLTree<K, V>::searchHelper(AVLTreeNode<K, V> *node, const K &k) const {
    if (node == nullptr) {
        throw std::runtime_error("Key not found");
    }
    if (k == node->key) {
        return node->value;
    }

    if (k < node->key) {
        return searchHelper(node->left, k);
    }
    return searchHelper(node->right, k);
}

template<class K, class V>
bool AVLTree<K, V>::searchBoolHelper(AVLTreeNode<K, V> *node, const K &k) const {
    if (node == nullptr) {
        return false;
    }
    if (k == node->key) {
        return true;
    }

    if (k < node->key) {
        return searchBoolHelper(node->left, k);
    }
    return searchBoolHelper(node->right, k);
}

template<class K, class V>
void AVLTree<K, V>::rightRotate(AVLTreeNode<K, V> *a) {
    AVLTreeNode<K, V> *b = a->left;
    a->left = b->right;
    if (b->right != nullptr) {
        b->right->parent = a;
    }
    b->parent = a->parent;
    if (a->parent == nullptr) {
        root = b;
    } else if (a == a->parent->right) {
        a->parent->right = b;
    } else {
        a->parent->left = b;
    }
    b->right = a;
    a->parent = b;


    a->height = a->height + 1 - min(0, b->height);
    b->height = b->height + 1 + max(0, a->height);

}

template<class K, class V>
AVLTreeNode<K, V> *AVLTree<K, V>::rightRotateNode(AVLTreeNode<K, V> *a) {
    AVLTreeNode<K, V> *b = a->left;
    a->left = b->right;
    if (b->right != nullptr) {
        b->right->parent = a;
    }
    b->parent = a->parent;
    if (a->parent == nullptr) {
        root = b;
    } else if (a == a->parent->right) {
        a->parent->right = b;
    } else {
        a->parent->left = b;
    }
    b->right = a;
    a->parent = b;


    a->height = a->height + 1 - min(0, b->height);
    b->height = b->height + 1 + max(0, a->height);

    return b;
}

template<class K, class V>
void AVLTree<K, V>::leftRotate(AVLTreeNode<K, V> *a) {
    AVLTreeNode<K, V> *b = a->right;
    a->right = b->left;
    if (b->left != nullptr) {
        b->left->parent = a;
    }
    b->parent = a->parent;
    if (a->parent == nullptr) {
        root = b;
    } else if (a == a->parent->left) {
        a->parent->left = b;
    } else {
        a->parent->right = b;
    }
    b->left = a;
    a->parent = b;


    a->height = a->height - 1 - max(0, b->height);
    b->height = b->height - 1 + min(0, a->height);

}

template<class K, class V>
AVLTreeNode<K, V> *AVLTree<K, V>::leftRotateNode(AVLTreeNode<K, V> *a) {
    AVLTreeNode<K, V> *b = a->right;
    a->right = b->left;
    if (b->left != nullptr) {
        b->left->parent = a;
    }
    b->parent = a->parent;
    if (a->parent == nullptr) {
        root = b;
    } else if (a == a->parent->left) {
        a->parent->left = b;
    } else {
        a->parent->right = b;
    }
    b->left = a;
    a->parent = b;


    a->height = a->height - 1 - max(0, b->height);
    b->height = b->height - 1 + min(0, a->height);

    return b;
}

template<class K, class V>
AVLTreeNode<K, V> *AVLTree<K, V>::removeHelper(AVLTreeNode<K, V> *node, K a) {
    if (node == nullptr) return nullptr;
    if (a < node->key) {
        node->left = removeHelper(node->left, a);
    } else if (a > node->key) {
        node->right = removeHelper(node->right, a);
    } else {
        AVLTreeNode<K, V> *right = node->right;
        if (node->right == nullptr) {
            AVLTreeNode<K, V> *left = node->left;
            delete (node);
            node = left;
        } else if (node->left == nullptr) {
            delete (node);
            node = right;
        } else {
            while (right->left != nullptr) right = right->left;
            node->key = right->key;
            node->right = removeHelper(node->right, right->key);
        }
    }
    if (node == nullptr) return node;


    int bal = getHeight(node->left) - getHeight(node->right);

    if (bal > 1) {
        if (getHeight(node->left) >= getHeight(node->right)) {
            return rightRotateNode(node);
        } else {
            node->left = leftRotateNode(node->left);
            return rightRotateNode(node);
        }
    } else if (bal < -1) {
        if (getHeight(node->right) >= getHeight(node->left)) {
            return leftRotateNode(node);
        } else {
            node->right = rightRotateNode(node->right);
            return leftRotateNode(node);
        }
    }
    return node;
}

template<class K, class V>
void AVLTree<K, V>::updateBF(AVLTreeNode<K, V> *node) {
    if (node->height < -1 || node->height > 1) {
        fixBF(node);
        return;
    }

    if (node->parent != nullptr) {
        if (node == node->parent->left) {
            node->parent->height -= 1;
        }

        if (node == node->parent->right) {
            node->parent->height += 1;
        }

        if (node->parent->height != 0) {
            updateBF(node->parent);
        }
    }
}

template<class K, class V>
void AVLTree<K, V>::fixBF(AVLTreeNode<K, V> *node) {
    if (node->height > 0) {
        if (node->right->height < 0) {
            rightRotate(node->right);
            leftRotate(node);
        } else {
            leftRotate(node);
        }
    } else if (node->height < 0) {
        if (node->left->height > 0) {
            leftRotate(node->left);
            rightRotate(node);
        } else {
            rightRotate(node);
        }
    }
}

template<class K, class V>
AVLTree<K, V>::AVLTree() {
    root = nullptr;
    treeSize = 0;
}

template<class K, class V>
AVLTree<K, V>::AVLTree(const AVLTree<K, V> &other) {
    if (other.treeSize == 0) {
        root = nullptr;

        treeSize = 0;
        return;
    }
    root = copy(other.root);
    treeSize = 0;
}

template<class K, class V>
AVLTree<K, V> &AVLTree<K, V>::operator=(const AVLTree<K, V> &other) {
    if (&other != this) {
        deleteAll(root);
        root = copy(other.root);
        treeSize = other.treeSize;
    }
    return *this;
}

template<class K, class V>
AVLTree<K, V>::~AVLTree() {
    deleteAll(root);
    root = nullptr;
    treeSize = 0;
}

template<class K, class V>
bool AVLTree<K, V>::insert(const K &key, const V &value) {
    if (searchBool(key)) return false;

    treeSize++;
    auto *node = new AVLTreeNode<K, V>(key, value);
    cout << node->key;
    AVLTreeNode<K, V> *b = nullptr;
    AVLTreeNode<K, V> *a = root;

    while (a != nullptr) {
        b = a;
        if (node->key < a->key) {
            a = a->left;
        } else {
            a = a->right;
        }
    }


    node->parent = b;
    if (b == nullptr) {
        root = node;
    } else if (node->key < b->key) {
        b->left = node;
    } else {
        b->right = node;
    }

    updateBF(node);
    return true;
}

template<class K, class V>
bool AVLTree<K, V>::remove(const K &key) {
    if (!searchBool(key)) return false;
    treeSize--;
    root = removeHelper(root, key);
    return true;
}

template<class K, class V>
V AVLTree<K, V>::search(const K &k) const {
    return searchHelper(root, k);
}

template<class K, class V>
bool AVLTree<K, V>::searchBool(const K &k) const {
    return searchBoolHelper(root, k);
}

template<class K, class V>
vector<V> AVLTree<K, V>::values() const {
    vector<V> vals;
    valuesHelper(root, vals);
    return vals;
}

template<class K, class V>
vector<K> AVLTree<K, V>::keys() const {
    vector<V> ks;
    keysHelper(root, ks);
    return ks;
}

template<class K, class V>
int AVLTree<K, V>::size() const {
    return treeSize;
}



