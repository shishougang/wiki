        #include "CursorList.h"

        /**
         * Routine to initialize the cursorSpace.
         */
        template <class Object>
        void List<Object>::initializeCursorSpace( )
        {
            static int cursorSpaceIsInitialized = false;

            if( !cursorSpaceIsInitialized )
            {
                cursorSpace.resize( 100 );
                for( int i = 0; i < cursorSpace.size( ); i++ )
                    cursorSpace[ i ].next = i + 1;
                cursorSpace[ cursorSpace.size( ) - 1 ].next = 0;
                cursorSpaceIsInitialized = true;
            }
        }

        /**
         * Allocate a CursorNode
         */
        template <class Object>
        int List<Object>::alloc( )
        {
            int p = cursorSpace[ 0 ].next;
            cursorSpace[ 0 ].next = cursorSpace[ p ].next;
            return p;
        }

        /**
         * Free a CursorNode
         */
        template <class Object>
        void List<Object>::free( int p )
        {
            cursorSpace[ p ].next = cursorSpace[ 0 ].next;
            cursorSpace[ 0 ].next = p;
        }


        /**
         * Construct the list
         */
        template <class Object>
        List<Object>::List( )
        {
            initializeCursorSpace( );
            header = alloc( );
            cursorSpace[ header ].next = 0;
        }

        /**
         * Copy constructor
         */
        template <class Object>
        List<Object>::List( const List<Object> & rhs )
        {
            initializeCursorSpace( );
            header = alloc( );
            cursorSpace[ header ].next = 0;
            *this = rhs;
        }

        /**
         * Destroy the list
         */
        template <class Object>
        List<Object>::~List( )
        {
            makeEmpty( );
            free( header );
        }

        /**
         * Test if the list is logically empty.
         * return true if empty, false otherwise.
         */
        template <class Object>
        bool List<Object>::isEmpty( ) const
        {
            return cursorSpace[ header ].next == 0;
        }

        /**
         * Make the list logically empty.
         */
        template <class Object>
        void List<Object>::makeEmpty( )
        {
            while( !isEmpty( ) )
                remove( first( ).retrieve( ) );
        }

        /**
         * Return an iterator representing the header node.
         */
        template <class Object>
        ListItr<Object> List<Object>::zeroth( ) const
        {
            return ListItr<Object>( header );
        }

        /**
         * Return an iterator representing the first node in the list.
         * This operation is valid for empty lists.
         */
        template <class Object>
        ListItr<Object> List<Object>::first( ) const
        {
            return ListItr<Object>( cursorSpace[ header ].next );
        }

        /**
         * Insert item x after p.
         */
        template <class Object>
        void List<Object>::insert( const Object & x, const ListItr<Object> & p )
        {
            if( p.current != 0 )
            {
                int pos = p.current;
                int tmp = alloc( );

                cursorSpace[ tmp ] = CursorNode( x, cursorSpace[ pos ].next );
                cursorSpace[ pos ].next = tmp;
            }
        }

        /**
         * Return iterator corresponding to the first node containing an item x.
         * Iterator isPastEnd if item is not found.
         */
        template <class Object>
        ListItr<Object> List<Object>::find( const Object & x ) const
        {
/* 1*/      int itr = cursorSpace[ header ].next;

/* 2*/      while( itr != 0 && cursorSpace[ itr ].element != x )
/* 3*/          itr = cursorSpace[ itr ].next;

/* 4*/      return ListItr<Object>( itr );
        }

        /**
         * Return iterator prior to the first node containing an item x.
         */
        template <class Object>
        ListItr<Object> List<Object>::findPrevious( const Object & x ) const
        {
/* 1*/      int itr = header;

/* 2*/      while( cursorSpace[ itr ].next != 0 &&
                   cursorSpace[ cursorSpace[ itr ].next ].element != x )
/* 3*/          itr = cursorSpace[ itr ].next;

/* 4*/      return ListItr<Object>( itr );
        }

        /**
         * Remove the first occurrence of an item x.
         */
        template <class Object>
        void List<Object>::remove( const Object & x )
        {
            ListItr<Object> p = findPrevious( x );
            int pos = p.current;

            if( cursorSpace[ pos ].next != 0 )
            {
                int tmp = cursorSpace[ pos ].next;
                cursorSpace[ pos ].next = cursorSpace[ tmp ].next;
                free ( tmp );
            }
        }


        /**
         * Deep copy of linked lists.
         */
        template <class Object>
        const List<Object> & List<Object>::operator=( const List<Object> & rhs )
        {
            ListItr<Object> ritr = rhs.first( );
            ListItr<Object> itr = zeroth( );

            if( this != &rhs )
            {
                makeEmpty( );
                for( ; !ritr.isPastEnd( ); ritr.advance( ), itr.advance( ) )
                    insert( ritr.retrieve( ), itr );
            }
            return *this;
        }


