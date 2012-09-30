        #include <iostream.h>
        #include "MemoryCell.h"
        #include "mystring.h"


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
