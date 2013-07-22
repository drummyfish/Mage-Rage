#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

/**
 * Map object class header file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "general.h"
#include "graphic_object.h"

class c_map_object: public c_graphic_object
  {
	/**
	  This class is a map object, such as a
	  tree or a lever.
	*/

    protected:
      t_object_type type;        /** type of the object */
	  int link_id;               /** identifies link between objects so they affect each other */
	  int object_state;          /** identifies object state (on/off, open/closed etc.) */

    public:
	  c_map_object(t_object_type object_type);

	  /**
	    Class constructor, initialises new
		map object.

		@param object_type object type of the
		  new map object.
	  */
  };

#endif