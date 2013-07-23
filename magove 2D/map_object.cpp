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

	this->stepable = false;
	this->animation_frame = 0;
	this->playing_animation = ANIMATION_NONE;

	for (i = 0; i < 5; i++)
      this->bitmaps[i] = NULL;

	switch (this->type)
	  {
	    case OBJECT_CRATE:
		  this->bitmaps[0] = al_load_bitmap("resources/object_crate.png");
		  this->stepable = true;
		  break;

		case OBJECT_TREE:
		  this->bitmaps[0] = al_load_bitmap("resources/object_tree.png");
		  break;

		case OBJECT_STAIRS_NORTH:
		  this->stepable = true;
		  this->bitmaps[0] = al_load_bitmap("resources/object_stairs_north.png");
		  break;

		case OBJECT_STAIRS_EAST:
		  this->stepable = true;
		  this->bitmaps[0] = al_load_bitmap("resources/object_stairs_east.png");
		  break;

		case OBJECT_STAIRS_SOUTH:
		  this->stepable = true;
		  this->bitmaps[0] = al_load_bitmap("resources/object_stairs_south.png");
		  break;

		case OBJECT_STAIRS_WEST:
		  this->stepable = true;
		  this->bitmaps[0] = al_load_bitmap("resources/object_stairs_west.png");
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
	int help_x, help_y;

	help_x = 0;
	help_y = 0;
	
    al_draw_bitmap(this->bitmaps[0],x,y - 27,0);
  }

//---------------------------------------------------

bool c_map_object::is_stepable()
  {
	return this->stepable;
  }

//---------------------------------------------------