#include <string.h>
#include "mystring.h"

string::string( const char * cstring )
{
    if( cstring == NULL )
        cstring = "";
    strLength = strlen( cstring );
    bufferLength = strLength + 1;
    buffer = new char[ bufferLength ];
    strcpy( buffer, cstring );
}

string::string( const string & str )
{
    strLength = str.length( );
    bufferLength = strLength + 1;
    buffer = new char[ bufferLength ];
    strcpy( buffer,str.buffer );
}

const string & string::operator=( const string & rhs )
{
    if( this != &rhs )
    {
        if( bufferLength < rhs.length( ) + 1 )
        {
            delete [ ] buffer;
            bufferLength = rhs.length( ) + 1;
            buffer = new char[ bufferLength ];
        }
        strLength = rhs.length( );
        strcpy( buffer, rhs.buffer );
    }
    return *this;
}

const string & string::operator+=( const string & rhs )
{
    if( this == &rhs )
    {
        string copy( rhs );
        return *this += copy;
    }

    int newLength = length( ) + rhs.length( );
    if( newLength >= bufferLength )
    {
        bufferLength = 2 * ( newLength + 1 );

        char *oldBuffer = buffer;
        buffer = new char[ bufferLength ];
        strcpy( buffer, oldBuffer );
        delete [ ] oldBuffer;
    }

    strcpy( buffer + length( ), rhs.buffer );
    strLength = newLength;
    return *this;
}

char & string::operator[ ]( int k )
{
    if( k < 0 || k >= strLength )
        throw StringIndexOutOfBounds( );
    return buffer[ k ];
}

char string::operator[ ]( int k ) const
{
    if( k < 0 || k >= strLength )
        throw StringIndexOutOfBounds( );
    return buffer[ k ];
}

ostream & operator<<( ostream & out, const string & str )
{
    return out << str.c_str();
}

istream & operator>>( istream & in, string & str )
{
    char buf[ string::MAX_LENGTH + 1 ];
    in >> buf;
    if( !in.fail( ) )
        str = buf;
    return in;
}

istream & getline( istream & in, string & str )
{
    char buf[ string::MAX_LENGTH + 1 ];
    in.getline( buf, string::MAX_LENGTH );
    if( !in.fail( ) )
        str = buf;
    return in;
}

bool operator==( const string & lhs, const string & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) == 0;
}

bool operator!=( const string & lhs, const string & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) != 0;
}

bool operator<( const string & lhs, const string & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) < 0;
}

bool operator<=( const string & lhs, const string & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) <= 0;
}

bool operator>( const string & lhs, const string & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) > 0;
}

bool operator>=( const string & lhs, const string & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) >= 0;
}
