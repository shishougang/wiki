        #include "MemoryCell.h"

        /**
         * Construct the MemoryCell with initialValue
         */
        template <class Object>
        MemoryCell<Object>::MemoryCell( const Object & initialValue )
          : storedValue( initialValue )
        {
        }

        /**
         * Return the stored value.
         */
        template <class Object>
        const Object & MemoryCell<Object>::read( ) const
        {
            return storedValue;
        }

        /**
         * Store x.
         */
        template <class Object>
        void MemoryCell<Object>::write( const Object & x )
        {
            storedValue = x;
        }

