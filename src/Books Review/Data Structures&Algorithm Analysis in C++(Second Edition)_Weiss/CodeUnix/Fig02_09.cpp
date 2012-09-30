        #include <iostream.h>
        #include "vector.h"

        const int NOT_FOUND = -1;

/* START: Fig02_09.txt*/
        /**
         * Performs the standard binary search using two comparisons per level.
         * Returns index where item is found or -1 if not found
         */
        template <class Comparable>
        int binarySearch( const vector<Comparable> & a, const Comparable & x )
        {
/* 1*/      int low = 0, high = a.size( ) - 1;

/* 2*/      while( low <= high )
            {
/* 3*/          int mid = ( low + high ) / 2;

/* 4*/          if( a[ mid ] < x )
/* 5*/              low = mid + 1;
/* 6*/          else if( a[ mid ] > x )
/* 7*/              high = mid - 1;
                else
/* 8*/              return mid;   // Found
            }
/* 9*/      return NOT_FOUND;     // NOT_FOUND is defined as -1
        }
/* END */

        // Test program
        int main( )
        {
            const int SIZE = 8;
            vector<int> a( SIZE );

            for( int i = 0; i < SIZE; i++ )
                a[ i ] = i * 2;

            for( int j = 0; j < SIZE * 2; j++ )
                cout << "Found " << j << " at " << binarySearch( a, j ) << endl;
            return 0;
        }
