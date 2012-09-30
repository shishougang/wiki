        #ifndef TREAP_H_
        #define TREAP_H_

        #include <limits.h>
        #include "Random.h"
        #include "dsexceptions.h"
        #include <iostream.h>       // For NULL

        // Treap class
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
        class Treap;

        template <class Comparable>
        class TreapNode
        {
            Comparable element;
            TreapNode *left;
            TreapNode *right;
            int        priority;

            TreapNode( ) : left( NULL ), right( NULL ), priority( INT_MAX ) { }
            TreapNode( const Comparable & theElement, TreapNode *lt, TreapNode *rt, int pr )
              : element( theElement ), left( lt ), right( rt ), priority( pr )
              { }

            friend class Treap<Comparable>;
        };

        template <class Comparable>
        class Treap
        {
          public:
            explicit Treap( const Comparable & notFound );
            Treap( const Treap & rhs );
            ~Treap( );

            const Comparable & findMin( ) const;
            const Comparable & findMax( ) const;
            const Comparable & find( const Comparable & x ) const;
            bool isEmpty( ) const;
            void printTree( ) const;

            void makeEmpty( );
            void insert( const Comparable & x );
            void remove( const Comparable & x );

            const Treap & operator=( const Treap & rhs );

          private:
            TreapNode<Comparable> *root;
            const Comparable ITEM_NOT_FOUND;
            TreapNode<Comparable> *nullNode;
            Random randomNums;

              // Recursive routines
            void insert( const Comparable & x, TreapNode<Comparable> * & t );
            void remove( const Comparable & x, TreapNode<Comparable> * & t );
            void makeEmpty( TreapNode<Comparable> * & t );
            void printTree( TreapNode<Comparable> *t ) const;

              // Rotations
            void rotateWithLeftChild( TreapNode<Comparable> * & t ) const;
            void rotateWithRightChild( TreapNode<Comparable> * & t ) const;
            TreapNode<Comparable> * clone( TreapNode<Comparable> * t ) const;
        };

        #include "Treap.cpp"
        #endif
