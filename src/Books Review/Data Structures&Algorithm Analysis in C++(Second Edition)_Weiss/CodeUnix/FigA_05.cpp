        #include <iostream>
        #include <list>
        #include "dsexceptions.h"
        using namespace std;

        template <class Object>
        class Queue
        {
          public:
            bool isEmpty( ) const;
            const Object & getFront( ) const;
            void makeEmpty( );
            Object dequeue( );
            void enqueue( const Object & x );

          private:
            list<Object>   theList;
        };

        template <class Object>
        bool Queue<Object>::isEmpty( ) const
        {
            return theList.empty( );
        }

        template <class Object>
        const Object & Queue<Object>::getFront( ) const
        {
            if( isEmpty( ) )
                throw Underflow( );
            return theList.front( );
        }

        template <class Object>
        void Queue<Object>::makeEmpty( )
        {
            while( !isEmpty( ) )
                dequeue( );
        }

        template <class Object>
        Object Queue<Object>::dequeue( )
        {
            Object frontItem = getFront( );
            theList.pop_front( );
            return frontItem;
        }

        template <class Object>
        void Queue<Object>::enqueue( const Object & x )
        {
            theList.push_back( x );
        }


        int main( )
        {
            Queue<int> q;

            for( int j = 0; j < 5; j++ )
            {
                for( int i = 0; i < 5; i++ )
                    q.enqueue( i );
        
                while( !q.isEmpty( ) )
                    cout << q.dequeue( ) << endl;
            }

            return 0;
        } 