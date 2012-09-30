        #ifndef QUEUEAR_H
        #define QUEUEAR_H

        #include "vector.h"
        #include "dsexceptions.h"

        // Queue class -- array implementation
        //
        // CONSTRUCTION: with or without a capacity; default is 10
        //
        // ******************PUBLIC OPERATIONS*********************
        // void enqueue( x )      --> Insert x
        // void dequeue( )        --> Return and remove least recently inserted item
        // Object getFront( )     --> Return least recently inserted item
        // bool isEmpty( )        --> Return true if empty; else false
        // bool isFull( )         --> Return true if full; else false
        // void makeEmpty( )      --> Remove all items
        // ******************ERRORS********************************
        // Overflow and Underflow thrown as needed

        template <class Object>
        class Queue
        {
          public:
            explicit Queue( int capacity = 10 );

            bool isEmpty( ) const;
            bool isFull( ) const;
            const Object & getFront( ) const;

            void makeEmpty( );
            Object dequeue( );
            void enqueue( const Object & x );

          private:
            vector<Object> theArray;
            int            currentSize;
            int            front;
            int            back;

            void increment( int & x );
        };

        #include "QueueAr.cpp"
        #endif
