        #include <iostream.h>
        #include "matrix.h"

/* START: Fig10_53.txt */
        const int NOT_A_VERTEX = -1;

        /**
         * Compute all-shortest paths.
         * a[ ][ ]contains the adjacency matrix with
         * a[ i ][ i ] presumed to be zero.
         * d[ ] contains the values of the shortest path.
         * Vertices are numbered starting at 0; all arrays
         * have equal dimension. A negative cycle exists if
         * d[ i ][ i ] is set to a negative value.
         * Actual path can be computed using path[ ][ ].
         * NOT_A_VERTEX is -1
         */
        void allPairs( const matrix<int> & a,
                       matrix<int> & d, matrix<int> & path ) 
        {
            int n = a.numrows( );

            // Initialize d and path
/* 1*/      for( int i = 0; i < n; i++ )
/* 2*/          for( int j = 0; j < n; j++ )
                {
/* 3*/              d[ i ][ j ] = a[ i ][ j ];
/* 4*/              path[ i ][ j ] = NOT_A_VERTEX;
                }

/* 5*/      for( int k = 0; k < n; k++ )
                // Consider each vertex as an intermediate
/* 6*/          for( int i = 0; i < n; i++ )
/* 7*/              for( int j = 0; j < n; j++ )
/* 8*/                  if( d[ i ][ k ] + d[ k ][ j ] < d[ i ][ j ] )
                        {
                            // Update shortest path
/* 9*/                      d[ i ][ j ] = d[ i ][ k ] + d[ k ][ j ];
/*10*/                      path[ i ][ j ] = k;
                        }
        }
/* END */

        int main( )
        {
            matrix<int> a( 4, 4 );
            a[ 0 ][0 ] = 0; a[ 0 ][ 1 ] = 2; a[ 0 ][ 2 ] = -2; a[ 0 ][ 3 ] = 2;
            a[ 1 ][ 0 ] = 1000; a[ 1 ][ 1 ] = 0; a[ 1 ][ 2 ] = -3; a[ 1 ][ 3 ] = 1000;
            a[ 2 ][ 0 ] = 4; a[ 2 ][ 1 ] = 1000; a[ 2 ][ 2 ] = 0; a[ 2 ][ 3 ] = 1000;
            a[ 3 ][ 0 ] = 1000; a[ 3 ][ 1 ] = -2; a[ 3 ][ 2 ] = 3; a[ 3 ][ 3 ] = 0;

            matrix<int> d( 4, 4 );
            matrix<int> path( 4, 4 );

            allPairs( a, d, path );
            int i;
            for( i = 0; i < d.numrows( ); i++ )
            {
                for( int j = 0; j < d.numcols( ); j++ )
                    cout << d[ i ][ j ] << "    " ;
                cout << endl;
            }
            for( i = 0; i < path.numrows( ); i++ )
            {
                for( int j = 0; j < path.numcols( ); j++ )
                    cout << path[ i ][ j ] << "    " ;
                cout << endl;
            }

            return 0;
        }
