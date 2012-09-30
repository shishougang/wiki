        #include <iostream.h>
        #include "mystring.h"
        #include "vector.h"
        #include "IntCell.h"
        // Figures 1.17 and 1.18, but with illegalities commented out


        /**
         * Return the maximum item in array a.
         * Assumes a.size( ) > 0.
         * Comparable objects must provide
         *   copy constructor, operator<, operator=
         */
        template <class Comparable>
        const Comparable & findMax( const vector<Comparable> & a )
        {
/* 1*/      int maxIndex = 0;

/* 2*/      for( int i = 1; i < a.size( ); i++ )
/* 3*/          if( a[ maxIndex ] < a[ i ] )
/* 4*/              maxIndex = i;
/* 5*/      return a[ maxIndex ];
        }

        int main( )
        {
            vector<int>     v1( 37 );
            vector<double>  v2( 40 );
            vector<string>  v3( 80 );
//          vector<IntCell> v4( 75 );

            // Additional code to fill in the vectors

            cout << findMax( v1 ) << endl;  // OK: Comparable = int
            cout << findMax( v2 ) << endl;  // OK: Comparable = double
            cout << findMax( v3 ) << endl;  // OK: Comparable = string
//          cout << findMax( v4 ) << endl;  // Illegal; operator< undefined

            return 0;
        };
