#ifndef TREE_H
#define TREE_H

#include <functional>
#include <stack>

template<typename KeyT, typename ValT>
class BinaryTree
{
public:
    struct Node
    {
        KeyT key;
        ValT value;
        Node *left, right;

        void set( KeyT const &newKey, ValT const &newVal )
        {
            key = newKey;
            value = newVal;
        }
    };

    BinaryTree( void )
    {
        root = nullptr;
    }

    BinaryTree & add( KeyT const &key, ValT const &val )
    {
        Node *node = findNode(key);

        if (node == nullptr)
            node = new Node{key, val, nullptr, nullptr};
        else
            node->set(key, val);
    }

    bool find( KeyT const &key, ValT &val ) const
    {
        Node const * node = findNode(key);
        if (node != nullptr)
            val = node->value;
        return node != nullptr;
    }

    bool remove( KeyT key, ValT &val )
    {
        Node
                *ancestor = findPrevNode(key),
                *node;

        if (ancestor-> left == nullptr &&
            ancestor->right == nullptr)
            return false;

        bool left;

        if (ancestor->left->key == key)
            node = ancestor->left, left = true;
        else
            node = ancestor->right, left = false;

        // no children
        if (node->left == nullptr && node->right == nullptr)
        {
            left ? ancestor->left == nullptr : ancestor->right = nullptr;
            val = node->value;
            delete node;
        }
        else if (node->left != nullptr && node->right != nullptr)
        {
            if (node->right->left == nullptr)
            {
                node->right->left = node->left;
                (!left ? ancestor->right : ancestor->left) = node->right;
                delete node;
            }
            else
            {
                Node *leftist = node->right;

                while (leftist->left != nullptr)
                    leftist = leftist->left;

                leftist->left = node->left;
                (!left ? ancestor->right : ancestor->left) = node->right;
                delete node;
            }
        }
        else
        {
            (!left ? ancestor->right : ancestor->left) = (node->left == nullptr) ? node->right : node->left;
            delete node;
        }
    }

    void print( void ) const
    {

    }
private:
    void traverse( Node *node, std::function<void(void)> const &f )
    {

    }

    Node const * findNode( KeyT key ) const
    {
        Node *node = root;

        while (node != nullptr)
        {
            if (key < node->key)
                node = node->left;
            else if (key > node->key)
                node = node->right;
            else
                break;
        }

        return node;
    }

    Node const * findPrevNode( KeyT key ) const
    {
        Node *node = root;

        while (node != nullptr)
        {
            if (node->left->key == key || node->right->key == key ||
               (node->left == nullptr && node->right == nullptr))
                break;

            if (key < node->key)
                node = node->left;
            else if (key > node->key)
                node = node->right;
        }

        return node;
    }

    Node *root;
};

#endif // TREE_H
