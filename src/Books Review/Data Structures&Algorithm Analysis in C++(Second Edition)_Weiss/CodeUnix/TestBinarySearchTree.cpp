        #include <iostream.h>
        #include "BinarySearchTree.h"

            // Test program
        int main( )
        {
            const int ITEM_NOT_FOUND = -9999;
            BinarySearchTree<int> t( ITEM_NOT_FOUND );
            int NUMS = 4000;
            const int GAP  =   37;
            int i;

            cout << "Checking... (no more output means success)" << endl;

            for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
                t.insert( i );

            for( i = 1; i < NUMS; i+= 2 )
                t.remove( i );

            if( NUMS < 40 )
                t.printTree( );
            if( t.findMin( ) != 2 || t.findMax( ) != NUMS - 2 )
                cout << "FindMin or FindMax error!" << endl;

            for( i = 2; i < NUMS; i+=2 )
                if( t.find( i ) != i )
                    cout << "Find error1!" << endl;

            for( i = 1; i < NUMS; i+=2 )
            {
                if( t.find( i ) != ITEM_NOT_FOUND )
                    cout << "Find error2!" << endl;
            }

            BinarySearchTree<int> t2( ITEM_NOT_FOUND );
            t2 = t;

            for( i = 2; i < NUMS; i+=2 )
                if( t2.find( i ) != i )
                    cout << "Find error1!" << endl;

            for( i = 1; i < NUMS; i+=2 )
            {
                if( t2.find( i ) != ITEM_NOT_FOUND )
                    cout << "Find error2!" << endl;
            }


            return 0;
    }
