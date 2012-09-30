        #include "StackLi.h"
        #include <iostream.h>

        /**
         * Construct the stack.
         */
        template <class Object>
        Stack<Object>::Stack( )
        {
            topOfStack = NULL;
        }

        /**
         * Copy constructor.
         */
        template <class Object>
        Stack<Object>::Stack( const Stack<Object> & rhs )
        {
            topOfStack = NULL;
            *this = rhs;
        }

        /**
         * Destructor.
         */
        template <class Object>
        Stack<Object>::~Stack( )
        {
            makeEmpty( );
        }

        /**
         * Test if the stack is logically full.
         * Return false always, in this implementation.
         */
        template <class Object>
        bool Stack<Object>::isFull( ) const
        {
            return false;
        }

        /**
         * Test if the stack is logically empty.
         * Return true if empty, false otherwise.
         */
        template <class Object>
        bool Stack<Object>::isEmpty( ) const
        {
            return topOfStack == NULL;
        }

        /**
         * Make the stack logically empty.
         */
        template <class Object>
        void Stack<Object>::makeEmpty( )
        {
            while( !isEmpty( ) )
                pop( );
        }

        /**
         * Get the most recently inserted item in the stack.
         * Return the most recently inserted item in the stack
         * or throw an exception if empty.
         */
        template <class Object>
        const Object & Stack<Object>::top( ) const
        {
            if( isEmpty( ) )
                throw Underflow( );
            return topOfStack->element;
        }

        /**
         * Remove the most recently inserted item from the stack.
         * Exception Underflow if the stack is empty.
         */
        template <class Object>
        void Stack<Object>::pop( )
        {
            if( isEmpty( ) )
                throw Underflow( );

            ListNode *oldTop = topOfStack;
            topOfStack = topOfStack->next;
            delete oldTop;
        }

        /**
         * Return and remove the most recently inserted item
         * from the stack.
         */
        template <class Object>
        Object Stack<Object>::topAndPop( )
        {
            Object topItem = top( );
            pop( );
            return topItem;
        }

        /**
         * Insert x into the stack.
         */
        template <class Object>
        void Stack<Object>::push( const Object & x )
        {
            topOfStack = new ListNode( x, topOfStack );
        }

        /**
         * Deep copy.
         */
        template <class Object>
        const Stack<Object> & Stack<Object>::
        operator=( const Stack<Object> & rhs )
        {
            if( this != &rhs )
            {
                makeEmpty( );
                if( rhs.isEmpty( ) )
                    return *this;

                ListNode *rptr = rhs.topOfStack;
                ListNode *ptr  = new ListNode( rptr->element );
                topOfStack = ptr;

                for( rptr = rptr->next; rptr != NULL; rptr = rptr->next )
                    ptr = ptr->next = new ListNode( rptr->element );
            }
            return *this;
        }
