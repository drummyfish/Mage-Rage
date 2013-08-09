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
      t_object_type type;                  /** type of the object */
	  int link_id;                         /** identifies link between objects so they affect each other */
	  int link_id2;                        /** another link, negative number means it's not used */
	  bool input;                          /** true if this object is input (ie. lever, button, etc.) */
	  t_object_state object_state;         /** identifies object state (on/off, open/closed etc.) */
	  ALLEGRO_BITMAP *bitmaps[5];          /** bitmaps used to draw this object */
	  bool stepable;                       /** true if this object can be stepped over */
	  c_map_object **controlling;          /** array of pointers to objects which are affected by this object */
	  int number_of_controlled;            /** length of controlled array */
	  string sign_text;                    /** text - only for sign objects */

    public:
	  c_map_object(t_object_type object_type, int link_id, int link_id2, long int *global_time);

	    /**
	      Class constructor, initialises new
		  map object.

		  @param object_type object type of the
		    new map object.
		  @param link_id a number identifying
		    the connection between objects,
			objects with same link id will
			affect each other
		  @param link_id2 another link id,
		    negative number means this will not
			be used
		  @param global_time reference to a 
		    global time counter variable which
			is needed for animations
	    */

	  void update_controlled_objects();

	    /**
		  Updated states of objects that are
		  controlled by this object.
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

	  int get_link_id2();

	    /**
		  Returns the object's secondary
		    link id.

		  @return object secondary link id
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

	  void set_state(t_object_state object_state);

	    /**
		  Sets the object's state (but does
		  nothing else like updating controlled
		  objects etc.).

		  @param object_state new object state
		*/

	  void switch_state();

	    /**
		  Switches states of the object between
		  on and off.
		*/

	  virtual void draw(int x, int y);

	    /**
		  Draws the map at given position on the
		  screen.

		  @param x x position of the screen
		  @param y y position of the screen
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

	  void update_animation_period();

	    /**
		  Depending on current animation sets
		  the animation period attribute.
		*/

	  bool compare_link_ids(c_map_object *another_object);

	    /**
		  Checks if this map object and another
		  map object are linked via their link
		  ids.

		  @param another_object object to be
		    compared to this object by link
			ids
		  @return true if this object is linked
		    with another_object, otherwise
			false
		*/

	  c_map_object *get_controlled_object(int index);

	    /**
		  Returns one of objects controlled
		  by this object.

		  @param index index of the controlled
		    objects to be returned
          @return pointer to controlled object
		    at given index, if the index
			exceeds length of object list,
			NULL is returned
		*/

	  void set_sign_text(string text);

	    /**
		  Sets the text for sign map object.

		  @param text text to be set
		*/

	  string get_sign_text();

	    /**
		  Returns text associated with sign
		  map object.

		  @return sign text
		*/
  };

#endif