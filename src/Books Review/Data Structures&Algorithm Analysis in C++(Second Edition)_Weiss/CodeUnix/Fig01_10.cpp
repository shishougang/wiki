 
        #include <iostream.h>
        #include "vector.h"      // vector (our version, in Appendix B)
        #include "mystring.h"    // string (our version, in Appendix B)

        int main( )
        {
            vector<string> v( 5 );
            int itemsRead = 0;
            string x;

            while( cin >> x )
            {
                if( itemsRead == v.size( ) )
                    v.resize( v.size( ) * 2 );
                v[ itemsRead++ ] = x;
            }

            for( int i = itemsRead - 1; i >= 0; i-- )
                cout << v[ i ] << endl;
            return 0;
        }
