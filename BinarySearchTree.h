#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }


    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    bool insert( const Comparable & x )
    {
        return insert( x, root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

    int RankOfKey(int & x){
        return RankOfKey(x, root);
    }

    // BinaryNode* KeyOfRank(int k){
    //   return KeyOfRank(k, root);
    // }

    int getSize(){
      return size(root);
    }

    int Treeheight() {
        if (isEmpty()) {
            return -1;
        }
        else
            return(Treeheight(root, 0));
    }

    void inOrderTrav(vector<int> & vectorB){
      if(isEmpty()){
        return;
      }
      else
        return inOrderTrav(root, vectorB);
    }

  private:
    struct BinaryNode
    {
        Comparable element;
        int size;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }

        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    bool insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr ){
            t = new BinaryNode{ x, nullptr, nullptr };
            t->size = 1;
            return true;
        }
        else if( x < t->element ){
            bool temp = insert(x, t->left);
            if(temp){
              t->size = t->size + 1;
              return true;
            }
            else {
              return false;
            }
            if(x == t->element){
              return false;
            }
        }
        else if( t->element < x ){
            bool temp = insert(x, t->right);
            if(temp){
              t->size = t->size+1;
              return true;
            }
            else{
              return false;
            }
        }
        else if(x == t->element){
              return false;  // Duplicate; do nothing
        }
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }

    int RankOfKey(int & x, BinaryNode* T){
      if(T == nullptr){
        return 0;
      }
      if(x < T->element){
        return RankOfKey(x, T->left);
      }
      else if(x == T->element){
        return 1 + size(T->left);
      }
      else{
        return 1 + size(T->left) + RankOfKey(x, T->right);
      }
    }

    // BinaryNode* KeyOfRank(int k, BinaryNode* T){
    //   if(T == NULL || (k < min(T) || k > max(T))){
    //     return NULL;
    //   }
    //   if(size(T-left) == k-1){
    //     return T;
    //   }
    //   if(size(T->left) >= k){
    //     return KeyOfRank(k, T->left);
    //   }
    //   else{
    //     return KeyOfRank(k - size(T->left) - 1, T-right);
    //   }
    // }

    int size(BinaryNode* T){
      if(T == NULL){
        return 0;
      }
      return T->size;
    }

    int Treeheight(BinaryNode *t, int currentdepth) {
        if (t == nullptr)
            return(currentdepth);
        else {
            int rheight = Treeheight(t->right, currentdepth + 1);
            int lheight = Treeheight(t->left, currentdepth + 1);

            return(rheight > lheight ? rheight : lheight);
        }
    }

    void inOrderTrav(BinaryNode *t, vector<int> & vectorB){
      if(t == NULL){
        return;
      }
      inOrderTrav(t->left, vectorB);
      vectorB.push_back(t->element);
      inOrderTrav(t->right, vectorB);
    }

    // bool delete(T, x){
    //   //Delete X from T and return true if successful
    //   if(T == NULL){
    //     return false;
    //   }
    //   if(x < T->element){
    //     bool temp = Delete(T->left, x);
    //     if(temp){
    //       T->size = T->size - 1;
    //       return true;
    //     }
    //     else
    //       return false;
    //   }
    //   if(x > T->element){
    //     bool temp = Delete(T->right, x);
    //     if(temp){
    //       T->size = T->size - 1;
    //       return true;
    //     }
    //     else
    //       return false;
    //   }
    //   if(x == T->element){
    //     if(T->left == NULL && T->right == NULL){
    //       T = NULL;
    //       return true;
    //     }
    //     else if(T->left != nullptr && T->right == nullptr){
    //       T = T->left;
    //       return true;
    //     }
    //     else if(T->right != nullptr && T->left == nullptr){
    //       T = T->right;
    //       return true;
    //     }
    //     else if() //Has 2 children
    //
    //
    //
    //
    //   }
    // } // End Delete


};

#endif
