/*
 * rbbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyErootistsErootception
 */
#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

/* -----------------------------------------------------
 * Red-Black Nodes and Search Tree
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
    RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
        : Node<KeyType, ValueType> (k, v, p)
    {
        color = red;
    }

    virtual ~RedBlackNode () {}

    Color getColor () const
    {
        return color;
    }

    void setColor (Color c)
    {
        color = c;
    }

    virtual RedBlackNode<KeyType, ValueType> *getParent () const
    {
        return (RedBlackNode<KeyType,ValueType>*) this->_parent;
    }

    virtual RedBlackNode<KeyType, ValueType> *getLeft () const
    {
        return (RedBlackNode<KeyType,ValueType>*) this->_left;
    }

    virtual RedBlackNode<KeyType, ValueType> *getRight () const
    {
        return (RedBlackNode<KeyType,ValueType>*) this->_right;
    }

protected:
    Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
public:
  void printRoot() {
    //std::cout << this->root->getRight()->getRight()->getKey() << "    " << static_cast<RedBlackNode<KeyType,ValueType>*>(this->root->getRight()->getLeft())->getColor() << std::endl;
  }

    void insert (const std::pair<const KeyType, ValueType>& new_item){
      int g = new_item.first;
      int f = new_item.second;
    Node<KeyType, ValueType>* mo = new RedBlackNode<KeyType, ValueType>(g, f, NULL);
    this->insertNode( mo );
    static_cast<RedBlackNode<KeyType,ValueType>*>(mo)->setColor( red);
    while ( (mo != this->root) && (static_cast<RedBlackNode<KeyType,ValueType>*>(mo->getParent())->getColor() == red) ) {
        //std::cout << "Entered the while loop" << std::endl;
        if ( mo->getParent() == mo->getParent()->getParent()->getLeft() ) {
            //std::cout << "Entered parent == left child of parent of parent" << std::endl;
            Node<KeyType, ValueType> *y = mo->getParent()->getParent()->getRight();
            if ( static_cast<RedBlackNode<KeyType,ValueType>*>(y)->getColor() == black ) {
                if ( mo == mo->getParent()->getRight() ) {
                    mo = mo->getParent();
                    left_rotate( mo );
                }
                static_cast<RedBlackNode<KeyType,ValueType>*>(mo->getParent())->setColor(black);
                static_cast<RedBlackNode<KeyType,ValueType>*>(mo->getParent()->getParent())->setColor(red);
                right_rotate( mo->getParent()->getParent() );
            }
            else {
                static_cast<RedBlackNode<KeyType,ValueType>*>(mo->getParent())->setColor(black);
                static_cast<RedBlackNode<KeyType,ValueType>*>(y)->setColor(black);
                static_cast<RedBlackNode<KeyType,ValueType>*>(mo->getParent()->getParent())->setColor(red);
                mo = mo->getParent()->getParent();
            }
        }
        else {
            //same thing but flip right and left
            //std::cout << "in the else" << std::endl;
            Node<KeyType, ValueType> *y = mo->getParent()->getParent()->getLeft();
            if (y != NULL &&  static_cast<RedBlackNode<KeyType,ValueType>*>(y)->getColor() == red ) {
                static_cast<RedBlackNode<KeyType,ValueType>*>(mo->getParent())->setColor(black);
                static_cast<RedBlackNode<KeyType,ValueType>*>(y)->setColor(black);
                static_cast<RedBlackNode<KeyType,ValueType>*>(mo->getParent()->getParent())->setColor(red);
                mo = mo->getParent()->getParent();
            }
            else {
                if ( mo == mo->getParent()->getLeft() ) {
                    mo = mo->getParent();
                    right_rotate( mo );
                }
                static_cast<RedBlackNode<KeyType,ValueType>*>(mo->getParent())->setColor(black);
                static_cast<RedBlackNode<KeyType,ValueType>*>(mo->getParent()->getParent())->setColor(red);
                left_rotate( mo->getParent()->getParent() );
            }
        }
    }
    static_cast<RedBlackNode<KeyType,ValueType>*>(this->root)->setColor(black);
    //std::string a [] = {"red","black"};
    //std::cout <<  mo->getKey() << "-->" << a[static_cast<RedBlackNode<KeyType,ValueType>*>(mo)->getColor()] << std::endl;
}
private:
void left_rotate(Node<KeyType, ValueType>* p)
{
        Node<KeyType, ValueType>*y = p->getRight();
        p->setRight(y->getLeft());
        if(y->getLeft()!=NULL){
            y->getLeft()->setParent(p);
        }
        y->setParent(p->getParent());
        if(p->getParent() == NULL) {
          this->root = y;
        }
        else {
          if(p == p->getParent()->getLeft()) {
            p->getParent()->setLeft(y);
          }
          else {
            p->getParent()->setRight(y);
          }
        }
        y->setLeft(p);
        p->setParent(y);

}

void right_rotate(Node<KeyType, ValueType>* p)
{
    Node<KeyType, ValueType>*y = p->getLeft();
        p->setLeft(y->getRight());
        if(y->getRight()!=NULL){
            y->getRight()->setParent(p);
        }
        y->setParent(p->getParent());
        if(p->getParent() == NULL) {
          this->root = y;
        }
        else {
          if(p == p->getParent()->getRight()) {
            p->getParent()->setRight(y);
          }
          else {
            p->getParent()->setLeft(y);
          }
        }
        y->setRight(p);
        p->setParent(y);

}


};


#endif
