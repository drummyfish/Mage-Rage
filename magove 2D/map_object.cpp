/**
 * Map object class implementation file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "map_object.h"

//-----------------------------------------------

c_map_object::c_map_object(t_object_type object_type)
  {
	int i;

	this->type = object_type;
	this->object_state = OBJECT_STATE_OFF;
	this->stepable = false;
	this->animation_frame = 0;
	this->playing_animation = ANIMATION_NONE;

	for (i = 0; i < 5; i++)
      this->bitmaps[i] = NULL;

	switch (this->type)
	  {
	    case OBJECT_LEVER:
          this->bitmaps[0] = al_load_bitmap("resources/object_lever_1.png");
		  this->bitmaps[1] = al_load_bitmap("resources/object_lever_2.png");
          this->bitmaps[2] = al_load_bitmap("resources/object_lever_3.png");
		  this->bitmaps[3] = al_load_bitmap("resources/object_lever_4.png");
		  this->bitmaps[4] = al_load_bitmap("resources/object_lever_5.png");
		  break;

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

//-----------------------------------------------

t_object_type c_map_object::get_type()
  {
	return this->type;
  }

//-----------------------------------------------

void c_map_object::draw(int x, int y, long int global_time)
  {
	int help_x, help_y;

	help_x = 0;
	help_y = 0;
	
	switch (this->type)
	  {
	    case OBJECT_LEVER:
		  if (this->playing_animation == ANIMATION_NONE)
			if (this->object_state == OBJECT_STATE_OFF)
			  al_draw_bitmap(this->bitmaps[0],x,y - 27,0);
			else
			  al_draw_bitmap(this->bitmaps[4],x,y - 27,0);
		  break;

	    default:
          al_draw_bitmap(this->bitmaps[0],x,y - 27,0);
		  break;
	  }
  }

//-----------------------------------------------

void c_map_object::change_state(t_object_state object_state)
  {
	this->object_state = object_state;
  }

//-----------------------------------------------

bool c_map_object::is_stepable()
  {
	return this->stepable;
  }

//-----------------------------------------------

void c_map_object::use()
  {
	switch(this->type)
	  {
	    case OBJECT_LEVER:
		  if (this->object_state == OBJECT_STATE_OFF)
			this->object_state = OBJECT_STATE_ON;
		  else
            this->object_state = OBJECT_STATE_OFF;

		default:
		  break;
	  }
  }

//-----------------------------------------------