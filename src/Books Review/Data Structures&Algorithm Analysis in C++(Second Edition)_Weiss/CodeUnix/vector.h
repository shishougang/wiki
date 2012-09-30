#ifndef VECTOR_H
#define VECTOR_H

#define vector Vector

class ArrayIndexOutOfBounds { };

template <class Object>
class vector
{
  public:
    explicit vector( int theSize = 0 ) : currentSize( theSize )
      { objects = new Object[ currentSize ]; }
    vector( const vector & rhs ) : objects( NULL )
      { operator=( rhs ); }
    ~vector( )
#ifndef WIN32
      { delete [ ] objects; }
#else
      { if( currentSize != 0 ) delete [ ] objects; }
#endif

    int size( ) const
      { return currentSize; }

    Object & operator[]( int index )
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= currentSize )
            throw ArrayIndexOutOfBounds( );
                                                     #endif
        return objects[ index ];
    }

    const Object & operator[]( int index ) const
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= currentSize )
            throw ArrayIndexOutOfBounds( );
                                                     #endif
        return objects[ index ];
    }


    const vector & operator = ( const vector & rhs );
    void resize( int newSize );
  private:
    int currentSize;
    Object * objects;
};

#include "vector.cpp"
#endif


