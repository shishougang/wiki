        #include <iostream.h>
        #include "IntCell.h"

        int main( )
        {
            IntCell m;   // Or, IntCell m( 0 ); but not IntCell m( );

            m.write( 5 );
            cout << "Cell contents: " << m.read( ) << endl;

            return 0;
        }
