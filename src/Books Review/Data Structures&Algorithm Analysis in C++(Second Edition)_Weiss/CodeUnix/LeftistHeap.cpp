        #include "LeftistHeap.h"
        #include "dsexceptions.h"

        /**
         * Construct the leftist heap.
         */
        template <class Comparable>
        LeftistHeap<Comparable>::LeftistHeap( )
        {
            root = NULL;
        }

        /**
         * Copy constructor.
         */
        template <class Comparable>
        LeftistHeap<Comparable>::LeftistHeap( const LeftistHeap<Comparable> & rhs )
        {
            root = NULL;
            *this = rhs;
        }


        /**
         * Destruct the leftist heap.
         */
        template <class Comparable>
        LeftistHeap<Comparable>::~LeftistHeap( )
        {
            makeEmpty( );
        }

        /**
         * Merge rhs into the priority queue.
         * rhs becomes empty. rhs must be different from this.
         */
        template <class Comparable>
        void LeftistHeap<Comparable>::merge( LeftistHeap & rhs )
        {
            if( this == &rhs )    // Avoid aliasing problems
                return;
    
            root = merge( root, rhs.root );
            rhs.root = NULL;
        }

        /**
         * Internal method to merge two roots.
         * Deals with deviant cases and calls recursive merge1.
         */
        template <class Comparable>
        LeftistNode<Comparable> *
        LeftistHeap<Comparable>::merge( LeftistNode<Comparable> * h1,
                                        LeftistNode<Comparable> * h2 ) const
        {
            if( h1 == NULL )
                return h2;
            if( h2 == NULL )
                return h1;
            if( h1->element < h2->element )
                return merge1( h1, h2 );
            else
                return merge1( h2, h1 );
        }

        /**
         * Internal method to merge two roots.
         * Assumes trees are not empty, and h1's root contains smallest item.
         */
        template <class Comparable>
        LeftistNode<Comparable> *
        LeftistHeap<Comparable>::merge1( LeftistNode<Comparable> * h1,
                                         LeftistNode<Comparable> * h2 ) const
        {
            if( h1->left == NULL )   // Single node
                h1->left = h2;       // Other fields in h1 already accurate
            else
            {
                h1->right = merge( h1->right, h2 );
                if( h1->left->npl < h1->right->npl )
                    swapChildren( h1 );
                h1->npl = h1->right->npl + 1;
            }
            return h1;
        }

        /**
         * Swaps t's two children.
         */
        template <class Comparable>
        void LeftistHeap<Comparable>::swapChildren( LeftistNode<Comparable> * t ) const
        {
            LeftistNode<Comparable> *tmp = t->left;
            t->left = t->right;
            t->right = tmp;
        }

        /**
         * Insert item x into the priority queue, maintaining heap order.
         */
        template <class Comparable>
        void LeftistHeap<Comparable>::insert( const Comparable & x )
        {
            root = merge( new LeftistNode<Comparable>( x ), root );
        }

        /**
         * Find the smallest item in the priority queue.
         * Return the smallest item, or throw Underflow if empty.
         */
        template <class Comparable>
        const Comparable & LeftistHeap<Comparable>::findMin( ) const
        {
            if( isEmpty( ) )
                throw Underflow( );
            return root->element;
        }

        /**
         * Remove the smallest item from the priority queue.
         * Throws Underflow if empty.
         */
        template <class Comparable>
        void LeftistHeap<Comparable>::deleteMin( )
        {
            if( isEmpty( ) )
                throw Underflow( );

            LeftistNode<Comparable> *oldRoot = root;
            root = merge( root->left, root->right );
            delete oldRoot;
        }

        /**
         * Remove the smallest item from the priority queue.
         * Pass back the smallest item, or throw Underflow if empty.
         */
        template <class Comparable>
        void LeftistHeap<Comparable>::deleteMin( Comparable & minItem )
        {
            minItem = findMin( );
            deleteMin( );
        }

        /**
         * Test if the priority queue is logically empty.
         * Returns true if empty, false otherwise.
         */
        template <class Comparable>
        bool LeftistHeap<Comparable>::isEmpty( ) const
        {
            return root == NULL;
        }

        /**
         * Test if the priority queue is logically full.
         * Returns false in this implementation.
         */
        template <class Comparable>
        bool LeftistHeap<Comparable>::isFull( ) const
        {
            return false;
        }

        /**
         * Make the priority queue logically empty.
         */
        template <class Comparable>
        void LeftistHeap<Comparable>::makeEmpty( )
        {
            reclaimMemory( root );
            root = NULL;
        }

        /**
         * Deep copy.
         */
        template <class Comparable>
        const LeftistHeap<Comparable> &
        LeftistHeap<Comparable>::
        operator=( const LeftistHeap<Comparable> & rhs )
        {
            if( this != &rhs )
            {
                makeEmpty( );
                root = clone( rhs.root );
            }
            return *this;
        }

        /**
         * Internal method to make the tree empty.
         * WARNING: This is prone to running out of stack space;
         *          exercises suggest a solution.
         */
        template <class Comparable>
        void LeftistHeap<Comparable>::reclaimMemory( LeftistNode<Comparable> * t ) const
        {
            if( t != NULL )
            {
                reclaimMemory( t->left );
                reclaimMemory( t->right );
                delete t;
            }
        }

        /**
         * Internal method to clone subtree.
         * WARNING: This is prone to running out of stack space.
         *          exercises suggest a solution.
         */
        template <class Comparable>
        LeftistNode<Comparable> *
        LeftistHeap<Comparable>::clone( LeftistNode<Comparable> * t ) const
        {
            if( t == NULL )
                return NULL;
            else
                return new LeftistNode<Comparable>( t->element, clone( t->left ),
                                              clone( t->right ), t->npl );
        }
