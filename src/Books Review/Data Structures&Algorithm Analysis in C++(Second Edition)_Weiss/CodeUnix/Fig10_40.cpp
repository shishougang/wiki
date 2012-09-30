        #include <iostream.h>

/* START: Fig10_40.txt */
        /**
         * Compute Fibonacci numbers as described in Chapter 1.
         */
        int fib( int n )
        {
            if( n <= 1 )
                return 1;
            else
                return fib( n - 1 ) + fib( n - 2 );
        }
/* END */

/* START: Fig10_41.txt */
        /**
         * Compute Fibonacci numbers as described in Chapter 1.
         */
        int fibonacci( int n )
        {
            if( n <= 1 )
                return 1;

            int last = 1;
            int nextToLast = 1;
            int answer = 1;
            for( int i = 2; i <= n; i++ )
            {
                answer = last + nextToLast;
                nextToLast = last;
                last = answer;
            }
            return answer;
        }
/* END */

        int main( )
        {
            cout << "fib( 7 ) = " << fib( 7 ) << endl;
            cout << "fibonacci( 7 ) = " << fibonacci( 7 ) << endl;
            return 0;
        }
