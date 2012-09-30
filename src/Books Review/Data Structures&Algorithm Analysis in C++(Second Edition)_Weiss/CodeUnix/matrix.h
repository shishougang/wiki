        #ifndef MATRIX_H
        #define MATRIX_H

        #include "vector.h"

        template <class Object>
        class matrix
        {
          public:
            matrix( int rows, int cols ) : array( rows )
            {
                for( int i = 0; i < rows; i++ )
                    array[ i ].resize( cols );
            }
            matrix( const matrix & rhs ) : array( rhs.array ) { }
            const vector<Object> & operator[]( int row ) const
              { return array[ row ]; }
            vector<Object> & operator[]( int row )
              { return array[ row ]; }
            int numrows( ) const
              { return array.size( ); }
            int numcols( ) const
              { return numrows( ) ? array[ 0 ].size( ) : 0; }
          private:
            vector< vector<Object> > array;
        };

        #endif


