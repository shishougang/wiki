        #include <iostream.h>
        class IntCell
        {
          public:
            explicit IntCell( int initialValue = 0 );

            IntCell( const IntCell & rhs );
            ~IntCell( );
            const IntCell & operator=( const IntCell & rhs );

            int read( ) const;
            void write( int x );
          private:
            int *storedValue;
        };

        IntCell::IntCell( int initialValue )
        {
            storedValue = new int( initialValue );
        }

        IntCell::IntCell( const IntCell & rhs )
        {
            storedValue = new int( *rhs.storedValue );
        }

        IntCell::~IntCell( )
        {
            delete storedValue;
        }

        const IntCell & IntCell::operator=( const IntCell & rhs )
        {
            if( this != &rhs )
                *storedValue = *rhs.storedValue;
            return *this;
        }

        int IntCell::read( ) const
        {
            return *storedValue;
        }

        void IntCell::write( int x )
        {
            *storedValue = x;
        }


        /*
         * Figure 1.15.
         */
        int f( )
        {
            IntCell a( 2 );
            IntCell b = a;
            IntCell c;

            c = b;
            a.write( 4 );
            cout << a.read( ) << endl << b.read( ) << endl << c.read( ) << endl;
            return 0;
        }


        int main( )
        {
            f( );
            return 0;
        }