        #include <iostream.h>
    
        int f( int x )
        {
/* 1*/      if( x == 0 )
/* 2*/          return 0;
            else
/* 3*/          return 2 * f( x - 1 ) +  x * x;
        }

        int main( )
        {
            cout << "f(5) = " << f( 5 ) << endl;
            return 0;
        }
