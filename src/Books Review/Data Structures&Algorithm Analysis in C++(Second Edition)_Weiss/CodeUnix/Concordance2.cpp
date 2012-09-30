#include <iostream.h>
#include <fstream.h>
#ifdef unix
    #include <strstream.h>
#else
    #include <strstrea.h>   // <strstream.h> on UNIX machines
#endif

#include "mystring.h"
#include "AvlTree.h"
#include "LinkedList.h"

struct WordEntry
{
    WordEntry( ) : word( "" ), lines( NULL )
      { }

    bool operator<( const WordEntry & rhs ) const
      { return word < rhs.word; }
    bool operator==( const WordEntry & rhs ) const
      { return word == rhs.word; }

    string       word;
    List<int>    *lines;
    ListItr<int> *listEnd;
};

ostream & operator<<( ostream & out, const WordEntry & rhs )
{
    out << rhs.word << ": ";

    if( rhs.lines != NULL && !rhs.lines->isEmpty( ) )
    {
        ListItr<int> itr = rhs.lines->first( );
        out << '\t' << itr.retrieve( );
        for( itr.advance( ); !itr.isPastEnd( ); itr.advance( ) )
            out << ", " << itr.retrieve( );
    }
    return out;
}

int main( int argc, char *argv[ ] )
{
    if( argc != 2 )
    {
        cerr << "Usage: " << argv[ 0 ] << " filename" << endl;
        return 1;
    }

    ifstream inFile( argv[ 1 ] );
    if( !inFile )
    {
        cerr << "Cannot open " << argv[ 1 ] << endl;
        return 1;
    }

    const WordEntry ITEM_NOT_FOUND;    // "" is the word member
    AvlTree<WordEntry> wordMap( ITEM_NOT_FOUND );
    string oneLine;
    WordEntry entry;

        // Read the words; add them to wordMap
    for( int lineNum = 1; getline( inFile, oneLine ); lineNum++ )
    {
        istrstream st( (char *) oneLine.c_str( ) );   // Deprecated form of string streams
        while( st >> entry.word )
        {
            const WordEntry & match = wordMap.find( entry );
            if( match == ITEM_NOT_FOUND )
            {
                entry.lines = new List<int>;
                entry.lines->insert( lineNum, entry.lines->zeroth( ) );
                entry.listEnd = new ListItr<int>( entry.lines->first( ) );
                wordMap.insert( entry );
            }
            else
            {
                match.lines->insert( lineNum, *match.listEnd );
                match.listEnd->advance( );
            }
        }
    }
	
    wordMap.printTree( );
    return 0;
}

