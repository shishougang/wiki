        #ifndef AVL_TREE_H_
        #define AVL_TREE_H_


          // Node and forward declaration because g++ does
          // not understand nested classes.
        template <class Comparable>
        class AvlTree;

        template <class Comparable>
        class AvlNode
        {
            Comparable element;
            AvlNode   *left;
            AvlNode   *right;
            int       height;

            AvlNode( const Comparable & theElement, AvlNode *lt, AvlNode *rt, int h = 0 )
              : element( theElement ), left( lt ), right( rt ), height( h ) { }
            friend class AvlTree<Comparable>;
        };

        #include "dsexceptions.h"
        #include <iostream.h>       // For NULL

        // AvlTree class
        //
        // CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x (unimplemented)
        // Comparable find( x )   --> Return item that matches x
        // Comparable findMin( )  --> Return smallest item
        // Comparable findMax( )  --> Return largest item
        // boolean isEmpty( )     --> Return true if empty; else false
        // void makeEmpty( )      --> Remove all items
        // void printTree( )      --> Print tree in sorted order

        template <class Comparable>
        class AvlTree
        {
          public:
            explicit AvlTree( const Comparable & notFound );
            AvlTree( const AvlTree & rhs );
            ~AvlTree( );

            const Comparable & findMin( ) const;
            const Comparable & findMax( ) const;
            const Comparable & find( const Comparable & x ) const;
            bool isEmpty( ) const;
            void printTree( ) const;

            void makeEmpty( );
            void insert( const Comparable & x );
            void remove( const Comparable & x );

            const AvlTree & operator=( const AvlTree & rhs );

          private:
            AvlNode<Comparable> *root;
            const Comparable ITEM_NOT_FOUND;

            const Comparable & elementAt( AvlNode<Comparable> *t ) const;

            void insert( const Comparable & x, AvlNode<Comparable> * & t ) const;
            AvlNode<Comparable> * findMin( AvlNode<Comparable> *t ) const;
            AvlNode<Comparable> * findMax( AvlNode<Comparable> *t ) const;
            AvlNode<Comparable> * find( const Comparable & x, AvlNode<Comparable> *t ) const;
            void makeEmpty( AvlNode<Comparable> * & t ) const;
            void printTree( AvlNode<Comparable> *t ) const;
            AvlNode<Comparable> * clone( AvlNode<Comparable> *t ) const;

                // Avl manipulations
            int height( AvlNode<Comparable> *t ) const;
            int max( int lhs, int rhs ) const;
            void rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const;
            void rotateWithRightChild( AvlNode<Comparable> * & k1 ) const;
            void doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const;
            void doubleWithRightChild( AvlNode<Comparable> * & k1 ) const;
        };

        #include "AvlTree.cpp"
        #endif
