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
      t_object_type type;          /** type of the object */
	  int link_id;                 /** identifies link between objects so they affect each other */
	  t_object_state object_state; /** identifies object state (on/off, open/closed etc.) */
	  ALLEGRO_BITMAP *bitmaps[5];  /** bitmaps used to draw this object */
	  bool stepable;               /** true if this object can be stepped over */

    public:
	  c_map_object(t_object_type object_type);

	    /**
	      Class constructor, initialises new
		  map object.

		  @param object_type object type of the
		    new map object.
	    */

	  t_object_type get_type();

	    /**
	      Returns this object's type.

		  @return this object's type
	    */

	  void change_state(t_object_state object_state);

	    /**
		  Changes the object's state.

		  @param object_state new object state
		*/

	  virtual void draw(int x, int y, long int global_time);

	    /**
		  Draws the map at given position on the
		  screen.

		  @param x x position of the screen
		  @param y y position of the screen
		  @param global_time global time counter
		    which is needed for animations etc.
		*/

	  bool is_stepable();

	    /**
		  Checks whether this object can be
		  stepped over.

		  @return true if this object is
		    stepable, otherwise false
		*/

	  void use();

	    /**
		  This method is called when player uses
		  the object.
		*/
  };

#endif