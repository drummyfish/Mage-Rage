#ifndef LOCAL_TEXTS_H
#define LOCAL_TEXTS_H

/**
 * Local texts class header file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include <string>
using namespace std;

class c_local_texts
  {
    /**
	* This class provides an interface to loading
	* local texts for game (that means different
	* languages texts). It can load them from a
	* file and provide access to them.
	*/

    public:
      c_local_texts();
	    /**
	      Class constructor, initialises new object.
	    */

	  ~c_local_texts();
	    /**
		  Class destructor, frees all it's memory.
		*/

	  bool load_from_file(string file_name);
	    /**
	      Loads the texts from given file. The file
		  contains texts separated by newlines,
		  each line in format: identifier:text

		  @param file_name path to the file
		  @return true if the file was loaded
		    succesfully, false otherwise
	    */

	  string get_text(string identifier);
	    /**
          Returns text with given identifier.		  
		
		  @param identifier identifier of the
		    text to be returned
		  @return text with given identifier
		*/
  };

#endif