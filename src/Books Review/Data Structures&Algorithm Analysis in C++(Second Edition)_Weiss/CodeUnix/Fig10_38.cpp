        #include <iostream.h>
        #include "matrix.h"
 
/* START: Fig10_38.txt */
        /**
         * Standard matrix multiplication.
         * Arrays start at 0.
         * Assumes a and b are square.
         */
        matrix<int> operator*( const matrix<int> & a, const matrix<int> & b )
        {
            int n = a.numrows( );
            matrix<int> c( n, n );

            int i;
            for( i = 0; i < n; i++ )    // Initialization
                for( int j = 0; j < n; j++ )
                    c[ i ][ j ] = 0;

            for( i = 0; i < n; i++ )
                for( int j = 0; j < n; j++ )
                    for( int k = 0; k < n; k++ )
                        c[ i ][ j ] += a[ i ][ k ] * b[ k ][ j ];

            return c;
        }
/* END */

        int main( )
        {
            matrix<int> a( 2, 2 );
            a[ 0 ][ 0 ] = 1; a[ 0 ][ 1 ] = 2;
            a[ 1 ][ 0 ] = 3; a[ 1 ][ 1 ] = 4;

            matrix<int> c = a * a;

            cout << c[ 0 ][ 0 ] << " " << c[ 0 ][ 1 ] << endl <<
                                c[ 1 ][ 0 ] << " " << c[ 1 ][ 1 ] << endl;

            return 0;
        }
