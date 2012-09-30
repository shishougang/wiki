        #ifndef SPLAY_TREE_H_
        #define SPLAY_TREE_H_

        #include "dsexceptions.h"
        #include <iostream.h>       // For NULL

        // SplayTree class
        //
        // CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x
        // Comparable find( x )   --> Return item that matches x
        // Comparable findMin( )  --> Return smallest item
        // Comparable findMax( )  --> Return largest item
        // boolean isEmpty( )     --> Return true if empty; else false
        // void makeEmpty( )      --> Remove all items
        // void printTree( )      --> Print tree in sorted order


          // Node and forward declaration because g++ does
          // not understand nested classes.
        template <class Comparable>
        class SplayTree;

        template <class Comparable>
        class BinaryNode
        {
            Comparable  element;
            BinaryNode *left;
            BinaryNode *right;

            BinaryNode( ) : left( NULL ), right( NULL ) { }
            BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
              : element( theElement ), left( lt ), right( rt ) { }

            friend class SplayTree<Comparable>;
        };


        template <class Comparable>
        class SplayTree
        {
          public:
            explicit SplayTree( const Comparable & notFound );
            SplayTree( const SplayTree & rhs );
            ~SplayTree( );

            const Comparable & findMin( );
            const Comparable & findMax( );
            const Comparable & find( const Comparable & x );
            bool isEmpty( ) const;
            void printTree( ) const;

            void makeEmpty( );
            void insert( const Comparable & x );
            void remove( const Comparable & x );

            const SplayTree & operator=( const SplayTree & rhs );

          private:
            BinaryNode<Comparable> *root;
            BinaryNode<Comparable> *nullNode;
            const Comparable ITEM_NOT_FOUND;

            const Comparable & elementAt( BinaryNode<Comparable> *t ) const;

            void reclaimMemory( BinaryNode<Comparable> * t ) const;
            void printTree( BinaryNode<Comparable> *t ) const;
            BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;

                // Tree manipulations
            void rotateWithLeftChild( BinaryNode<Comparable> * & k2 ) const;
            void rotateWithRightChild( BinaryNode<Comparable> * & k1 ) const;
            void splay( const Comparable & x, BinaryNode<Comparable> * & t ) const;
        };

        #include "SplayTree.cpp"
        #endif
