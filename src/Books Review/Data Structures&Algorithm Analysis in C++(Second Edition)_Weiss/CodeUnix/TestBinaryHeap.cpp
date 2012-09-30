        #include <iostream.h>
        #include "BinaryHeap.h"
        #include "dsexceptions.h"

            // Test program
        int main( )
        {
            int numItems = 10000;
            BinaryHeap<int> h( numItems );
            int i = 37;
            int x;

            try
            {
                for( i = 37; i != 0; i = ( i + 37 ) % numItems )
                    h.insert( i );
                for( i = 1; i < numItems; i++ )
                {
                    h.deleteMin( x );
                    if( x != i )
                        cout << "Oops! " << i << endl;
                }
                for( i = 37; i != 0; i = ( i + 37 ) % numItems )
                    h.insert( i );
                h.insert( 0 );
                h.insert( i = 999999 );  // Should overflow
            }
            catch( Overflow )
              { cout << "Overflow (expected)! " << i  << endl; }

            return 0;
        }
