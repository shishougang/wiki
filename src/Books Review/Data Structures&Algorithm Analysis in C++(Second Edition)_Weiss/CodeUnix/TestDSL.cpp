        #include <iostream.h>
        #include "DSL.h"

            // Test program
        int main( )
        {
            const int ITEM_NOT_FOUND = 99999999;
            DSL<int> t( ITEM_NOT_FOUND );
            int NUMS = 3900;
            const int GAP  =   37;
            int i;

            cout << "Checking... (no more output means success)" << endl;

            for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
                t.insert( i );

            if( NUMS < 40 )
                t.printList( );
            if( t.findMin( ) != 1 || t.findMax( ) != NUMS - 1 )
                cout << "FindMin or FindMax error!" << endl;

            for( i = 1; i < NUMS; i++ )
                if( t.find( i ) != i )
                    cout << "Find error1!" << endl;
            if( t.find( 0 ) != ITEM_NOT_FOUND )
                cout << "ITEM_NOT_FOUND failed!" << endl;

            return 0;
        }
