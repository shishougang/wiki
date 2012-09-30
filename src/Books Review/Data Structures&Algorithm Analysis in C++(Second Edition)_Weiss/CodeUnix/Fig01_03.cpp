        #include <iostream.h>

        int bad( int n )
        {
/* 1*/      if( n == 0 )
/* 2*/          return 0;
            else
/* 3*/          return bad( n / 3 + 1 ) + n - 1;
        }

        int main( )
        {
            cout << "bad is infinite recursion" << endl;
            return 0;
        }
