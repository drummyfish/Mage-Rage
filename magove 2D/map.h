#ifndef MAP
#define MAP

/**
 * Map class header file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "general.h"
#include "graphic_object.h"

class c_map: c_graphics_object
  {
	/**
	  This class represents a game map. It is
	  able to draw and manage it.
	*/

    private:
	  t_environment environment;    /** map environment */
	  t_map_square squares[][];     /** map squares */

    public:

      c_map();

	    /** 
	      Class constructor, initialises new map
	  	  object.
	    */
  }

#endif