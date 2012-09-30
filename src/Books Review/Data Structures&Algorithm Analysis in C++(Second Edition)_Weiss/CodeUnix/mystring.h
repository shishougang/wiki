#ifndef MY_STRING_H_
#define MY_STRING_H_

#include <iostream.h>

/*
 * The next line is used because Codewarrior has a conflict with
 * the STL string. Make sure to put the #include of this file
 * AFTER all the system includes.
 */
#define string String

class StringIndexOutOfBounds { };

class string
{
  public:
    string( const char *cstring = "" );               // Constructor
    string( const string & str );                     // Copy constructor
    ~string( )                                        // Destructor
      { delete [ ] buffer; }

    const string & operator= ( const string & rhs );  // Copy
    const string & operator+=( const string & rhs );  // Append

    const char *c_str( ) const        // Return C-style string
      { return buffer; }
    int length( ) const               // Return string length
      { return strLength; }

    char   operator[]( int k ) const; // Accessor operator[]
    char & operator[]( int k );       // Mutator  operator[]

    enum { MAX_LENGTH = 1024 };  // Maximum length for input string

  private:
    char *buffer;                  // storage for characters
    int strLength;                 // length of string (# of characters)
    int bufferLength;              // capacity of buffer
};

ostream & operator<<( ostream & out, const string & str );    // Output
istream & operator>>( istream & in, string & str );           // Input
istream & getline( istream & in, string & str );              // Read line

bool operator==( const string & lhs, const string & rhs );    // Compare ==
bool operator!=( const string & lhs, const string & rhs );    // Compare !=
bool operator< ( const string & lhs, const string & rhs );    // Compare <
bool operator<=( const string & lhs, const string & rhs );    // Compare <=
bool operator> ( const string & lhs, const string & rhs );    // Compare >
bool operator>=( const string & lhs, const string & rhs );    // Compare >=

#endif
