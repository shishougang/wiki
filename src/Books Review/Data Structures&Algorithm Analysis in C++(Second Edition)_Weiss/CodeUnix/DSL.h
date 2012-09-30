        #ifndef DSL_H_
        #define DSL_H_

        #include "dsexceptions.h"
        #include <iostream.h>       // For NULL

        // Deterministic skip list class class
        //
        // CONSTRUCTION: with INFINITY object that is
        //               also used to signal failed finds
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x (unimplemented)
        // Comparable find( x )   --> Return item that matches x
        // Comparable findMin( )  --> Return smallest item
        // Comparable findMax( )  --> Return largest item
        // boolean isEmpty( )     --> Return true if empty; else false
        // void makeEmpty( )      --> Remove all items
        // void printList( )      --> Print items in sorted order


          // Node and forward declaration because g++ does
          // not understand nested classes.
        template <class Comparable>
        class DSL;

        template <class Comparable>
        class SkipNode
        {
            Comparable element;
            SkipNode  *right;
            SkipNode  *down;

            SkipNode( const Comparable & theElement = Comparable( ),
                               SkipNode *rt = NULL, SkipNode *dt = NULL )
              : element( theElement ), right( rt ), down( dt ) { }

            friend class DSL<Comparable>;
        };


        template <class Comparable>
        class DSL
        {
          public:
            explicit DSL( const Comparable & inf );
            DSL( const DSL & rhs );
            ~DSL( );

            const Comparable & findMin( ) const;
            const Comparable & findMax( ) const;
            const Comparable & find( const Comparable & x ) const;
            bool isEmpty( ) const;
            void printList( ) const;

            void makeEmpty( );
            void insert( const Comparable & x );
            void remove( const Comparable & x );

            const DSL & operator=( const DSL & rhs );
          private:
            const Comparable INFINITY;
            SkipNode<Comparable> *header;  // The list
            SkipNode<Comparable> *bottom;
            SkipNode<Comparable> *tail;

            const Comparable & elementAt( SkipNode<Comparable> * t ) const;

                // Usual recursive stuff
            void reclaimMemory( SkipNode<Comparable> *t ) const;
        };

        #include "DSL.cpp"
        #endif
