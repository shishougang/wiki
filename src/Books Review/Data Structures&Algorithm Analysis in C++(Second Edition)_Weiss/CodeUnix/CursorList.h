        #ifndef CursorList_H
        #define CursorList_H

#define List CursorList

        #include "vector.h"
        #include "dsexceptions.h"

        // LinkedList class using a cursor implementation
        //
        // CONSTRUCTION: with no initializer
        // Access is via LinkedListItr class
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
        class ListItr;     // Incomplete declaration.

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

          public:
            struct CursorNode
            {
                CursorNode( ) : next( 0 ) { }

              private:
                CursorNode( const Object & theElement, int n )
                  : element( theElement ), next( n ) { }

                Object element;
                int    next;

                friend class List<Object>;
                friend class ListItr<Object>;
            };

            const List & operator=( const List & rhs );

          private:
            int header;

            static vector<CursorNode> cursorSpace;

            static void initializeCursorSpace( );
            static int alloc( );
            static void free( int p );

            friend class ListItr<Object>;
        };


        // ListItr class; maintains "current position"
        //
        // CONSTRUCTION: Package friendly only, with an int
        //
        // ******************PUBLIC OPERATIONS*********************
        // bool isPastEnd( )      --> True if at valid position in list
        // void advance( )        --> Advance (if not already null)
        // Object retrieve        --> Return item in current position

        template <class Object>
        class ListItr
        {
          public:
            ListItr( ) : current( 0 ) { }
            bool isPastEnd( ) const
              { return current == 0; }
            void advance( )
              { if( !isPastEnd( ) ) current = List<Object>::cursorSpace[ current ].next; }
            const Object & retrieve( ) const
              { if( isPastEnd( ) ) throw BadIterator( );
                return List<Object>::cursorSpace[ current ].element; }

          private:
            int current;       // Current position
            friend class List<Object>;

            ListItr( int theNode )
              : current( theNode ) { }
        };

        #include "CursorList.cpp"
        #endif
