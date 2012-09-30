    /*
     * This code doesn't really do much, and abstraction is not built in.
     * Thus, I haven't bothered testing it exhaustively.
     */
    #include <iostream.h>
    #include "vector.h"

    class Polynomial
    {
        enum { MAX_DEGREE = 100 };
        friend int main( );   // So I can do a quick test.

      public:
        Polynomial( );
        void zeroPolynomial( );
        Polynomial operator+( const Polynomial & rhs ) const;
        Polynomial operator*( const Polynomial & rhs ) const;
        void print( ostream & out ) const;
  
      private:
        vector<int> coeffArray;
        int highPower;
    };


        int max( int a, int b )
        {
             return a > b ? a : b;
        }

        Polynomial::Polynomial( ) : coeffArray( MAX_DEGREE + 1 )
        {
           zeroPolynomial( );
        }

        void Polynomial::zeroPolynomial( )
        {
            for( int i = 0; i <= MAX_DEGREE; i++ )
                coeffArray[ i ] = 0;
            highPower = 0;
        }

        Polynomial Polynomial::operator+( const Polynomial & rhs ) const
        {
            Polynomial sum;

            sum.highPower = max( highPower, rhs.highPower );
            for( int i = sum.highPower; i >= 0; i-- )
                sum.coeffArray[ i ] = coeffArray[ i ] + rhs.coeffArray[ i ];
            return sum;
        }

        Polynomial Polynomial::operator*( const Polynomial & rhs ) const
        {
            Polynomial product;

            product.highPower = highPower + rhs.highPower;
            if( product.highPower > MAX_DEGREE )
                cerr << "operator* exceeded MAX_DEGREE" << endl;
            for( int i = 0; i <= highPower; i++ )
                for( int j = 0; j <= rhs.highPower; j++ )
                    product.coeffArray[ i + j ] +=
                            coeffArray[ i ] * rhs.coeffArray[ j ];
            return product;
        }

        void Polynomial::print( ostream & out ) const
        {
            for( int i = highPower; i > 0; i-- )
                out << coeffArray[ i ] << "x^" << i << " + ";
            out << coeffArray[ 0 ] << endl;
        }

        ostream & operator<<( ostream & out, const Polynomial & rhs )
        {
            rhs.print( out );
            return out;
        }

        int main( )
        {
            Polynomial p;
            Polynomial q;

            p.highPower = 1; p.coeffArray[ 0 ] = 1; p.coeffArray[ 1 ] = 1;

            q = p + p;
            p = q * q;
            q = p + p;

            cout << q << endl;
            return 0;
        }