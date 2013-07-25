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
	  bool input;                  /** true if this object is input (ie. lever, button, etc.) */
	  t_object_state object_state; /** identifies object state (on/off, open/closed etc.) */
	  ALLEGRO_BITMAP *bitmaps[5];  /** bitmaps used to draw this object */
	  bool stepable;               /** true if this object can be stepped over */
	  c_map_object **controlling;  /** array of pointers to objects which are affected by this object */
	  int number_of_controlled;    /** length of controlled array */

    public:
	  c_map_object(t_object_type object_type, int link_id);

	    /**
	      Class constructor, initialises new
		  map object.

		  @param object_type object type of the
		    new map object.
		  @param link_id a number identifying
		    the connection between objects,
			objects with same link id will
			affect each other
	    */

	  void update_controlled_objects(long int global_time);
	    /**
		  Updated states of objects that are
		  controlled by this object.

		  @param global_time global time counter
		*/

	  void add_controlled_objects(int number_of_objects, c_map_object *objects[]);

	    /**
		  Registers objects that will be
		  controlled by this object.

		  @param number_of_objects length of
		    objects array
		  @param objects array of pointers to
		    objects that will be controlled
		*/

	  t_object_type get_type();

	    /**
	      Returns this object's type.

		  @return this object's type
	    */

	  int get_link_id();

	    /**
		  Returns the object's link id.

		  @return object link id
		*/

	  t_object_state get_state();

	    /**
		  Returns the object's state.

		  @return object state
		*/

	  bool is_input();
	    
	    /**
		  Checks if this object is an input
		  object.

		  @return true, if this object is
		    input, otherwise false
		*/

	  void change_state(t_object_state object_state);

	    /**
		  Changes the object's state.

		  @param object_state new object state
		*/

	  void switch_state(long int global_time);

	    /**
		  Switches states of the object between
		  on and off.

		  @param global_time global time counter
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

	  void use(long int global_time);

	    /**
		  This method is called when player uses
		  the object.

		  @param global_time global time count
		    for animations
		*/

	  void update_animation_period();

	    /**
		  Depending on current animation sets
		  the animation period attribute.
		*/
  };

#endif