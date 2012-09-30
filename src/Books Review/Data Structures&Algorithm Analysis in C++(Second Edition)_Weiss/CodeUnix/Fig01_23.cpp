        #include <iostream.h>
        #include "vector.h"
        #include "mystring.h"

        class Employee
        {
          public:
            void setValue( const string & n, double s )
              { name = n; salary = s; }

            void print( ostream & out ) const
              { out << name << " (" << salary << ")"; }
            bool operator< ( const Employee & rhs ) const
              { return salary < rhs.salary; }

            // Other general accessors and mutators, not shown
          private:
            string name;
            double salary;
        };

          // Define an output operator for Employee
        ostream & operator<< ( ostream & out, const Employee & rhs )
        {
            rhs.print( out );
            return out;
        }

        /**
         * Return the maximum item in array a.
         * Assumes a.size( ) > 0.
         * Comparable objects must provide
         *   copy constructor, operator<, operator=
         */
        template <class Comparable>
        const Comparable & findMax( const vector<Comparable> & a )
        {
/* 1*/      int maxIndex = 0;

/* 2*/      for( int i = 1; i < a.size( ); i++ )
/* 3*/          if( a[ maxIndex ] < a[ i ] )
/* 4*/              maxIndex = i;
/* 5*/      return a[ maxIndex ];
        }

        int main( )
        {
            vector<Employee> v( 3 );

            v[0].setValue( "Bill Clinton", 200000.00 );
            v[1].setValue( "Bill Gates", 2000000000.00 );
            v[2].setValue( "Billy the Marlin", 60000.00 );
            cout << findMax( v ) << endl;

            return 0;
        }
