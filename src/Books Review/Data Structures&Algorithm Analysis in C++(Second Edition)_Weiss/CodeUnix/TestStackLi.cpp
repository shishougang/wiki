        #include "StackLi.h"
        #include <iostream.h>

        int main( )
        {
            Stack<int> s, s1;

            for( int i = 0; i < 10; i++ )
                s.push( i );
        
            s1 = s;

            cout << "s" << endl;
            while( !s.isEmpty( ) )
                cout << s.topAndPop( ) << endl;

            cout << endl << "s1" << endl;
            while( !s1.isEmpty( ) )
                cout << s1.topAndPop( ) << endl;

            return 0;
        } 