        #include <iostream.h>

        bool isEven( int n )
        {
            return n % 2 == 0;
        }

/* START: Fig02_11.txt*/
        long pow( long x, int n )
        {
/* 1*/      if( n == 0 )
/* 2*/          return 1;
/* 3*/      if( n == 1 )
/* 4*/          return x;
/* 5*/      if( isEven( n ) )
/* 6*/          return pow( x * x, n / 2 );
            else
/* 7*/          return pow( x * x, n / 2 ) * x;
        }
/* END */

        // Test program
        int main( )
        {
            cout << "2^21 = " << pow( 2, 21 ) << endl;
            cout << "2^30 = " << pow( 2, 30 ) << endl;
            return 0;
        }
