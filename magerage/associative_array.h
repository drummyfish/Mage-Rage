#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H

/**
 * Associative array class header file.
 *
 * Copyright 2013 Miloslav Číž
 *
 * This file is part of Mage Rage.
 *
 * Mage Rage is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Mage Rage is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar. If not, see <http://www.gnu.org/licenses/>.
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