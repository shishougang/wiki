        #include <iostream.h>

        void printDigit( int n )
        {
            cout << n;
        }

/* START: Fig01_04.txt */
        void printOut( int n )  // Print nonnegative n
        {
            if( n >= 10 )
                printOut( n / 10 );
            printDigit( n % 10 );
        }
/* END */

        int main(  )
        {
            printOut( 1369 );
            cout << endl;
            return 0;
        }
