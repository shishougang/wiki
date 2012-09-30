        #include <iostream.h>

/* START: Fig02_10.txt*/
        long gcd( long m, long n )
        {
/* 1*/      while( n != 0 )
            {
/* 2*/          long rem = m % n;
/* 3*/          m = n;
/* 4*/          n = rem;
            }
/* 5*/      return m;
        }
/* END */

        // Test program
        int main( )
        {
            cout << "gcd( 45, 35 ) = " << gcd( 45, 35 ) << endl;
            cout << "gcd( 1989, 1590 ) = " << gcd( 1989, 1590 ) << endl;
            return 0;
        }
