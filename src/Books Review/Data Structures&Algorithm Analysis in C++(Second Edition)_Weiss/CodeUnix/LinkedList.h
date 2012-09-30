        #ifndef LinkedList_H
        #define LinkedList_H

        #include "dsexceptions.h"
        #include <iostream.h>    // For NULL

        // List class
        //
        // CONSTRUCTION: with no initializer
        // Access is via ListItr class
        //
        // ******************PUBLIC OPERATIONS*********************
        // boolean isEmpty( )     --> Return true if empty; else false
        // void makeEmpty( )      --> Remove all items
        // ListItr zeroth( )      --> Return position to prior to first
        // ListItr first( )       --> Return first position
        // void insert( x, p )    --> Insert x after current iterator position p
        // void remove( x )       --> Remove x
        // ListItr find( x )      --> Return position that views x
        // ListItr findPrevious( x )
        //                        --> Return position prior to x
        // ******************ERRORS********************************
        // No special errors

        template <class Object>
        class List;     // Incomplete declaration.

        template <class Object>
        class ListItr;     // Incomplete declaration.

        template <class Object>
        class ListNode
        {
            ListNode( const Object & theElement = Object( ), ListNode * n = NULL )
              : element( theElement ), next( n ) { }

            Object   element;
            ListNode *next;

            friend class List<Object>;
            friend class ListItr<Object>;
        };


        template <class Object>
        class List
        {
          public:
            List( );
            List( const List & rhs );
            ~List( );

            bool isEmpty( ) const;
            void makeEmpty( );
            ListItr<Object> zeroth( ) const;
            ListItr<Object> first( ) const;
            void insert( const Object & x, const ListItr<Object> & p );
            ListItr<Object> find( const Object & x ) const;
            ListItr<Object> findPrevious( const Object & x ) const;
            void remove( const Object & x );

            const List & operator=( const List & rhs );

          private:
            ListNode<Object> *header;
        };


        // ListItr class; maintains "current position"
        //
        // CONSTRUCTION: Package friendly only, with a ListNode
        //
        // ******************PUBLIC OPERATIONS*********************
        // bool isPastEnd( )      --> True if past end position in list
        // void advance( )        --> Advance (if not already null)
        // Object retrieve        --> Return item in current position

        template <class Object>
        class ListItr
        {
          public:
            ListItr( ) : current( NULL ) { }
            bool isPastEnd( ) const
              { return current == NULL; }
            void advance( )
              { if( !isPastEnd( ) ) current = current->next; }
            const Object & retrieve( ) const
              { if( isPastEnd( ) ) throw BadIterator( );
                return current->element; }

          private:
            ListNode<Object> *current;    // Current position

            ListItr( ListNode<Object> *theNode )
              : current( theNode ) { }

            friend class List<Object>; // Grant access to constructor
        };

        #include "LinkedList.cpp"
        #endif
