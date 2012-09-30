        #ifndef BINOMIAL_QUEUE_H_
        #define BINOMIAL_QUEUE_H_

        #include <iostream.h>
        #include "vector.h"

        // Binomial queue class
        //
        // CONSTRUCTION: with no parameters
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // deleteMin( )           --> Return and remove smallest item
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
        class BinomialQueue;

        template <class Comparable>
        class BinomialNode
        {
            Comparable    element;
            BinomialNode *leftChild;
            BinomialNode *nextSibling;

            BinomialNode( const Comparable & theElement, 
                          BinomialNode *lt, BinomialNode *rt )
              : element( theElement ), leftChild( lt ), nextSibling( rt ) { }
            friend class BinomialQueue<Comparable>;
        };

        template <class Comparable>
        class BinomialQueue
        {
          public:
            BinomialQueue( );
            BinomialQueue( const BinomialQueue & rhs );
            ~BinomialQueue( );

            bool isEmpty( ) const;
            bool isFull( ) const;
            const Comparable & findMin( ) const;

            void insert( const Comparable & x );
            void deleteMin( );
            void deleteMin( Comparable & minItem );
            void makeEmpty( );
            void merge( BinomialQueue & rhs );

            const BinomialQueue & operator=( const BinomialQueue & rhs );

          private:
            int currentSize;                // Number of items in the priority queue
            vector<BinomialNode<Comparable> *> theTrees;   // An array of tree roots

            int findMinIndex( ) const;
            int capacity( ) const;
            BinomialNode<Comparable> * combineTrees( BinomialNode<Comparable> *t1,
                                              BinomialNode<Comparable> *t2 ) const;
            void makeEmpty( BinomialNode<Comparable> * & t ) const;
            BinomialNode<Comparable> * clone( BinomialNode<Comparable> * t ) const;
        };

        #include "BinomialQueue.cpp"
        #endif
