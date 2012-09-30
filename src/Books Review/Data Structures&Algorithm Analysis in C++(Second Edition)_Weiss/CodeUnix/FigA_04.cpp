        #include <iostream>
        #include <vector>
        #include <algorithm>
        using namespace std;

        int main( )
        {
            vector<int> v;    // Initial size is 0
            int x;

            while( cin >> x )
                v.push_back( x );

            sort( v.begin( ), v.end( ) );

            for( int i = 0; i < v.size( ); i++ )
                cout << v[ i ] << endl;
            return 0;
        }
