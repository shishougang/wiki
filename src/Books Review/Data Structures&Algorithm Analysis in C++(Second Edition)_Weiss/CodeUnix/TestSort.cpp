        #include <iostream.h>
        #include "Sort.h"
        #include "vector.h"
        #include "Random.h"


        void checkSort( const vector<int> & a )
        {
            for( int i = 0; i < a.size( ); i++ )
                if( a[ i ] != i )
                    cout << "Error at " << i << endl;
            cout << "Finished checksort" << endl;
        }


        void permute( vector<int> & a )
        {
            static Random r;

            for( int j = 1; j < a.size( ); j++ )
                swap( a[ j ], a[ r.randomInt( 0, j ) ] );
        }

        
        int main( )
        {
            const int NUM_ITEMS = 1000;

            vector<int> a( NUM_ITEMS );
            for( int i = 0; i < a.size( ); i++ )
                a[ i ] = i;

            for( int theSeed = 0; theSeed < 20; theSeed++ )
            {
                permute( a );
                insertionSort( a );
                checkSort( a );

                permute( a );
                heapsort( a );
                checkSort( a );

                permute( a );
                shellsort( a );
                checkSort( a );

                permute( a );
                mergeSort( a );
                checkSort( a );

                permute( a );
                quicksort( a );
                checkSort( a );

                permute( a );
                largeObjectSort( a );
                checkSort( a );

                permute( a );
                quickSelect( a, NUM_ITEMS / 2 );
                cout << a[ NUM_ITEMS / 2 - 1 ] << " " << NUM_ITEMS / 2 << endl;
            }

            return 0;
        }
