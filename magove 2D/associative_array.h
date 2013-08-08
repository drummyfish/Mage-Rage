#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H

/**
 * Associative array class header file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include <string>
using namespace std;
#define ALLOC_BY 64;

class c_associative_array
  {
    /**
	* This class provides an interface for an
	* associative array, which can be loaded and
	* saved to a file.
	*/

  protected: string *keys_array;
			 string *values_array;
			 int length;

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
		  @return text with given identifier
		*/

	  void set_text(string identifier, string value);

	    /**
          Sets the value for given identifier.
		  If the identifier already exists,
		  it's current walue will be
		  overwritten, otherwise a new key is
		  created with this value.
		
		  @param identifier identifier of the
		    text to be returned
		  @param value value for the identifier
		*/

	  void delete_item(string identifier);
	    
	    /**
		  Deletes given item. If the item
		  doesn't exist, nothing happens.

		  @param identifier identifier of the
		    item to be deleted
		*/
  };

#endif