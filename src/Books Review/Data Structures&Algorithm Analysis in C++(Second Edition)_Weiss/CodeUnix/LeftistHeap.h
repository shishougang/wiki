        #ifndef BINARY_HEAP_H_
        #define BINARY_HEAP_H_

        #include <iostream.h>

        // Leftist heap class
        //
        // CONSTRUCTION: with no parameters
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // deleteMin( minItem )   --> Remove (and optionally return) smallest item
        // Comparable findMin( )  --> Return smallest item
        // bool isEmpty( )        --> Return true if empty; else false
        // bool isFull( )         --> Return true if full; else false
        // void makeEmpty( )      --> Remove all items
        // void merge( rhs )      --> Absorb rhs into this heap
        // ******************ERRORS********************************
        // Throws Underflow and Overflow as warranted


          // Node and forward declaration because g++ does
          // not understand nested classes.
        template <class Comparable>
        class LeftistHeap;

        template <class Comparable>
        class LeftistNode
        {
            Comparable   element;
            LeftistNode *left;
            LeftistNode *right;
            int          npl;

            LeftistNode( const Comparable & theElement, LeftistNode *lt = NULL,
                         LeftistNode *rt = NULL, int np = 0 )
              : element( theElement ), left( lt ), right( rt ), npl( np ) { }
            friend class LeftistHeap<Comparable>;
        };

        template <class Comparable>
        class LeftistHeap
        {
          public:
            LeftistHeap( );
            LeftistHeap( const LeftistHeap & rhs );
            ~LeftistHeap( );

            bool isEmpty( ) const;
            bool isFull( ) const;
            const Comparable & findMin( ) const;

            void insert( const Comparable & x );
            void deleteMin( );
            void deleteMin( Comparable & minItem );
            void makeEmpty( );
            void merge( LeftistHeap & rhs );

            const LeftistHeap & operator=( const LeftistHeap & rhs );

          private:
            LeftistNode<Comparable> *root;

            LeftistNode<Comparable> * merge( LeftistNode<Comparable> *h1,
                                             LeftistNode<Comparable> *h2 ) const;
            LeftistNode<Comparable> * merge1( LeftistNode<Comparable> *h1,
                                              LeftistNode<Comparable> *h2 ) const;
            void swapChildren( LeftistNode<Comparable> * t ) const;
            void reclaimMemory( LeftistNode<Comparable> * t ) const;
            LeftistNode<Comparable> * clone( LeftistNode<Comparable> *t ) const;
        };

        #include "LeftistHeap.cpp"
        #endif
