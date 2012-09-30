        #include <iostream.h>
        #include "mystring.h"


        /**
         * A class for simulating a memory cell.
         */
        template <class Object>
        class MemoryCell
        {
          public:
            explicit MemoryCell( const Object & initialValue = Object( ) )
              : storedValue( initialValue ) { }
            const Object & read( ) const
              { return storedValue; }
            void write( const Object & x )
              { storedValue = x; }
          private:
            Object storedValue;
        };

        // OOPS: I forgot to put a + operator in the string class.
        // So it's here:

        string operator+( const string & lhs, const string & rhs )
        {
            string result = lhs;
            return result += rhs;
            
        }

        int main( )
        {
            MemoryCell<int>    m1;
            MemoryCell<string> m2( "hello" );

            m1.write( 37 );
            m2.write( m2.read( ) + " world" );
            cout << m1.read( ) << endl << m2.read( ) << endl;

            return 0;
        }
