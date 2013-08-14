#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H

/**
 * Associative array class header file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "general.h"
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

class c_associative_array
  {

    protected:
	  vector<string> *keys;      /** list of keys */
	  vector<string> *values;    /** list of values */

    public:
      c_associative_array();

	    /**
	      Class constructor, initialises a new
		  object.
	    */

	  ~c_associative_array();

	    /**
		  Class destructor, frees all it's memory.
		*/

	  bool load_from_file(string file_name);

	    /**
	      Loads the array from given file. The
		  file contains texts separated by
		  newlines, each line in format:
		  identifier:text

		  @param file_name path to the file
		  @return true if the file was loaded
		    succesfully, false otherwise
	    */

	  bool save_to_file(string file_name);

	  	/**
	      Saves the array to given file.

		  @param file_name path to the file
		  @return true if the file was saved
		    succesfully, false otherwise
	    */

	  string get_text(string identifier);

	    /**
          Returns text with given identifier.		  
		
		  @param identifier identifier of the
		    text to be returned
		  @return text with given identifier,
			or (if the text was not found)
			returns an empty string
		*/

	  void set_text(string identifier, string value);

	    /**
          Sets the value for given identifier.
		  If the identifier already exists,
		  it's current value will be
		  overwritten, otherwise a new key is
		  created with this value.
		
		  @param identifier identifier of the
		    text to be returned
		  @param value value for the identifier
		*/

	  void delete_text(string identifier);
	    
	    /**
		  Deletes given item. If the item
		  doesn't exist, nothing happens.

		  @param identifier identifier of the
		    item to be deleted
		*/
  };

#endif