        #include <iostream.h>
        #include "vector.h"

/* START: Fig02_05.txt */
        /**
         * Cubic maximum contiguous subsequence sum algorithm.
         */
        int maxSubSum1( const vector<int> & a )
        {
/* 1*/      int maxSum = 0;

/* 2*/      for( int i = 0; i < a.size( ); i++ )
/* 3*/          for( int j = i; j < a.size( ); j++ )
                {
/* 4*/              int thisSum = 0;

/* 5*/              for( int k = i; k <= j; k++ )
/* 6*/                  thisSum += a[ k ];

/* 7*/              if( thisSum > maxSum )
/* 8*/                  maxSum   = thisSum;
                }

/* 9*/      return maxSum;
        }
/* END */


/* START: Fig02_06.txt */
        /**
         * Quadratic maximum contiguous subsequence sum algorithm.
         */
        int maxSubSum2( const vector<int> & a )
        {
/* 1*/      int maxSum = 0;

/* 2*/      for( int i = 0; i < a.size( ); i++ )
            {
/* 3*/          int thisSum = 0;
/* 4*/          for( int j = i; j < a.size( ); j++ )
                {
/* 5*/              thisSum += a[ j ];

/* 6*/              if( thisSum > maxSum )
/* 7*/                  maxSum = thisSum;
                }
            }

/* 8*/      return maxSum;
        }
/* END */

        /**
         * Return maximum of three integers.
         */
        int max3( int a, int b, int c )
        {
            return a > b ? a > c ? a : c : b > c ? b : c;
        }

/* START: Fig02_07.txt */
        /**
         * Recursive maximum contiguous subsequence sum algorithm.
         * Finds maximum sum in subarray spanning a[left..right].
         * Does not attempt to maintain actual best sequence.
         */
        int maxSumRec( const vector<int> & a, int left, int right )
        {
/* 1*/      if( left == right )  // Base case
/* 2*/          if( a[ left ] > 0 )
/* 3*/              return a[ left ];
                else
/* 4*/              return 0;

/* 5*/      int center = ( left + right ) / 2;
/* 6*/      int maxLeftSum  = maxSumRec( a, left, center );
/* 7*/      int maxRightSum = maxSumRec( a, center + 1, right );

/* 8*/      int maxLeftBorderSum = 0, leftBorderSum = 0;
/* 9*/      for( int i = center; i >= left; i-- )
            {
/*10*/          leftBorderSum += a[ i ];
/*11*/          if( leftBorderSum > maxLeftBorderSum )
/*12*/              maxLeftBorderSum = leftBorderSum;
            }

/*13*/      int maxRightBorderSum = 0, rightBorderSum = 0;
/*14*/      for( int j = center + 1; j <= right; j++ )
            {
/*15*/          rightBorderSum += a[ j ];
/*16*/          if( rightBorderSum > maxRightBorderSum )
/*17*/              maxRightBorderSum = rightBorderSum;
            }

/*18*/      return max3( maxLeftSum, maxRightSum,
/*19*/                   maxLeftBorderSum + maxRightBorderSum );
        }

        /**
         * Driver for divide-and-conquer maximum contiguous
         * subsequence sum algorithm.
         */
        int maxSubSum3( const vector<int> & a )
        {
            return maxSumRec( a, 0, a.size( ) - 1 );
        }
/* END */


/* START: Fig02_08.txt */
        /**
         * Linear-time maximum contiguous subsequence sum algorithm.
         */
        int maxSubSum4( const vector<int> & a )
        {
/* 1*/      int maxSum = 0, thisSum = 0;

/* 2*/      for( int j = 0; j < a.size( ); j++ )
            {
/* 3*/          thisSum += a[ j ];

/* 4*/          if( thisSum > maxSum )
/* 5*/              maxSum = thisSum;
/* 6*/          else if( thisSum < 0 )
/* 7*/              thisSum = 0;
            }

/* 8*/      return maxSum;
        }
/* END */

        /**
         * Simple test program.
         */
        int main( )
        {
            vector<int> a( 8 );
            a[ 0 ] = 4; a[ 1 ] = -3; a[ 2 ] = 5; a[ 3 ] = -2;
            a[ 4 ] = -1; a[ 5 ] = 2; a[ 6 ] = 6; a[ 7 ] = -2;
            int maxSum;

            maxSum = maxSubSum1( a );
            cout << "Max sum is " <<  maxSum << endl;
            maxSum = maxSubSum2( a );
            cout << "Max sum is " <<  maxSum << endl;
            maxSum = maxSubSum3( a );
            cout << "Max sum is " <<  maxSum << endl;
            maxSum = maxSubSum4( a );
            cout << "Max sum is " <<  maxSum << endl;

            return 0;
        }
