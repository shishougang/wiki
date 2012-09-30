        #ifndef AA_TREE_H_
        #define AA_TREE_H_

        #include "dsexceptions.h"
        #include <iostream.h>       // For NULL

        // AATree class
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
        class AATree;

        template <class Comparable>
        class AANode
        {
            Comparable element;
            AANode    *left;
            AANode    *right;
            int        level;

            AANode( ) : left( NULL ), right( NULL ), level( 1 ) { }
            AANode( const Comparable & e, AANode *lt, AANode *rt, int lv = 1 )
              : element( e ), left( lt ), right( rt ), level( lv ) { }

            friend class AATree<Comparable>;
        };

        template <class Comparable>
        class AATree
        {
          public:
            explicit AATree( const Comparable & notFound );
            AATree( const AATree & rhs );
            ~AATree( );

            const Comparable & findMin( ) const;
            const Comparable & findMax( ) const;
            const Comparable & find( const Comparable & x ) const;
            bool isEmpty( ) const;
            void printTree( ) const;

            void makeEmpty( );
            void insert( const Comparable & x );
            void remove( const Comparable & x );

            const AATree & operator=( const AATree & rhs );
          private:
            AANode<Comparable> *root;
            const Comparable ITEM_NOT_FOUND;
            AANode<Comparable> *nullNode;

              // Recursive routines
            void insert( const Comparable & x, AANode<Comparable> * & t );
            void remove( const Comparable & x, AANode<Comparable> * & t );
            void makeEmpty( AANode<Comparable> * & t );
            void printTree( AANode<Comparable> *t ) const;

              // Rotations
            void skew( AANode<Comparable> * & t ) const;
            void split( AANode<Comparable> * & t ) const;
            void rotateWithLeftChild( AANode<Comparable> * & t ) const;
            void rotateWithRightChild( AANode<Comparable> * & t ) const;
            AANode<Comparable> * clone( AANode<Comparable> * t ) const;
        };

        #include "AATree.cpp"
        #endif
