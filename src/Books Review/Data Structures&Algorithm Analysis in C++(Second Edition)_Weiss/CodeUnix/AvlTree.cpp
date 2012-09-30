    #include "AvlTree.h"
    #include <iostream.h>

    /**
     * Implements an unbalanced Avl search tree.
     * Note that all "matching" is based on the compares method.
     * @author Mark Allen Weiss
     */
        /**
         * Construct the tree.
         */
        template <class Comparable>
        AvlTree<Comparable>::AvlTree( const Comparable & notFound ) :
          ITEM_NOT_FOUND( notFound ), root( NULL )
        {
        }

        /**
         * Copy constructor.
         */
        template <class Comparable>
        AvlTree<Comparable>::AvlTree( const AvlTree<Comparable> & rhs ) :
          ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ), root( NULL )
        {
           *this = rhs;
        }

        /**
         * Destructor for the tree.
         */
        template <class Comparable>
        AvlTree<Comparable>::~AvlTree( )
        {
            makeEmpty( );
        }

        /**
         * Insert x into the tree; duplicates are ignored.
         */
        template <class Comparable>
        void AvlTree<Comparable>::insert( const Comparable & x )
        {
            insert( x, root );
        }

        /**
         * Remove x from the tree. Nothing is done if x is not found.
         */
        template <class Comparable>
        void AvlTree<Comparable>::remove( const Comparable & x )
        {
            cout << "Sorry, remove unimplemented; " << x <<
                 " still present" << endl;
        }

        /**
         * Find the smallest item in the tree.
         * Return smallest item or ITEM_NOT_FOUND if empty.
         */
        template <class Comparable>
        const Comparable & AvlTree<Comparable>::findMin( ) const
        {
            return elementAt( findMin( root ) );
        }

        /**
         * Find the largest item in the tree.
         * Return the largest item of ITEM_NOT_FOUND if empty.
         */
        template <class Comparable>
        const Comparable & AvlTree<Comparable>::findMax( ) const
        {
            return elementAt( findMax( root ) );
        }

        /**
         * Find item x in the tree.
         * Return the matching item or ITEM_NOT_FOUND if not found.
         */
        template <class Comparable>
        const Comparable & AvlTree<Comparable>::
                                 find( const Comparable & x ) const
        {
            return elementAt( find( x, root ) );
        }

        /**
         * Make the tree logically empty.
         */
        template <class Comparable>
        void AvlTree<Comparable>::makeEmpty( )
        {
            makeEmpty( root );
        }

        /**
         * Test if the tree is logically empty.
         * Return true if empty, false otherwise.
         */
        template <class Comparable>
        bool AvlTree<Comparable>::isEmpty( ) const
        {
            return root == NULL;
        }

        /**
         * Print the tree contents in sorted order.
         */
        template <class Comparable>
        void AvlTree<Comparable>::printTree( ) const
        {
            if( isEmpty( ) )
                cout << "Empty tree" << endl;
            else
                printTree( root );
        }

        /**
         * Deep copy.
         */
        template <class Comparable>
        const AvlTree<Comparable> &
        AvlTree<Comparable>::
        operator=( const AvlTree<Comparable> & rhs )
        {
            if( this != &rhs )
            {
                makeEmpty( );
                root = clone( rhs.root );
            }
            return *this;
        }

        /**
         * Internal method to get element field in node t.
         * Return the element field or ITEM_NOT_FOUND if t is NULL.
         */
        template <class Comparable>
        const Comparable & AvlTree<Comparable>::elementAt( AvlNode<Comparable> *t ) const
        {
            if( t == NULL )
               return ITEM_NOT_FOUND;
            else
               return t->element;
        }

        /**
         * Internal method to insert into a subtree.
         * x is the item to insert.
         * t is the node that roots the tree.
         */
        template <class Comparable>
        void AvlTree<Comparable>::insert( const Comparable & x, AvlNode<Comparable> * & t ) const
        {
            if( t == NULL )
                t = new AvlNode<Comparable>( x, NULL, NULL );
            else if( x < t->element )
            {
                insert( x, t->left );
                if( height( t->left ) - height( t->right ) == 2 )
                    if( x < t->left->element )
                        rotateWithLeftChild( t );
                    else
                        doubleWithLeftChild( t );
            }
            else if( t->element < x )
            {
                insert( x, t->right );
                if( height( t->right ) - height( t->left ) == 2 )
                    if( t->right->element < x )
                        rotateWithRightChild( t );
                    else
                        doubleWithRightChild( t );
            }
            else
                ;  // Duplicate; do nothing
            t->height = max( height( t->left ), height( t->right ) ) + 1;
        }

        /**
         * Internal method to find the smallest item in a subtree t.
         * Return node containing the smallest item.
         */
        template <class Comparable>
        AvlNode<Comparable> *
        AvlTree<Comparable>::findMin( AvlNode<Comparable> *t ) const
        {
            if( t == NULL)
                return t;

            while( t->left != NULL )
                t = t->left;
            return t;
        }

        /**
         * Internal method to find the largest item in a subtree t.
         * Return node containing the largest item.
         */
        template <class Comparable>
        AvlNode<Comparable> *
        AvlTree<Comparable>::findMax( AvlNode<Comparable> *t ) const
        {
            if( t == NULL )
                return t;

            while( t->right != NULL )
                t = t->right;
            return t;
        }

        /**
         * Internal method to find an item in a subtree.
         * x is item to search for.
         * t is the node that roots the tree.
         * Return node containing the matched item.
         */
        template <class Comparable>
        AvlNode<Comparable> *
        AvlTree<Comparable>::find( const Comparable & x, AvlNode<Comparable> *t ) const
        {
            while( t != NULL )
                if( x < t->element )
                    t = t->left;
                else if( t->element < x )
                    t = t->right;
                else
                    return t;    // Match

            return NULL;   // No match
        }

        /**
         * Internal method to make subtree empty.
         */
        template <class Comparable>
        void AvlTree<Comparable>::makeEmpty( AvlNode<Comparable> * & t ) const
        {
            if( t != NULL )
            {
                makeEmpty( t->left );
                makeEmpty( t->right );
                delete t;
            }
            t = NULL;
        }

        /**
         * Internal method to clone subtree.
         */
        template <class Comparable>
        AvlNode<Comparable> *
        AvlTree<Comparable>::clone( AvlNode<Comparable> * t ) const
        {
            if( t == NULL )
                return NULL;
            else
                return new AvlNode<Comparable>( t->element, clone( t->left ),
                                              clone( t->right ), t->height );
        }

        /**
         * Return the height of node t or -1 if NULL.
         */
        template <class Comparable>
        int AvlTree<Comparable>::height( AvlNode<Comparable> *t ) const
        {
            return t == NULL ? -1 : t->height;
        }

        /**
         * Return maximum of lhs and rhs.
         */
        template <class Comparable>
        int AvlTree<Comparable>::max( int lhs, int rhs ) const
        {
            return lhs > rhs ? lhs : rhs;
        }

        /**
         * Rotate binary tree node with left child.
         * For AVL trees, this is a single rotation for case 1.
         * Update heights, then set new root.
         */
        template <class Comparable>
        void AvlTree<Comparable>::rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const
        {
            AvlNode<Comparable> *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
            k1->height = max( height( k1->left ), k2->height ) + 1;
            k2 = k1;
        }

        /**
         * Rotate binary tree node with right child.
         * For AVL trees, this is a single rotation for case 4.
         * Update heights, then set new root.
         */
        template <class Comparable>
        void AvlTree<Comparable>::rotateWithRightChild( AvlNode<Comparable> * & k1 ) const
        {
            AvlNode<Comparable> *k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;
            k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
            k2->height = max( height( k2->right ), k1->height ) + 1;
            k1 = k2;
        }

        /**
         * Double rotate binary tree node: first left child.
         * with its right child; then node k3 with new left child.
         * For AVL trees, this is a double rotation for case 2.
         * Update heights, then set new root.
         */
        template <class Comparable>
        void AvlTree<Comparable>::doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const
        {
            rotateWithRightChild( k3->left );
            rotateWithLeftChild( k3 );
        }

        /**
         * Double rotate binary tree node: first right child.
         * with its left child; then node k1 with new right child.
         * For AVL trees, this is a double rotation for case 3.
         * Update heights, then set new root.
         */
        template <class Comparable>
        void AvlTree<Comparable>::doubleWithRightChild( AvlNode<Comparable> * & k1 ) const
        {
            rotateWithLeftChild( k1->right );
            rotateWithRightChild( k1 );
        }

        /**
         * Internal method to print a subtree in sorted order.
         * t points to the node that roots the tree.
         */
        template <class Comparable>
        void AvlTree<Comparable>::printTree( AvlNode<Comparable> *t ) const
        {
            if( t != NULL )
            {
                printTree( t->left );
                cout << t->element << endl;
                printTree( t->right );
            }
        }
