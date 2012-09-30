        #include "BinomialQueue.h"
        #include "dsexceptions.h"

        static const int MAX_TREES = 14;

        /**
         * Construct the binomial queue.
         */
        template <class Comparable>
        BinomialQueue<Comparable>::BinomialQueue( ) : theTrees( MAX_TREES )
        {
            for( int i = 0; i < theTrees.size( ); i++ )
                theTrees[ i ] = NULL;
            currentSize = 0;
        }

        /**
         * Copy constructor is left as an exercise.
         */
        template <class Comparable>
        BinomialQueue<Comparable>::
        BinomialQueue( const BinomialQueue<Comparable> & rhs )
        {
            cout << "Copy constructor is unimplemented" << endl;
        }

        /**
         * Destroy the binomial queue.
         */
        template <class Comparable>
        BinomialQueue<Comparable>::~BinomialQueue( )
        {
            makeEmpty( );
        }

        /**
         * Merge rhs into the priority queue.
         * rhs becomes empty. rhs must be different from this.
         * Throw Overflow if result exceeds capacity.
         */
        template <class Comparable>
        void BinomialQueue<Comparable>::merge( BinomialQueue<Comparable> & rhs )
        {
            if( this == &rhs )    // Avoid aliasing problems
                return;

            if( currentSize + rhs.currentSize > capacity( ) )
                throw Overflow( );

            currentSize += rhs.currentSize;

            BinomialNode<Comparable> *carry = NULL;
            for( int i = 0, j = 1; j <= currentSize; i++, j *= 2 )
            {
                BinomialNode<Comparable> *t1 = theTrees[ i ];
                BinomialNode<Comparable> *t2 = rhs.theTrees[ i ];

                int whichCase = t1 == NULL ? 0 : 1;
                whichCase += t2 == NULL ? 0 : 2;
                whichCase += carry == NULL ? 0 : 4;

                switch( whichCase )
                {
                  case 0: /* No trees */
                  case 1: /* Only this */
                    break;
                  case 2: /* Only rhs */
                    theTrees[ i ] = t2;
                    rhs.theTrees[ i ] = NULL;
                    break;
                  case 4: /* Only carry */
                    theTrees[ i ] = carry;
                    carry = NULL;
                    break;
                  case 3: /* this and rhs */
                    carry = combineTrees( t1, t2 );
                    theTrees[ i ] = rhs.theTrees[ i ] = NULL;
                    break;
                  case 5: /* this and carry */
                    carry = combineTrees( t1, carry );
                    theTrees[ i ] = NULL;
                    break;
                  case 6: /* rhs and carry */
                    carry = combineTrees( t2, carry );
                    rhs.theTrees[ i ] = NULL;
                    break;
                  case 7: /* All three */
                    theTrees[ i ] = carry;
                    carry = combineTrees( t1, t2 );
                    rhs.theTrees[ i ] = NULL;
                    break;
                }
            }

            for( int k = 0; k < rhs.theTrees.size( ); k++ )
                rhs.theTrees[ k ] = NULL;
            rhs.currentSize = 0;
        }        

        /**
         * Return the result of merging equal-sized t1 and t2.
         */
        template <class Comparable>
        BinomialNode<Comparable> *
        BinomialQueue<Comparable>::combineTrees( BinomialNode<Comparable> *t1,
                                                 BinomialNode<Comparable> *t2 ) const
        {
            if( t2->element < t1->element )
                return combineTrees( t2, t1 );
            t2->nextSibling = t1->leftChild;
            t1->leftChild = t2;
            return t1;
        }

        /**
         * Insert item x into the priority queue, maintaining heap order.
         * This implementation is not optimized for O(1) performance.
         * Throw Overflow if capacity exceeded.
         */
        template <class Comparable>
        void BinomialQueue<Comparable>::insert( const Comparable & x )
        {
            BinomialQueue oneItem;
            oneItem.currentSize = 1;
            oneItem.theTrees[ 0 ] = new BinomialNode<Comparable>( x, NULL, NULL );

            merge( oneItem );
        }

        /**
         * Return the smallest item in the priority queue.
         * Throw Underflow if empty.
         */
        template <class Comparable>
        const Comparable & BinomialQueue<Comparable>::findMin( ) const
        {
            if( isEmpty( ) )
                throw Underflow( );

            return theTrees[ findMinIndex( ) ]->element;
        }

    
        /**
         * Find index of tree containing the smallest item in the priority queue.
         * The priority queue must not be empty.
         * Return the index of tree containing the smallest item.
         */
        template <class Comparable>
        int BinomialQueue<Comparable>::findMinIndex( ) const
        {
            int i;
            int minIndex;

            for( i = 0; theTrees[ i ] == NULL; i++ )
                ;

            for( minIndex = i; i < theTrees.size( ); i++ )
                if( theTrees[ i ] != NULL &&
                    theTrees[ i ]->element < theTrees[ minIndex ]->element )
                    minIndex = i;

            return minIndex;
        }

        /**
         * Remove the smallest item from the priority queue.
         * Throw Underflow if empty.
         */
        template <class Comparable>
        void BinomialQueue<Comparable>::deleteMin( )
        {
            Comparable x;
            deleteMin( x );
        }


        /**
         * Remove the smallest item from the priority queue, and
         * copy it into minItem.  Throw Underflow if empty.
         */
        template <class Comparable>
        void BinomialQueue<Comparable>::deleteMin( Comparable & minItem )
        {
            if( isEmpty( ) )
                throw Underflow( );

            int minIndex = findMinIndex( );
            minItem = theTrees[ minIndex ]->element;

            BinomialNode<Comparable> *oldRoot = theTrees[ minIndex ];
            BinomialNode<Comparable> *deletedTree = oldRoot->leftChild;
            delete oldRoot;

            BinomialQueue deletedQueue;
            deletedQueue.currentSize = ( 1 << minIndex ) - 1;
            for( int j = minIndex - 1; j >= 0; j-- )
            {
                deletedQueue.theTrees[ j ] = deletedTree;
                deletedTree = deletedTree->nextSibling;
                deletedQueue.theTrees[ j ]->nextSibling = NULL;
            }

            theTrees[ minIndex ] = NULL;
            currentSize -= deletedQueue.currentSize + 1;

            merge( deletedQueue );
        }

        /**
         * Test if the priority queue is logically empty.
         * Return true if empty, false otherwise.
         */
        template <class Comparable>
        bool BinomialQueue<Comparable>::isEmpty( ) const
        {
            return currentSize == 0;
        }

        /**
         * Test if the priority queue is logically full.
         * Return true if full, false otherwise.
         */
        template <class Comparable>
        bool BinomialQueue<Comparable>::isFull( ) const
        {
            return currentSize == capacity( );
        }

        /**
         * Make the priority queue logically empty.
         */
        template <class Comparable>
        void BinomialQueue<Comparable>::makeEmpty( )
        {
            currentSize = 0;
            for( int i = 0; i < theTrees.size( ); i++ )
                makeEmpty( theTrees[ i ] );
        }

        /**
         * Deep copy.
         */
        template <class Comparable>
        const BinomialQueue<Comparable> &
        BinomialQueue<Comparable>::
        operator=( const BinomialQueue<Comparable> & rhs )
        {
            if( this != &rhs )
            {
                makeEmpty( );
                theTrees.resize( rhs.theTrees.size( ) );  // Just in case
                for( int i = 0; i < rhs.theTrees.size( ); i++ )
                    theTrees[ i ] = clone( rhs.theTrees[ i ] );
                currentSize = rhs.currentSize;
            }
            return *this;
        }

        /**
         * Return the capacity.
         */
        template <class Comparable>
        int BinomialQueue<Comparable>::capacity( ) const
        {
            return ( 1 << theTrees.size( ) ) - 1;
        }

        /**
         * Make a binomial tree logically empty, and free memory.
         */
        template <class Comparable>
        void BinomialQueue<Comparable>::
        makeEmpty( BinomialNode<Comparable> * & t ) const
        {
            if( t != NULL )
            {
                makeEmpty( t->leftChild );
                makeEmpty( t->nextSibling );
                delete t;
                t = NULL;
            }
        }


        /**
         * Internal method to clone subtree.
         */
        template <class Comparable>
        BinomialNode<Comparable> *
        BinomialQueue<Comparable>::clone( BinomialNode<Comparable> * t ) const
        {
            if( t == NULL )
                return NULL;
            else
                return new BinomialNode<Comparable>( t->element,
                           clone( t->leftChild ), clone( t->nextSibling ) );
        }

