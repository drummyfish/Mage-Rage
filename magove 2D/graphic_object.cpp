/**
 * Graphic object class implementation.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "graphic_object.h"

//--------------------------------------------------

void c_graphic_object::draw(int x, int y)
  {
  }

//--------------------------------------------------

void c_graphic_object::play_animation(int animation_id)
  {
	this->playing_animation = animation_id;
	this->animation_frame = 0;
	this->looping_animation = false;
  }

//--------------------------------------------------

void c_graphic_object::loop_animation(int animation_id)
  {
	this->playing_animation = animation_id;
	this->animation_frame = 0;
	this->looping_animation = true;
  }

//--------------------------------------------------

void c_graphic_object::stop_animation()
  {
    this->playing_animation = -1;
  }

//--------------------------------------------------