#include "string.cpp"

int main( )
{
    string a = "this";
    string b = "that";

    a += a;
    string c = a;
    c += "then";
    cout << (c>a) << " should be 1" << endl;

    string d;
    for( int i = 0; i < 300000; i++ )
        d += "a";
    cout << d.length( ) << "\n";

    cout << "Enter a string\n" ;
    string e;
    cin >> e;
    e += "";
    d = e;
    cout << d << endl;
    for( int j = 0; j < e.length( ); j++ )
        cout << d[ j ];
    cout << "\n";
    return 0;
}
    