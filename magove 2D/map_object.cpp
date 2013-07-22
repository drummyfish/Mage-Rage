/**
 * Map object class implementation file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "map_object.h"

//---------------------------------------------------

c_map_object::c_map_object(t_object_type object_type)
  {
	int i;

	this->type = object_type;

	for (i = 0; i < 5; i++)
      this->bitmaps[i] = NULL;

	switch (this->type)
	  {
	    case OBJECT_CRATE:
		  this->bitmaps[0] = al_load_bitmap("resources/object_crate.png");
		  break;

		case OBJECT_TREE:
		  this->bitmaps[0] = al_load_bitmap("resources/object_tree.png");
		  break;
	  }
  }

//---------------------------------------------------

t_object_type c_map_object::get_type()
  {
	return this->type;
  }

//---------------------------------------------------

void c_map_object::draw(int x, int y, long int global_time)
  {
	switch (this->type)
	  {
	    case OBJECT_CRATE:
		  al_draw_bitmap(this->bitmaps[0],x,y - 27,0);
		  break;

		case OBJECT_TREE:
		  al_draw_bitmap(this->bitmaps[0],x,y - 27,0);
		  break;
	  }
  }

//---------------------------------------------------