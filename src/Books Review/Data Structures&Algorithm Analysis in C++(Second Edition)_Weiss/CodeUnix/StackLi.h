        #ifndef STACKLI_H
        #define STACKLI_H

        #include "dsexceptions.h"
        #include <iostream.h>       // For NULL

        // Stack class -- linked list implementation
        //
        // CONSTRUCTION: with no parameters
        //
        // ******************PUBLIC OPERATIONS*********************
        // void push( x )         --> Insert x
        // void pop( )            --> Remove most recently inserted item
        // Object top( )          --> Return most recently inserted item
        // Object topAndPop( )    --> Return and remove most recently inserted item
        // bool isEmpty( )        --> Return true if empty; else false
        // bool isFull( )         --> Return true if full; else false
        // void makeEmpty( )      --> Remove all items
        // ******************ERRORS********************************
        // Overflow and Underflow thrown as needed

        template <class Object>
        class Stack
        {
          public:
            Stack( );
            Stack( const Stack & rhs );
            ~Stack( );

            bool isEmpty( ) const;
            bool isFull( ) const;
            const Object & top( ) const;

            void makeEmpty( );
            void pop( );
            void push( const Object & x );
            Object topAndPop( );

            const Stack & operator=( const Stack & rhs );

          private:
            struct ListNode
            {
                Object   element;
                ListNode *next;

                ListNode( const Object & theElement, ListNode * n = NULL )
                  : element( theElement ), next( n ) { }
            };

            ListNode *topOfStack;
        };

        #include "StackLi.cpp"
        #endif

