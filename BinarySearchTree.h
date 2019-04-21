#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
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
    bool contains( const Comparable & x, vector<int> & lineno ) const
    {
        return contains( x, lineno, root );
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
        out << "Binary Search Tree Index:" << endl
            << "-------------------------" << endl;
        if (isEmpty())
            out << "Empty tree" << endl;
        else
            printTree( root, out );
        out << endl;
    }

    void printTree(string fName) const {
      ofstream outFile(fName);
      ostream & out = outFile;
      out << "Binary Search Tree Index:" << endl
          << "-------------------------" << endl;
      if (isEmpty())
          out << "Empty tree" << endl;
      else
          printTree( root, out );
      out << endl;
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
    void insert( const Comparable & x, const int & lineno )
    {
        insert( x, lineno, root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x, int && lineno )
    {
        insert( std::move( x ), lineno, root );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

    /**
     * Added by Marty for lab7
     */
    int countTreeNodes() const
    {
        if (isEmpty()) {
            return -1;
        }
        else
            return(countTreeNodes(root));
    }

    int Treeheight() {
        if (isEmpty()) {
            return -1;
        }
        else
            return(Treeheight(root, 0));
    }

  private:
    struct BinaryNode
    {
        Comparable element;
        vector<int> lineNumberList;      // Line number where the word exists
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
    void insert( const Comparable & x, int lineno, BinaryNode * & t )
    {
        if (t == nullptr) {
            t = new BinaryNode{ x, nullptr, nullptr };
            t->lineNumberList.push_back(lineno);
        }
        else if( x < t->element )
            insert( x, lineno, t->left );
        else if( t->element < x )
            insert( x, lineno, t->right );
        else
            t->lineNumberList.push_back(lineno);  // Duplicate; add the line number
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(Comparable && x, int lineno, BinaryNode * & t)
    {
        if (t == nullptr) {
            t = new BinaryNode{ std::move(x), nullptr, nullptr };
            t->lineNumberList.push_back(lineno);
        }
        else if( x < t->element )
            insert(std::move(x), lineno, t->left);
        else if( t->element < x )
            insert(std::move(x), lineno, t->right);
        else
            t->lineNumberList.push_back(lineno);  // Duplicate; add the line number
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
    bool contains( const Comparable & x, vector<int> & lineno, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, lineno, t->left );
        else if( t->element < x )
            return contains( x, lineno, t->right );
        else {
            lineno = t->lineNumberList;
            return true;    // Match
        }
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
        if (t != nullptr)
        {
            int numbers_printed = 0;
            printTree(t->left, out);
            out << left << setw(16) << t->element << " ";
            for (const auto line : t->lineNumberList) {
                if (numbers_printed++ % 9 == 0)  // First number
                    out << line;
                else if (numbers_printed % 9)
                    out << ", " << line;
                else {
                    out << ", " << line << "," << endl
                        << left << setw(17) << " ";
                }
            }
            out << endl;
            printTree(t->right, out);
        }
    }

    /**
    * Internal method to print a subtree rooted at t in sorted order.
    */
    int countTreeNodes(BinaryNode *t) const
    {
        if (t == nullptr)
            return 0;
        else
            return(1 + countTreeNodes(t->left) + countTreeNodes(t->right));
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

    /**
    * Internal method to calculate the height of the tree
    */
    int Treeheight(BinaryNode *t, int currentdepth) {
        if (t == nullptr)
            return(currentdepth);
        else {
            int rheight = Treeheight(t->right, currentdepth + 1);
            int lheight = Treeheight(t->left, currentdepth + 1);

            return(rheight > lheight ? rheight : lheight);
        }
    }
};

#endif
