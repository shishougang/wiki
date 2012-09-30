        #ifndef PAIRING_HEAP_H_
        #define PAIRING_HEAP_H_

        #include <iostream.h>       // For NULL

        // Pairing heap class
        //
        // CONSTRUCTION: with no parameters
        //
        // ******************PUBLIC OPERATIONS*********************
        // PairNode & insert( x ) --> Insert x
        // deleteMin( minItem )   --> Remove (and optionally return) smallest item
        // Comparable findMin( )  --> Return smallest item
        // bool isEmpty( )        --> Return true if empty; else false
        // bool isFull( )         --> Return true if empty; else false
        // void makeEmpty( )      --> Remove all items
        // void decreaseKey( PairNode p, newVal )
        //                        --> Decrease value in node p
        // ******************ERRORS********************************
        // Throws Underflow as warranted


          // Node and forward declaration because g++ does
          // not understand nested classes.
        template <class Comparable>
        class PairingHeap;

        template <class Comparable>
        class PairNode
        {
            Comparable   element;
            PairNode    *leftChild;
            PairNode    *nextSibling;
            PairNode    *prev;

            PairNode( const Comparable & theElement ) : element( theElement ),
              leftChild( NULL ), nextSibling( NULL ), prev( NULL ) { }
            friend class PairingHeap<Comparable>;
        };

        template <class Comparable>
        class PairingHeap
        {
          public:
            PairingHeap( );
            PairingHeap( const PairingHeap & rhs );
            ~PairingHeap( );

            bool isEmpty( ) const;
            bool isFull( ) const;
            const Comparable & findMin( ) const;

            PairNode<Comparable> *insert( const Comparable & x );
            void deleteMin( );
            void deleteMin( Comparable & minItem );
            void makeEmpty( );
            void decreaseKey( PairNode<Comparable> *p, const Comparable & newVal );

            const PairingHeap & operator=( const PairingHeap & rhs );

          private:
            PairNode<Comparable> *root;

            void reclaimMemory( PairNode<Comparable> *t ) const;
            void compareAndLink( PairNode<Comparable> * & first, PairNode<Comparable> *second ) const;
            PairNode<Comparable> * combineSiblings( PairNode<Comparable> *firstSibling ) const;
            PairNode<Comparable> * clone( PairNode<Comparable> * t ) const;
        };

        #include "PairingHeap.cpp"
        #endif
