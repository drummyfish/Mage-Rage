/**
 * Associative array class implementation.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "associative_array.h"

//--------------------------------------------------

  c_associative_array::c_associative_array()
    {
	  this->length = 0;
	  this->keys_array = NULL;
	  this->values_array = NULL;
    }

//--------------------------------------------------