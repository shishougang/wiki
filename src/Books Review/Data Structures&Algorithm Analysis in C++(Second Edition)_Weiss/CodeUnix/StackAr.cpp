        #include "StackAr.h"

        /**
         * Construct the stack.
         */
        template <class Object>
        Stack<Object>::Stack( int capacity ) : theArray( capacity )
        {
            topOfStack = -1;
        }

        /**
         * Test if the stack is logically empty.
         * Return true if empty, false otherwise.
         */
        template <class Object>
        bool Stack<Object>::isEmpty( ) const
        {
            return topOfStack == -1;
        }

        /**
         * Test if the stack is logically full.
         * Return true if full, false otherwise.
         */
        template <class Object>
        bool Stack<Object>::isFull( ) const
        {
            return topOfStack == theArray.size( ) - 1;
        }

        /**
         * Make the stack logically empty.
         */
        template <class Object>
        void Stack<Object>::makeEmpty( )
        {
            topOfStack = -1;
        }

        /**
         * Get the most recently inserted item in the stack.
         * Does not alter the stack.
         * Return the most recently inserted item in the stack.
         * Exception Underflow if stack is already empty.
         */
        template <class Object>
        const Object & Stack<Object>::top( ) const
        {
            if( isEmpty( ) )
                throw Underflow( );
            return theArray[ topOfStack ];
        }

        /**
         * Remove the most recently inserted item from the stack.
         * Exception Underflow if stack is already empty.
         */
        template <class Object>
        void Stack<Object>::pop( )
        {
            if( isEmpty( ) )
                throw Underflow( );
            topOfStack--;
        }

        /**
         * Insert x into the stack, if not already full.
         * Exception Overflow if stack is already full.
         */
        template <class Object>
        void Stack<Object>::push( const Object & x )
        {
            if( isFull( ) )
                throw Overflow( );
            theArray[ ++topOfStack ] = x;
        }

        /**
         * Return and remove most recently inserted item from the stack.
         * Return most recently inserted item.
         * Exception Underflow if stack is already empty.
         */
        template <class Object>
        Object Stack<Object>::topAndPop( )
        {
            if( isEmpty( ) )
                throw Underflow( );
            return theArray[ topOfStack-- ];
        }
