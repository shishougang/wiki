        #include "Random.h"
        #include <iostream.h>

            // Test program
        int main( )
        {
            Random r( 1 );

            for( int i = 0; i < 20; i++ )
                cout << r.randomInt( ) << endl;

            return 0;
        }