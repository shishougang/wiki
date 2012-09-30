        #include <iostream>
        #include <set>
        #include <string>
        using namespace std;

        // Print the contents of Container c
        template <class Container>
        void printCollection( const Container & c )
        {
            Container::const_iterator itr;
            for( itr = c.begin( ); itr != c.end( ); itr++ )
                cout << *itr << '\n';
        }

        int main( )
        {
            set<string, greater<string> > s;  // Use reverse order

            s.insert( "joe" );
            s.insert( "bob" );
            printCollection( s );   // Figure A.2

            return 0;
        }
