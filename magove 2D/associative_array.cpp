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
	  this->keys_array = (string*) malloc (ALLOC_BY * sizeof(string));
	  this->values_array = (string*) malloc (ALLOC_BY * sizeof(string));
    }
  
 //--------------------------------------------------
  
   void c_associative_array::set_text(string identifier, string value)
   {
	  int i;

	  for(i=0; i<this->length; i++)
	  {
		  if(this->keys_array[i].compare(identifier) == 0)
		  {
			  values_array[i] = value;
			  return;
		  }
	  }

	  if(length % ALLOC_BY == 0)
	  {
		  keys_array = (string*) realloc (keys_array, (length + ALLOC_BY) * sizeof(string));
		  values_array = (string*) realloc (values_array, (length + ALLOC_BY) * sizeof(string));
	  }

	  keys_array[length] = identifier;
	  values_array[length] = value;
	  length++;

   }

 //--------------------------------------------------

  string c_associative_array::get_text(string identifier)
	  {

		  int i;
		  
		  for(i=0; i<this->length; i++)
		  {
			 if(this->keys_array[i].compare(identifier) == 0)
			 {
				return values_array[i];
			 }
		  }

		  return "";
	  }

//--------------------------------------------------